import numpy as np
import torch
import torch.nn as nn
from PIL import Image, ImageDraw
from typing import List, Tuple
import logging

class CGREncoder:
    """
    Chaos Game Representation (CGR) encoder for DNA sequences.
    Encodes DNA sequences into 2D images using the CGR algorithm.
    """
    
    def __init__(self, resolution: int = 64):
        """
        Initialize CGR encoder.
        
        Args:
            resolution: Output image resolution (resolution x resolution)
        """
        self.resolution = resolution
        self.nucleotide_coords = {
            'A': (0, 0),
            'T': (1, 0),
            'C': (0, 1),
            'G': (1, 1)
        }
        self.logger = logging.getLogger(__name__)
    
    def encode_sequence(self, sequence: str) -> np.ndarray:
        """
        Encode a DNA sequence into CGR representation.
        
        Args:
            sequence: DNA sequence string containing A, T, C, G
            
        Returns:
            CGR image as numpy array of shape (resolution, resolution)
        """
        # Initialize position at center
        x, y = 0.5, 0.5
        
        # Create frequency matrix
        freq_matrix = np.zeros((self.resolution, self.resolution))
        
        for nucleotide in sequence.upper():
            if nucleotide in self.nucleotide_coords:
                corner_x, corner_y = self.nucleotide_coords[nucleotide]
                
                # Move halfway towards the corner
                x = (x + corner_x) / 2
                y = (y + corner_y) / 2
                
                # Convert to pixel coordinates
                pixel_x = int(x * (self.resolution - 1))
                pixel_y = int(y * (self.resolution - 1))
                
                # Increment frequency
                freq_matrix[pixel_y, pixel_x] += 1
        
        return freq_matrix
    
    def encode_batch(self, sequences: List[str]) -> torch.Tensor:
        """
        Encode a batch of DNA sequences.
        
        Args:
            sequences: List of DNA sequence strings
            
        Returns:
            Batch tensor of shape (batch_size, 1, resolution, resolution)
        """
        batch_data = []
        
        for seq in sequences:
            cgr_matrix = self.encode_sequence(seq)
            
            # Normalize to [0, 1] range
            if cgr_matrix.max() > 0:
                cgr_matrix = cgr_matrix / cgr_matrix.max()
            
            batch_data.append(cgr_matrix)
        
        # Convert to tensor and add channel dimension
        batch_array = np.array(batch_data)  # Convert to numpy first
        batch_tensor = torch.FloatTensor(batch_array).unsqueeze(1)
        
        return batch_tensor
    
    def visualize_cgr(self, sequence: str, save_path: str = None) -> np.ndarray:
        """
        Visualize CGR representation of a sequence.
        
        Args:
            sequence: DNA sequence string
            save_path: Optional path to save the image
            
        Returns:
            CGR image as numpy array
        """
        cgr_matrix = self.encode_sequence(sequence)
        
        # Normalize for visualization
        if cgr_matrix.max() > 0:
            cgr_matrix = cgr_matrix / cgr_matrix.max() * 255
        
        if save_path:
            img = Image.fromarray(cgr_matrix.astype(np.uint8))
            img.save(save_path)
        
        return cgr_matrix