"""
Caps-ac4C Direct Training Version
=================================

A simplified version of the Caps-ac4C model for direct training without grid search.
Uses fixed hyperparameters from the original paper for optimal performance.

Key Features:
- CGR encoding at 64x64 resolution
- Capsule network with dynamic routing (3 iterations)
- Fixed hyperparameters for consistent results
- Comprehensive evaluation and visualization
- Early stopping and model saving

Usage:
    python main.py --data_path path/to/data.csv --output_dir results/
"""

import argparse
import logging
import os
import sys
import time
import json
import pandas as pd
from typing import List, Tuple
import warnings
warnings.filterwarnings('ignore')

# Import model components
from trainer import ModelTrainer
from evaluator import ModelEvaluator
from cgr_encoder import CGREncoder


def setup_logging(log_level: str = "INFO"):
    """Setup logging configuration"""
    log_format = '%(asctime)s - %(name)s - %(levelname)s - %(message)s'
    
    logging.basicConfig(
        level=getattr(logging, log_level.upper()),
        format=log_format,
        handlers=[
            logging.StreamHandler(sys.stdout),
        ]
    )


def load_sample_data() -> Tuple[List[str], List[int]]:
    """
    Load sample data for demonstration.
    In practice, replace this with your actual data loading function.
    """
    # Sample ac4C and non-ac4C sequences (example data)
    sequences = [
        # Positive samples (ac4C sites)
        "AUGCGGCUGCAUCCGAAGUGCGCAAAGCCGUCGGUGCUUCUCCGACAUGUGCGACAAGCCC",
        "CGGAUGCAGCCGAAGUGCGCAAAACCGUCGGUGCUUCUCCGAUUGUGCGACAAGCCCUGCC", 
        "GAUGCUGCAUCCGAAGUGCGCAAACCGUCGGUGCUUUCUCGAUUGUGCGACAAGCCCUGCC",
        "AUGCCGCUGCAUCCGAAGUGCGCAAAGCCAUCGGUGCUUCUCCGACAUGUGCGACAAGCCC",
        "CGGAUGCAGCUGAAGUGCGCAAAACCGUCGGUGCUUCUCCGAUUGUGCGACAAGCCCUGCC",
        # Negative samples (non-ac4C sites)  
        "AGCGGUGCAUCCGAAGUGCGCAAAGCCGUCGGUGCUUCUCCGACAUGUGCGACAAGCCCAA",
        "CGGAUGCAGCCGAAGUGCGCAAAACCGUCGGUGCUUCUCCGAUUGUGCGACAAGCCCUGAA",
        "GAUGCUGCAUCCGAAGUGCGCAAACCGUCGGUGCUUUCUCGAUUGUGCGACAAGCCCUGAA",
        "AUGCCGCUGCAUCCGAAGUGCGCAAAGCCAUCGGUGCUUCUCCGACAUGUGCGACAAGCAA",
        "CGGAUGCAGCUGAAGUGCGCAAAACCGUCGGUGCUUCUCCGAUUGUGCGACAAGCCCUGAA",
        # Add more samples
        "AUGCGGCUGCAUCCGAAGUGCGCAAAGCCGUCGGUGCUUCUCCGACAUGUGCGACAAGCCC",
        "AGCGGUGCAUCCGAAGUGCGCAAAGCCGUCGGUGCUUCUCCGACAUGUGCGACAAGCCCAA",
        "CGGAUGCAGCCGAAGUGCGCAAAACCGUCGGUGCUUCUCCGAUUGUGCGACAAGCCCUGCC",
        "CGGAUGCAGCCGAAGUGCGCAAAACCGUCGGUGCUUCUCCGAUUGUGCGACAAGCCCUGAA",
        "GAUGCUGCAUCCGAAGUGCGCAAACCGUCGGUGCUUUCUCGAUUGUGCGACAAGCCCUGCC",
        "GAUGCUGCAUCCGAAGUGCGCAAACCGUCGGUGCUUUCUCGAUUGUGCGACAAGCCCUGAA",
    ]
    
    # Labels: 1 for ac4C sites, 0 for non-ac4C sites
    labels = [1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0]
    
    # Generate more synthetic data for demonstration
    import random
    import string
    
    def generate_sequence(length=60):
        """Generate random RNA sequence"""
        nucleotides = ['A', 'U', 'G', 'C']
        return ''.join(random.choice(nucleotides) for _ in range(length))
    
    # Add more synthetic samples
    for i in range(100):  # 100 additional samples
        seq = generate_sequence()
        label = random.randint(0, 1)
        sequences.append(seq)
        labels.append(label)
    
    return sequences, labels


def load_data_from_file(data_path: str) -> Tuple[List[str], List[int]]:
    """
    Load data from CSV file.
    Expected format: columns 'sequence' and 'label'
    """
    try:
        df = pd.read_csv(data_path)
        
        if 'sequence' not in df.columns or 'label' not in df.columns:
            raise ValueError("CSV must contain 'sequence' and 'label' columns")
        
        sequences = df['sequence'].tolist()
        labels = df['label'].tolist()
        
        return sequences, labels
    
    except Exception as e:
        logging.error(f"Error loading data from {data_path}: {e}")
        logging.info("Using sample data instead...")
        return load_sample_data()


def main():
    """Main training and evaluation pipeline"""
    parser = argparse.ArgumentParser(description="Caps-ac4C Direct Training")
    parser.add_argument('--data_path', type=str, default=None,
                       help='Path to CSV file with sequence data')
    parser.add_argument('--output_dir', type=str, default='./caps_ac4c_results',
                       help='Output directory for results')
    parser.add_argument('--log_level', type=str, default='INFO',
                       choices=['DEBUG', 'INFO', 'WARNING', 'ERROR'],
                       help='Logging level')
    parser.add_argument('--device', type=str, default=None,
                       help='Device to use (cuda/cpu)')
    
    args = parser.parse_args()
    
    # Setup
    setup_logging(args.log_level)
    logger = logging.getLogger(__name__)
    
    # Create output directory
    os.makedirs(args.output_dir, exist_ok=True)
    
    logger.info("=" * 50)
    logger.info("Caps-ac4C Direct Training Pipeline")
    logger.info("=" * 50)
    
    # Load data
    logger.info("Loading data...")
    if args.data_path and os.path.exists(args.data_path):
        sequences, labels = load_data_from_file(args.data_path)
    else:
        logger.info("No data file specified or file not found. Using sample data.")
        sequences, labels = load_sample_data()
    
    logger.info(f"Loaded {len(sequences)} sequences")
    logger.info(f"Class distribution: {sum(labels)} positive, {len(labels) - sum(labels)} negative")
    
    # Initialize trainer
    logger.info("Initializing trainer with fixed hyperparameters...")
    trainer = ModelTrainer(
        device=args.device,
        log_dir=os.path.join(args.output_dir, 'logs'),
        model_dir=os.path.join(args.output_dir, 'models')
    )
    
    logger.info("Fixed Hyperparameters:")
    for key, value in trainer.config.items():
        logger.info(f"  {key}: {value}")
    
    # Train model
    logger.info("Starting training...")
    start_time = time.time()
    
    training_results = trainer.train(sequences, labels)
    
    training_time = time.time() - start_time
    logger.info(f"Training completed in {training_time:.2f} seconds")
    
    # Initialize evaluator
    logger.info("Initializing evaluator...")
    evaluator = ModelEvaluator(
        model=trainer.model,
        device=trainer.device,
        save_dir=os.path.join(args.output_dir, 'evaluation')
    )
    
    # Comprehensive evaluation
    logger.info("Performing comprehensive evaluation...")
    eval_results = evaluator.evaluate(sequences, labels)
    
    # Generate report
    logger.info("Generating comprehensive report...")
    report_dir = evaluator.generate_comprehensive_report(
        results=eval_results,
        history=training_results['history'],
        sequences=sequences,
        save_prefix="caps_ac4c_direct"
    )
    
    # Save final summary
    summary = {
        'training_time': training_time,
        'final_metrics': {
            'accuracy': eval_results['accuracy'],
            'precision': eval_results['precision'],
            'recall': eval_results['recall'],
            'f1_score': eval_results['f1_score'],
            'auc_roc': eval_results['auc_roc'],
            'mcc': eval_results['mcc']
        },
        'config': trainer.config,
        'data_info': {
            'num_samples': len(sequences),
            'num_positive': sum(labels),
            'num_negative': len(labels) - sum(labels)
        }
    }
    
    summary_path = os.path.join(args.output_dir, 'final_summary.json')
    with open(summary_path, 'w') as f:
        json.dump(summary, f, indent=2)
    
    # Print final results
    logger.info("=" * 50)
    logger.info("FINAL RESULTS")
    logger.info("=" * 50)
    logger.info(f"Training Time: {training_time:.2f} seconds")
    logger.info(f"Accuracy: {eval_results['accuracy']:.4f}")
    logger.info(f"Precision: {eval_results['precision']:.4f}")
    logger.info(f"Recall: {eval_results['recall']:.4f}")
    logger.info(f"F1-Score: {eval_results['f1_score']:.4f}")
    logger.info(f"AUC-ROC: {eval_results['auc_roc']:.4f}")
    logger.info(f"MCC: {eval_results['mcc']:.4f}")
    logger.info(f"Results saved to: {args.output_dir}")
    logger.info(f"Detailed report: {report_dir}")
    logger.info("=" * 50)


if __name__ == "__main__":
    main()