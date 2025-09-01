import torch
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.metrics import (
    accuracy_score, precision_recall_fscore_support, roc_auc_score,
    confusion_matrix, classification_report, roc_curve, precision_recall_curve
)
from sklearn.manifold import TSNE
from torch.utils.data import DataLoader, TensorDataset
import pandas as pd
import logging
import os
from typing import Dict, List, Tuple, Optional
from tqdm import tqdm

from capsule_network import CapsAC4CNet
from cgr_encoder import CGREncoder


class ModelEvaluator:
    """
    Comprehensive evaluation and visualization for Caps-ac4C model.
    """
    
    def __init__(self, model: CapsAC4CNet, device: str = None, save_dir: str = "./results"):
        """
        Initialize evaluator.
        
        Args:
            model: Trained Caps-ac4C model
            device: Computing device
            save_dir: Directory to save results
        """
        self.model = model
        self.device = torch.device(device if device else 
                                 ('cuda' if torch.cuda.is_available() else 'cpu'))
        self.model.to(self.device)
        self.save_dir = save_dir
        os.makedirs(save_dir, exist_ok=True)
        
        self.logger = logging.getLogger(__name__)
        
        # CGR encoder for visualization
        self.cgr_encoder = CGREncoder(resolution=64)
    
    def predict(self, sequences: List[str], batch_size: int = 32) -> Dict:
        """
        Make predictions on sequences.
        
        Args:
            sequences: List of DNA sequences
            batch_size: Batch size for prediction
            
        Returns:
            Dictionary containing predictions and confidence scores
        """
        self.model.eval()
        
        # Encode sequences
        cgr_data = self.cgr_encoder.encode_batch(sequences)
        
        # Create data loader
        dataset = TensorDataset(cgr_data)
        data_loader = DataLoader(dataset, batch_size=batch_size, shuffle=False)
        
        predictions = []
        probabilities = []
        capsule_outputs = []
        
        with torch.no_grad():
            for (data,) in tqdm(data_loader, desc="Predicting"):
                data = data.to(self.device)
                
                outputs = self.model(data)
                
                # Get class predictions
                class_probs = outputs['class_predictions']
                pred_classes = class_probs.argmax(dim=1)
                
                predictions.extend(pred_classes.cpu().numpy())
                probabilities.extend(class_probs.cpu().numpy())
                capsule_outputs.extend(outputs['digit_caps'].cpu().numpy())
        
        return {
            'predictions': np.array(predictions),
            'probabilities': np.array(probabilities),
            'capsule_outputs': np.array(capsule_outputs)
        }
    
    def evaluate(self, sequences: List[str], labels: List[int], 
                batch_size: int = 32) -> Dict:
        """
        Comprehensive evaluation of the model.
        
        Args:
            sequences: List of DNA sequences
            labels: True labels
            batch_size: Batch size for evaluation
            
        Returns:
            Dictionary containing all evaluation metrics
        """
        self.logger.info("Starting comprehensive evaluation...")
        
        # Get predictions
        predictions_dict = self.predict(sequences, batch_size)
        predictions = predictions_dict['predictions']
        probabilities = predictions_dict['probabilities']
        
        # Basic metrics
        accuracy = accuracy_score(labels, predictions)
        precision, recall, f1, support = precision_recall_fscore_support(
            labels, predictions, average='binary'
        )
        
        # AUC metrics
        pos_probs = probabilities[:, 1]  # Probability of positive class
        try:
            auc_roc = roc_auc_score(labels, pos_probs)
        except ValueError:
            auc_roc = 0.0
        
        # Confusion matrix
        cm = confusion_matrix(labels, predictions)
        
        # Specificity and sensitivity
        tn, fp, fn, tp = cm.ravel()
        specificity = tn / (tn + fp) if (tn + fp) > 0 else 0
        sensitivity = tp / (tp + fn) if (tp + fn) > 0 else 0
        
        # MCC (Matthews Correlation Coefficient)
        mcc = ((tp * tn) - (fp * fn)) / np.sqrt(
            (tp + fp) * (tp + fn) * (tn + fp) * (tn + fn)
        ) if (tp + fp) * (tp + fn) * (tn + fp) * (tn + fn) > 0 else 0
        
        # Compile results
        results = {
            'accuracy': accuracy,
            'precision': precision,
            'recall': recall,
            'f1_score': f1,
            'specificity': specificity,
            'sensitivity': sensitivity,
            'auc_roc': auc_roc,
            'mcc': mcc,
            'confusion_matrix': cm,
            'predictions': predictions,
            'probabilities': probabilities,
            'true_labels': labels,
            'support': support,
            'capsule_outputs': predictions_dict['capsule_outputs']
        }
        
        # Log results
        self.logger.info("Evaluation Results:")
        self.logger.info(f"Accuracy: {accuracy:.4f}")
        self.logger.info(f"Precision: {precision:.4f}")
        self.logger.info(f"Recall: {recall:.4f}")
        self.logger.info(f"F1-Score: {f1:.4f}")
        self.logger.info(f"Specificity: {specificity:.4f}")
        self.logger.info(f"Sensitivity: {sensitivity:.4f}")
        self.logger.info(f"AUC-ROC: {auc_roc:.4f}")
        self.logger.info(f"MCC: {mcc:.4f}")
        
        return results
    
    def plot_training_history(self, history: Dict, save_path: str = None):
        """Plot training history curves"""
        fig, axes = plt.subplots(2, 2, figsize=(15, 10))
        fig.suptitle('Training History', fontsize=16)
        
        # Loss curves
        axes[0, 0].plot(history['train_loss'], label='Train Loss', color='blue')
        axes[0, 0].plot(history['val_loss'], label='Validation Loss', color='red')
        axes[0, 0].set_title('Total Loss')
        axes[0, 0].set_xlabel('Epoch')
        axes[0, 0].set_ylabel('Loss')
        axes[0, 0].legend()
        axes[0, 0].grid(True)
        
        # Accuracy curves
        axes[0, 1].plot(history['train_accuracy'], label='Train Accuracy', color='blue')
        axes[0, 1].plot(history['val_accuracy'], label='Validation Accuracy', color='red')
        axes[0, 1].set_title('Accuracy')
        axes[0, 1].set_xlabel('Epoch')
        axes[0, 1].set_ylabel('Accuracy')
        axes[0, 1].legend()
        axes[0, 1].grid(True)
        
        # Margin loss
        axes[1, 0].plot(history['train_margin_loss'], label='Train Margin Loss', color='green')
        axes[1, 0].plot(history['val_margin_loss'], label='Val Margin Loss', color='orange')
        axes[1, 0].set_title('Margin Loss')
        axes[1, 0].set_xlabel('Epoch')
        axes[1, 0].set_ylabel('Margin Loss')
        axes[1, 0].legend()
        axes[1, 0].grid(True)
        
        # Learning rate
        axes[1, 1].plot(history['learning_rates'], color='purple')
        axes[1, 1].set_title('Learning Rate')
        axes[1, 1].set_xlabel('Epoch')
        axes[1, 1].set_ylabel('Learning Rate')
        axes[1, 1].set_yscale('log')
        axes[1, 1].grid(True)
        
        plt.tight_layout()
        
        if save_path:
            plt.savefig(save_path, dpi=300, bbox_inches='tight')
            self.logger.info(f"Training history plot saved to: {save_path}")
        else:
            plt.savefig(os.path.join(self.save_dir, 'training_history.png'), 
                       dpi=300, bbox_inches='tight')
        
        plt.show()
    
    def plot_confusion_matrix(self, results: Dict, save_path: str = None):
        """Plot confusion matrix"""
        cm = results['confusion_matrix']
        
        plt.figure(figsize=(8, 6))
        sns.heatmap(cm, annot=True, fmt='d', cmap='Blues', 
                   xticklabels=['Negative', 'Positive'],
                   yticklabels=['Negative', 'Positive'])
        plt.title('Confusion Matrix')
        plt.xlabel('Predicted Label')
        plt.ylabel('True Label')
        
        if save_path:
            plt.savefig(save_path, dpi=300, bbox_inches='tight')
        else:
            plt.savefig(os.path.join(self.save_dir, 'confusion_matrix.png'),
                       dpi=300, bbox_inches='tight')
        
        plt.show()
    
    def plot_roc_curve(self, results: Dict, save_path: str = None):
        """Plot ROC curve"""
        labels = results['true_labels']
        probabilities = results['probabilities'][:, 1]
        
        fpr, tpr, thresholds = roc_curve(labels, probabilities)
        auc_score = results['auc_roc']
        
        plt.figure(figsize=(8, 6))
        plt.plot(fpr, tpr, color='darkorange', lw=2, 
                label=f'ROC Curve (AUC = {auc_score:.4f})')
        plt.plot([0, 1], [0, 1], color='navy', lw=2, linestyle='--')
        plt.xlim([0.0, 1.0])
        plt.ylim([0.0, 1.05])
        plt.xlabel('False Positive Rate')
        plt.ylabel('True Positive Rate')
        plt.title('Receiver Operating Characteristic (ROC) Curve')
        plt.legend(loc="lower right")
        plt.grid(True)
        
        if save_path:
            plt.savefig(save_path, dpi=300, bbox_inches='tight')
        else:
            plt.savefig(os.path.join(self.save_dir, 'roc_curve.png'),
                       dpi=300, bbox_inches='tight')
        
        plt.show()
    
    def plot_precision_recall_curve(self, results: Dict, save_path: str = None):
        """Plot Precision-Recall curve"""
        labels = results['true_labels']
        probabilities = results['probabilities'][:, 1]
        
        precision, recall, thresholds = precision_recall_curve(labels, probabilities)
        
        plt.figure(figsize=(8, 6))
        plt.plot(recall, precision, color='blue', lw=2)
        plt.xlabel('Recall')
        plt.ylabel('Precision')
        plt.title('Precision-Recall Curve')
        plt.grid(True)
        
        if save_path:
            plt.savefig(save_path, dpi=300, bbox_inches='tight')
        else:
            plt.savefig(os.path.join(self.save_dir, 'precision_recall_curve.png'),
                       dpi=300, bbox_inches='tight')
        
        plt.show()
    
    def plot_capsule_visualization(self, results: Dict, sequences: List[str], 
                                 save_path: str = None):
        """Visualize capsule outputs using t-SNE"""
        capsule_outputs = results['capsule_outputs']
        labels = results['true_labels']
        
        # Flatten capsule outputs for t-SNE
        capsule_flat = capsule_outputs.reshape(len(capsule_outputs), -1)
        
        # Apply t-SNE
        self.logger.info("Applying t-SNE to capsule outputs...")
        tsne = TSNE(n_components=2, random_state=42, perplexity=min(30, len(capsule_outputs)//4))
        tsne_results = tsne.fit_transform(capsule_flat)
        
        # Plot
        plt.figure(figsize=(10, 8))
        scatter = plt.scatter(tsne_results[:, 0], tsne_results[:, 1], 
                            c=labels, cmap='viridis', alpha=0.7)
        plt.colorbar(scatter, label='Class')
        plt.title('t-SNE Visualization of Capsule Outputs')
        plt.xlabel('t-SNE Component 1')
        plt.ylabel('t-SNE Component 2')
        
        if save_path:
            plt.savefig(save_path, dpi=300, bbox_inches='tight')
        else:
            plt.savefig(os.path.join(self.save_dir, 'capsule_tsne.png'),
                       dpi=300, bbox_inches='tight')
        
        plt.show()
    
    def plot_cgr_samples(self, sequences: List[str], labels: List[int], 
                        n_samples: int = 8, save_path: str = None):
        """Plot sample CGR encodings"""
        fig, axes = plt.subplots(2, n_samples//2, figsize=(15, 6))
        axes = axes.flatten()
        
        # Select random samples
        indices = np.random.choice(len(sequences), n_samples, replace=False)
        
        for i, idx in enumerate(indices):
            seq = sequences[idx]
            label = labels[idx]
            
            # Generate CGR
            cgr_matrix = self.cgr_encoder.encode_sequence(seq)
            
            # Plot
            axes[i].imshow(cgr_matrix, cmap='viridis')
            axes[i].set_title(f'Label: {label}', fontsize=10)
            axes[i].axis('off')
        
        plt.suptitle('Sample CGR Encodings', fontsize=14)
        plt.tight_layout()
        
        if save_path:
            plt.savefig(save_path, dpi=300, bbox_inches='tight')
        else:
            plt.savefig(os.path.join(self.save_dir, 'cgr_samples.png'),
                       dpi=300, bbox_inches='tight')
        
        plt.show()
    
    def generate_comprehensive_report(self, results: Dict, history: Dict,
                                    sequences: List[str], save_prefix: str = "caps_ac4c"):
        """Generate comprehensive evaluation report with all visualizations"""
        self.logger.info("Generating comprehensive evaluation report...")
        
        # Create results directory
        report_dir = os.path.join(self.save_dir, f"{save_prefix}_report")
        os.makedirs(report_dir, exist_ok=True)
        
        # Generate all plots
        self.plot_training_history(history, 
                                 os.path.join(report_dir, 'training_history.png'))
        self.plot_confusion_matrix(results, 
                                 os.path.join(report_dir, 'confusion_matrix.png'))
        self.plot_roc_curve(results, 
                          os.path.join(report_dir, 'roc_curve.png'))
        self.plot_precision_recall_curve(results, 
                                        os.path.join(report_dir, 'precision_recall_curve.png'))
        self.plot_capsule_visualization(results, sequences,
                                      os.path.join(report_dir, 'capsule_tsne.png'))
        self.plot_cgr_samples(sequences, results['true_labels'],
                            save_path=os.path.join(report_dir, 'cgr_samples.png'))
        
        # Save numerical results
        results_summary = {
            'accuracy': results['accuracy'],
            'precision': results['precision'],
            'recall': results['recall'],
            'f1_score': results['f1_score'],
            'specificity': results['specificity'],
            'sensitivity': results['sensitivity'],
            'auc_roc': results['auc_roc'],
            'mcc': results['mcc']
        }
        
        # Save to CSV
        df_results = pd.DataFrame([results_summary])
        df_results.to_csv(os.path.join(report_dir, 'evaluation_metrics.csv'), index=False)
        
        # Save detailed classification report
        with open(os.path.join(report_dir, 'classification_report.txt'), 'w') as f:
            f.write(classification_report(results['true_labels'], results['predictions']))
        
        self.logger.info(f"Comprehensive report saved to: {report_dir}")
        
        return report_dir