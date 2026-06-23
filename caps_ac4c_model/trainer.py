import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader, TensorDataset
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.metrics import accuracy_score, precision_recall_fscore_support, roc_auc_score, confusion_matrix
from tqdm import tqdm
import logging
import time
import os
from typing import Dict, List, Tuple, Optional
import json

from capsule_network import CapsAC4CNet, CapsuleLoss
from cgr_encoder import CGREncoder


class ModelTrainer:
    """
    Direct trainer for Caps-ac4C model with fixed hyperparameters.
    No grid search, uses validated parameters from original paper.
    """
    
    def __init__(self, 
                 device: str = None,
                 log_dir: str = "./logs",
                 model_dir: str = "./models"):
        """
        Initialize trainer with fixed hyperparameters.
        
        Args:
            device: Computing device (cuda/cpu)
            log_dir: Directory for logging
            model_dir: Directory for model saving
        """
        # Fixed hyperparameters from original paper
        self.config = {
            'cgr_resolution': 64,
            'routing_iterations': 3,
            'primary_caps_num': 64,
            'primary_caps_dim': 16,
            'digit_caps_dim': 32,
            'learning_rate': 0.0007,
            'batch_size': 32,
            'epochs': 50,
            'lambda_recon': 0.0005,
            'early_stopping_patience': 10,
            'weight_decay': 1e-4
        }
        
        # Setup device
        if device is None:
            self.device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
        else:
            self.device = torch.device(device)
            
        # Setup directories
        self.log_dir = log_dir
        self.model_dir = model_dir
        os.makedirs(log_dir, exist_ok=True)
        os.makedirs(model_dir, exist_ok=True)
        
        # Setup logging
        self.setup_logging()
        
        # Initialize components
        self.cgr_encoder = CGREncoder(resolution=self.config['cgr_resolution'])
        self.model = None
        self.optimizer = None
        self.criterion = None
        self.scheduler = None
        
        # Training history
        self.history = {
            'train_loss': [],
            'train_margin_loss': [],
            'train_recon_loss': [],
            'val_loss': [],
            'val_margin_loss': [],
            'val_recon_loss': [],
            'train_accuracy': [],
            'val_accuracy': [],
            'learning_rates': []
        }
        
        self.logger.info(f"Trainer initialized with device: {self.device}")
        self.logger.info(f"Configuration: {self.config}")
    
    def setup_logging(self):
        """Setup logging configuration"""
        log_file = os.path.join(self.log_dir, f"training_{time.strftime('%Y%m%d_%H%M%S')}.log")
        
        logging.basicConfig(
            level=logging.INFO,
            format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
            handlers=[
                logging.FileHandler(log_file),
                logging.StreamHandler()
            ]
        )
        self.logger = logging.getLogger(__name__)
    
    def build_model(self):
        """Build the Caps-ac4C model with fixed parameters"""
        self.model = CapsAC4CNet(
            primary_caps_num=self.config['primary_caps_num'],
            primary_caps_dim=self.config['primary_caps_dim'],
            digit_caps_num=2,  # Binary classification
            digit_caps_dim=self.config['digit_caps_dim'],
            routing_iterations=self.config['routing_iterations']
        ).to(self.device)
        
        # Setup loss function
        self.criterion = CapsuleLoss(lambda_recon=self.config['lambda_recon'])
        
        # Setup optimizer
        self.optimizer = optim.Adam(
            self.model.parameters(),
            lr=self.config['learning_rate'],
            weight_decay=self.config['weight_decay']
        )
        
        # Setup learning rate scheduler
        self.scheduler = optim.lr_scheduler.ReduceLROnPlateau(
            self.optimizer, mode='min', factor=0.5, patience=5
        )
        
        # Model summary
        total_params = sum(p.numel() for p in self.model.parameters())
        trainable_params = sum(p.numel() for p in self.model.parameters() if p.requires_grad)
        
        self.logger.info(f"Model built successfully!")
        self.logger.info(f"Total parameters: {total_params:,}")
        self.logger.info(f"Trainable parameters: {trainable_params:,}")
    
    def prepare_data(self, sequences: List[str], labels: List[int],
                    val_split: float = 0.2) -> Tuple[DataLoader, DataLoader]:
        """
        Prepare data for training.
        
        Args:
            sequences: List of DNA sequences
            labels: List of binary labels (0/1)
            val_split: Validation split ratio
            
        Returns:
            Tuple of (train_loader, val_loader)
        """
        self.logger.info("Preparing data...")
        
        # Encode sequences to CGR
        cgr_data = self.cgr_encoder.encode_batch(sequences)
        labels_tensor = torch.LongTensor(labels)
        
        # Split data
        n_samples = len(sequences)
        n_val = int(n_samples * val_split)
        n_train = n_samples - n_val
        
        # Random split
        indices = np.random.permutation(n_samples)
        train_indices = indices[:n_train]
        val_indices = indices[n_train:]
        
        # Create datasets
        train_dataset = TensorDataset(cgr_data[train_indices], labels_tensor[train_indices])
        val_dataset = TensorDataset(cgr_data[val_indices], labels_tensor[val_indices])
        
        # Create data loaders
        train_loader = DataLoader(
            train_dataset, 
            batch_size=self.config['batch_size'],
            shuffle=True,
            num_workers=4,
            pin_memory=True if self.device.type == 'cuda' else False
        )
        
        val_loader = DataLoader(
            val_dataset,
            batch_size=self.config['batch_size'],
            shuffle=False,
            num_workers=4,
            pin_memory=True if self.device.type == 'cuda' else False
        )
        
        self.logger.info(f"Data prepared: {n_train} training, {n_val} validation samples")
        
        return train_loader, val_loader
    
    def train_epoch(self, train_loader: DataLoader) -> Dict[str, float]:
        """Train for one epoch"""
        self.model.train()
        
        epoch_loss = 0.0
        epoch_margin_loss = 0.0
        epoch_recon_loss = 0.0
        correct = 0
        total = 0
        
        progress_bar = tqdm(train_loader, desc="Training")
        
        for batch_idx, (data, targets) in enumerate(progress_bar):
            data, targets = data.to(self.device), targets.to(self.device)
            
            self.optimizer.zero_grad()
            
            # Forward pass
            outputs = self.model(data, targets)
            
            # Calculate loss
            loss_dict = self.criterion(outputs, targets, data)
            total_loss = loss_dict['total_loss']
            
            # Backward pass
            total_loss.backward()
            
            # Gradient clipping
            torch.nn.utils.clip_grad_norm_(self.model.parameters(), max_norm=1.0)
            
            self.optimizer.step()
            
            # Statistics
            epoch_loss += total_loss.item()
            epoch_margin_loss += loss_dict['margin_loss'].item()
            epoch_recon_loss += loss_dict['reconstruction_loss'].item()
            
            # Accuracy
            predictions = outputs['class_predictions'].argmax(dim=1)
            correct += (predictions == targets).sum().item()
            total += targets.size(0)
            
            # Update progress bar
            progress_bar.set_postfix({
                'Loss': f"{total_loss.item():.4f}",
                'Acc': f"{100 * correct / total:.2f}%"
            })
        
        return {
            'loss': epoch_loss / len(train_loader),
            'margin_loss': epoch_margin_loss / len(train_loader),
            'recon_loss': epoch_recon_loss / len(train_loader),
            'accuracy': correct / total
        }
    
    def validate_epoch(self, val_loader: DataLoader) -> Dict[str, float]:
        """Validate for one epoch"""
        self.model.eval()
        
        epoch_loss = 0.0
        epoch_margin_loss = 0.0
        epoch_recon_loss = 0.0
        correct = 0
        total = 0
        
        with torch.no_grad():
            for data, targets in tqdm(val_loader, desc="Validation"):
                data, targets = data.to(self.device), targets.to(self.device)
                
                # Forward pass
                outputs = self.model(data, targets)
                
                # Calculate loss
                loss_dict = self.criterion(outputs, targets, data)
                
                # Statistics
                epoch_loss += loss_dict['total_loss'].item()
                epoch_margin_loss += loss_dict['margin_loss'].item()
                epoch_recon_loss += loss_dict['reconstruction_loss'].item()
                
                # Accuracy
                predictions = outputs['class_predictions'].argmax(dim=1)
                correct += (predictions == targets).sum().item()
                total += targets.size(0)
        
        return {
            'loss': epoch_loss / len(val_loader),
            'margin_loss': epoch_margin_loss / len(val_loader),
            'recon_loss': epoch_recon_loss / len(val_loader),
            'accuracy': correct / total
        }
    
    def train(self, sequences: List[str], labels: List[int]) -> Dict:
        """
        Train the model with direct parameters (no grid search).
        
        Args:
            sequences: List of DNA sequences
            labels: List of binary labels
            
        Returns:
            Training history and best model info
        """
        self.logger.info("Starting direct training...")
        
        # Build model
        if self.model is None:
            self.build_model()
        
        # Prepare data
        train_loader, val_loader = self.prepare_data(sequences, labels)
        
        # Early stopping setup
        best_val_loss = float('inf')
        patience_counter = 0
        best_model_state = None
        
        # Training loop
        for epoch in range(self.config['epochs']):
            epoch_start_time = time.time()
            
            # Train
            train_metrics = self.train_epoch(train_loader)
            
            # Validate
            val_metrics = self.validate_epoch(val_loader)
            
            # Learning rate scheduling
            self.scheduler.step(val_metrics['loss'])
            current_lr = self.optimizer.param_groups[0]['lr']
            
            # Update history
            self.history['train_loss'].append(train_metrics['loss'])
            self.history['train_margin_loss'].append(train_metrics['margin_loss'])
            self.history['train_recon_loss'].append(train_metrics['recon_loss'])
            self.history['train_accuracy'].append(train_metrics['accuracy'])
            
            self.history['val_loss'].append(val_metrics['loss'])
            self.history['val_margin_loss'].append(val_metrics['margin_loss'])
            self.history['val_recon_loss'].append(val_metrics['recon_loss'])
            self.history['val_accuracy'].append(val_metrics['accuracy'])
            self.history['learning_rates'].append(current_lr)
            
            # Early stopping check
            if val_metrics['loss'] < best_val_loss:
                best_val_loss = val_metrics['loss']
                patience_counter = 0
                best_model_state = self.model.state_dict().copy()
            else:
                patience_counter += 1
            
            # Logging
            epoch_time = time.time() - epoch_start_time
            self.logger.info(
                f"Epoch {epoch+1}/{self.config['epochs']} | "
                f"Time: {epoch_time:.2f}s | "
                f"Train Loss: {train_metrics['loss']:.4f} | "
                f"Train Acc: {train_metrics['accuracy']:.4f} | "
                f"Val Loss: {val_metrics['loss']:.4f} | "
                f"Val Acc: {val_metrics['accuracy']:.4f} | "
                f"LR: {current_lr:.6f}"
            )
            
            # Early stopping
            if patience_counter >= self.config['early_stopping_patience']:
                self.logger.info(f"Early stopping at epoch {epoch+1}")
                break
        
        # Load best model
        if best_model_state is not None:
            self.model.load_state_dict(best_model_state)
        
        # Save model and history
        self.save_model()
        self.save_history()
        
        self.logger.info("Training completed!")
        
        return {
            'history': self.history,
            'best_val_loss': best_val_loss,
            'config': self.config
        }
    
    def save_model(self, filename: str = None):
        """Save the trained model"""
        if filename is None:
            filename = f"caps_ac4c_model_{time.strftime('%Y%m%d_%H%M%S')}.pth"
        
        model_path = os.path.join(self.model_dir, filename)
        
        torch.save({
            'model_state_dict': self.model.state_dict(),
            'config': self.config,
            'history': self.history
        }, model_path)
        
        self.logger.info(f"Model saved to: {model_path}")
        return model_path
    
    def save_history(self, filename: str = None):
        """Save training history"""
        if filename is None:
            filename = f"training_history_{time.strftime('%Y%m%d_%H%M%S')}.json"
        
        history_path = os.path.join(self.log_dir, filename)
        
        with open(history_path, 'w') as f:
            json.dump(self.history, f, indent=2)
        
        self.logger.info(f"Training history saved to: {history_path}")
        return history_path
    
    def load_model(self, model_path: str):
        """Load a saved model"""
        checkpoint = torch.load(model_path, map_location=self.device)
        
        # Build model if not exists
        if self.model is None:
            self.config = checkpoint['config']
            self.build_model()
        
        self.model.load_state_dict(checkpoint['model_state_dict'])
        
        if 'history' in checkpoint:
            self.history = checkpoint['history']
        
        self.logger.info(f"Model loaded from: {model_path}")
        
        return self.model