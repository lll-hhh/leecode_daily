import torch
import torch.nn as nn
import torch.nn.functional as F
import logging

class PrimaryCaps(nn.Module):
    """Primary Capsule Layer"""
    
    def __init__(self, num_capsules: int = 64, capsule_dim: int = 16):
        """
        Initialize Primary Capsule Layer.
        
        Args:
            num_capsules: Number of primary capsules
            capsule_dim: Output dimension per capsule
        """
        super(PrimaryCaps, self).__init__()
        self.num_capsules = num_capsules
        self.capsule_dim = capsule_dim
        
        # Convolutional layers for feature extraction
        self.conv1 = nn.Conv2d(1, 32, kernel_size=9, stride=1, padding=4)  # 64x64 -> 64x64
        self.conv2 = nn.Conv2d(32, 64, kernel_size=9, stride=2, padding=4)  # 64x64 -> 32x32
        self.conv3 = nn.Conv2d(64, 128, kernel_size=9, stride=2, padding=4) # 32x32 -> 16x16
        
        # Capsule convolution - adjust kernel size for remaining feature map
        self.capsule_conv = nn.Conv2d(128, num_capsules * capsule_dim, 
                                     kernel_size=7, stride=2, padding=3) # 16x16 -> 8x8
        
    def forward(self, x):
        """Forward pass through primary capsules"""
        # Feature extraction
        x = F.relu(self.conv1(x))
        x = F.relu(self.conv2(x))
        x = F.relu(self.conv3(x))
        
        # Capsule formation
        capsules = self.capsule_conv(x)
        batch_size = capsules.size(0)
        
        # Reshape to [batch, num_capsules, capsule_dim]
        batch_size = capsules.size(0)
        spatial_size = capsules.size(2) * capsules.size(3)
        capsules = capsules.view(batch_size, self.num_capsules, self.capsule_dim, spatial_size)
        capsules = capsules.view(batch_size, self.num_capsules * spatial_size, self.capsule_dim)
        
        # Apply squashing function
        capsules = self.squash(capsules)
        
        return capsules
    
    def squash(self, tensor):
        """Squashing function for capsules"""
        squared_norm = (tensor ** 2).sum(dim=-1, keepdim=True)
        scale = squared_norm / (1 + squared_norm)
        unit_vector = tensor / torch.sqrt(squared_norm + 1e-8)
        return scale * unit_vector


class DigitCaps(nn.Module):
    """Digit Capsule Layer (Type Capsule)"""
    
    def __init__(self, num_capsules: int = 2, num_routes: int = 64 * 4,
                 in_caps_dim: int = 16, out_caps_dim: int = 32):
        """
        Initialize Digit Capsule Layer.
        
        Args:
            num_capsules: Number of output capsules (number of classes)
            num_routes: Number of input routes from primary capsules
            in_caps_dim: Input capsule dimension
            out_caps_dim: Output capsule dimension
        """
        super(DigitCaps, self).__init__()
        
        self.num_capsules = num_capsules
        self.num_routes = num_routes
        self.in_caps_dim = in_caps_dim
        self.out_caps_dim = out_caps_dim
        
        # Weight matrix for transformation
        self.W = nn.Parameter(torch.randn(num_capsules, num_routes, 
                                         out_caps_dim, in_caps_dim))
        
    def forward(self, x, num_iterations: int = 3):
        """
        Forward pass with dynamic routing.
        
        Args:
            x: Input from primary capsules [batch, num_routes, in_caps_dim]
            num_iterations: Number of routing iterations
        """
        batch_size = x.size(0)
        
        # Transform input capsules
        x_hat = torch.matmul(self.W, x[:, None, :, :, None])
        x_hat = x_hat.squeeze(-1)
        
        # Initialize routing logits
        b = torch.zeros(batch_size, self.num_capsules, self.num_routes, 1)
        if x.is_cuda:
            b = b.cuda()
        
        for i in range(num_iterations):
            # Softmax over capsules
            c = F.softmax(b, dim=1)
            
            # Weighted sum
            s = (c * x_hat).sum(dim=2)
            
            # Squash
            v = self.squash(s)
            
            if i < num_iterations - 1:
                # Update routing logits
                b += (x_hat * v[:, :, None, :]).sum(dim=-1, keepdim=True)
        
        return v
    
    def squash(self, tensor):
        """Squashing function for capsules"""
        squared_norm = (tensor ** 2).sum(dim=-1, keepdim=True)
        scale = squared_norm / (1 + squared_norm)
        unit_vector = tensor / torch.sqrt(squared_norm + 1e-8)
        return scale * unit_vector


class CapsAC4CNet(nn.Module):
    """
    Caps-ac4C Network for ac4C site prediction.
    Direct training version with fixed hyperparameters.
    """
    
    def __init__(self, 
                 primary_caps_num: int = 64,
                 primary_caps_dim: int = 16,
                 digit_caps_num: int = 2,
                 digit_caps_dim: int = 32,
                 routing_iterations: int = 3):
        """
        Initialize Caps-ac4C Network.
        
        Args:
            primary_caps_num: Number of primary capsules
            primary_caps_dim: Dimension of primary capsules
            digit_caps_num: Number of digit capsules (classes)
            digit_caps_dim: Dimension of digit capsules
            routing_iterations: Number of dynamic routing iterations
        """
        super(CapsAC4CNet, self).__init__()
        
        self.primary_caps_num = primary_caps_num
        self.primary_caps_dim = primary_caps_dim
        self.digit_caps_num = digit_caps_num
        self.digit_caps_dim = digit_caps_dim
        self.routing_iterations = routing_iterations
        
        # Primary Capsule Layer
        self.primary_caps = PrimaryCaps(
            num_capsules=primary_caps_num,
            capsule_dim=primary_caps_dim
        )
        
        # Calculate number of routes from primary capsules
        # After convolutions: 64x64 -> 64x64 -> 32x32 -> 16x16 -> 8x8
        feature_map_size = 8 * 8  # Final feature map size after convolutions
        num_routes = primary_caps_num * feature_map_size
        
        # Digit Capsule Layer
        self.digit_caps = DigitCaps(
            num_capsules=digit_caps_num,
            num_routes=num_routes,
            in_caps_dim=primary_caps_dim,
            out_caps_dim=digit_caps_dim
        )
        
        # Reconstruction network (optional for regularization)
        decoder_input_size = digit_caps_num * digit_caps_dim
        self.decoder = nn.Sequential(
            nn.Linear(decoder_input_size, 128),
            nn.ReLU(),
            nn.Linear(128, 256),
            nn.ReLU(),
            nn.Linear(256, 64*64),
            nn.Sigmoid()
        )
        
        self.logger = logging.getLogger(__name__)
    
    def forward(self, x, labels=None):
        """
        Forward pass through the network.
        
        Args:
            x: Input tensor [batch, 1, 64, 64]
            labels: Ground truth labels for reconstruction (optional)
            
        Returns:
            Dictionary containing predictions and reconstructions
        """
        # Primary capsules
        primary_caps_output = self.primary_caps(x)
        
        # Digit capsules with dynamic routing
        digit_caps_output = self.digit_caps(primary_caps_output, 
                                          self.routing_iterations)
        
        # Calculate predictions from capsule lengths
        class_predictions = torch.sqrt((digit_caps_output ** 2).sum(dim=2))
        
        # Reconstruction (for training stability)
        if labels is not None:
            # Mask the correct capsule for reconstruction
            masked_caps = self.mask_capsules(digit_caps_output, labels)
        else:
            # Use the longest capsule for reconstruction
            max_caps_idx = class_predictions.argmax(dim=1)
            masked_caps = self.mask_capsules(digit_caps_output, max_caps_idx)
        
        reconstruction = self.decoder(masked_caps)
        
        return {
            'class_predictions': class_predictions,
            'digit_caps': digit_caps_output,
            'reconstruction': reconstruction
        }
    
    def mask_capsules(self, digit_caps, labels):
        """Mask capsules for reconstruction"""
        batch_size = digit_caps.size(0)
        masked = torch.zeros_like(digit_caps)
        
        for i in range(batch_size):
            masked[i, labels[i]] = digit_caps[i, labels[i]]
        
        return masked.view(batch_size, -1)


class CapsuleLoss(nn.Module):
    """Capsule Network Loss Function"""
    
    def __init__(self, lambda_recon: float = 0.0005):
        """
        Initialize capsule loss.
        
        Args:
            lambda_recon: Reconstruction loss weight
        """
        super(CapsuleLoss, self).__init__()
        self.lambda_recon = lambda_recon
        self.mse_loss = nn.MSELoss()
    
    def forward(self, outputs, targets, input_images):
        """
        Calculate total capsule loss.
        
        Args:
            outputs: Model outputs dictionary
            targets: Ground truth labels
            input_images: Original input images for reconstruction
            
        Returns:
            Dictionary containing loss components
        """
        class_predictions = outputs['class_predictions']
        reconstruction = outputs['reconstruction']
        
        # Margin loss
        margin_loss = self.margin_loss(class_predictions, targets)
        
        # Reconstruction loss
        batch_size = input_images.size(0)
        input_flat = input_images.view(batch_size, -1)
        recon_loss = self.mse_loss(reconstruction, input_flat)
        
        # Total loss
        total_loss = margin_loss + self.lambda_recon * recon_loss
        
        return {
            'total_loss': total_loss,
            'margin_loss': margin_loss,
            'reconstruction_loss': recon_loss
        }
    
    def margin_loss(self, predictions, targets):
        """Calculate margin loss for capsule network"""
        batch_size = predictions.size(0)
        
        # Convert targets to one-hot
        targets_one_hot = torch.zeros_like(predictions)
        targets_one_hot.scatter_(1, targets.unsqueeze(1), 1)
        
        # Margin loss parameters
        m_plus = 0.9
        m_minus = 0.1
        lambda_val = 0.5
        
        # Calculate margin loss
        left = torch.clamp(m_plus - predictions, min=0) ** 2
        right = torch.clamp(predictions - m_minus, min=0) ** 2
        
        margin_loss = targets_one_hot * left + lambda_val * (1 - targets_one_hot) * right
        margin_loss = margin_loss.sum(dim=1).mean()
        
        return margin_loss