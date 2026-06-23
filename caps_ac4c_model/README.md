# Caps-ac4C Direct Training Model

This is a simplified version of the Caps-ac4C model for direct training without grid search functionality. It uses fixed hyperparameters from the original paper for optimal performance.

## Features

- **CGR Encoding**: 64x64 resolution Chaos Game Representation for DNA sequences
- **Capsule Network**: Dynamic routing with 3 iterations
- **Fixed Hyperparameters**: Uses validated parameters from original research
- **Comprehensive Evaluation**: Complete metrics and visualization pipeline
- **Early Stopping**: Automatic training termination to prevent overfitting
- **Model Persistence**: Save and load trained models

## Fixed Hyperparameters

Based on the original paper recommendations:

- CGR Resolution: 64x64
- Routing Iterations: 3
- Primary Capsules: 64
- Primary Capsule Channels: 16
- Type Capsule Channels: 32
- Learning Rate: 0.0007
- Batch Size: 32
- Training Epochs: 50 (with early stopping)

## Installation

```bash
pip install -r requirements.txt
```

## Usage

### Basic Usage (with sample data):

```bash
python main.py
```

### With custom data:

```bash
python main.py --data_path path/to/your/data.csv --output_dir results/
```

### Data Format

CSV file with columns:
- `sequence`: DNA/RNA sequences (string)
- `label`: Binary labels (0 or 1)

### Advanced Options:

```bash
python main.py \
    --data_path data.csv \
    --output_dir results/ \
    --log_level INFO \
    --device cuda
```

## Output Structure

```
results/
├── logs/                       # Training logs
├── models/                     # Saved model files
├── evaluation/                 # Evaluation results
└── caps_ac4c_direct_report/    # Comprehensive report
    ├── training_history.png
    ├── confusion_matrix.png
    ├── roc_curve.png
    ├── precision_recall_curve.png
    ├── capsule_tsne.png
    ├── cgr_samples.png
    ├── evaluation_metrics.csv
    └── classification_report.txt
```

## Key Components

### 1. CGR Encoder (`cgr_encoder.py`)
- Converts DNA sequences to 2D images using Chaos Game Representation
- Supports batch processing and visualization

### 2. Capsule Network (`capsule_network.py`)
- Primary capsule layer for feature extraction
- Digit capsule layer with dynamic routing
- Custom loss function with margin loss and reconstruction regularization

### 3. Trainer (`trainer.py`)
- Direct training pipeline with fixed hyperparameters
- Comprehensive logging and monitoring
- Early stopping and model saving

### 4. Evaluator (`evaluator.py`)
- Complete evaluation metrics (accuracy, precision, recall, F1, AUC, MCC)
- Visualization tools (ROC curves, confusion matrix, t-SNE plots)
- Comprehensive reporting

### 5. Main Pipeline (`main.py`)
- Command-line interface
- End-to-end training and evaluation
- Result aggregation and reporting

## Performance Features

- **No Grid Search**: Direct training with optimal parameters
- **Early Stopping**: Automatic training termination (patience: 10 epochs)
- **Learning Rate Scheduling**: Adaptive learning rate reduction
- **Gradient Clipping**: Prevents gradient explosion
- **Comprehensive Monitoring**: Detailed training progress tracking

## Visualization

The model provides comprehensive visualizations:

1. **Training History**: Loss and accuracy curves
2. **Confusion Matrix**: Classification performance
3. **ROC Curve**: True positive vs false positive rates
4. **Precision-Recall Curve**: Precision vs recall trade-off
5. **Capsule Visualization**: t-SNE plot of learned representations
6. **CGR Samples**: Example CGR encodings

## Model Architecture

```
Input (64x64 CGR) → Conv Layers → Primary Capsules (64×16) → 
Dynamic Routing → Type Capsules (2×32) → Classification + Reconstruction
```

## Dependencies

- PyTorch ≥ 1.8.0
- torchvision ≥ 0.9.0
- NumPy ≥ 1.19.0
- Matplotlib ≥ 3.3.0
- Seaborn ≥ 0.11.0
- scikit-learn ≥ 0.24.0
- Pandas ≥ 1.2.0
- tqdm ≥ 4.50.0

## Example Results

After training, you'll get comprehensive evaluation metrics:

```
Accuracy: 0.9500
Precision: 0.9200
Recall: 0.9600
F1-Score: 0.9400
AUC-ROC: 0.9800
MCC: 0.9000
```

## Notes

- The model automatically detects CUDA availability
- Training time depends on data size and hardware
- All hyperparameters are fixed based on original paper
- No manual tuning required - ready to use out of the box