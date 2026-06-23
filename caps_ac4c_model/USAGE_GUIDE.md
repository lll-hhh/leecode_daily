# Caps-ac4C模型直接训练使用指南

本文档提供了Caps-ac4C直接训练版本的详细使用说明。

## 快速开始

### 1. 环境配置

```bash
# 进入模型目录
cd caps_ac4c_model

# 安装依赖
pip install -r requirements.txt
```

### 2. 基本使用

最简单的使用方式（使用内置示例数据）：

```bash
python main.py
```

### 3. 使用自定义数据

准备CSV格式的数据文件，包含以下列：
- `sequence`: RNA序列（字符串）
- `label`: 标签（0或1，1表示ac4C位点）

```bash
python main.py --data_path your_data.csv --output_dir results/
```

## 详细参数说明

### 命令行参数

```bash
python main.py [选项]

选项:
  --data_path PATH     数据文件路径（CSV格式）
  --output_dir PATH    输出目录路径（默认：./caps_ac4c_results）
  --log_level LEVEL    日志级别（DEBUG|INFO|WARNING|ERROR）
  --device DEVICE      计算设备（cuda|cpu，自动检测）
```

### 示例用法

```bash
# 使用GPU训练
python main.py --data_path data.csv --device cuda

# 详细日志输出
python main.py --log_level DEBUG --output_dir detailed_results/

# 完整配置
python main.py \
    --data_path /path/to/data.csv \
    --output_dir /path/to/results \
    --log_level INFO \
    --device cuda
```

## 超参数配置

本版本使用固定的经过验证的超参数（无需调整）：

| 参数 | 值 | 说明 |
|------|-----|------|
| CGR分辨率 | 64×64 | 图像编码分辨率 |
| 路由迭代次数 | 3 | 胶囊网络动态路由 |
| 主胶囊数量 | 64 | 主胶囊层数量 |
| 主胶囊维度 | 16 | 主胶囊输出维度 |
| 类型胶囊维度 | 32 | 分类胶囊维度 |
| 学习率 | 0.0007 | 优化器学习率 |
| 批大小 | 32 | 训练批大小 |
| 训练轮数 | 50 | 最大训练轮数 |
| 早停耐心度 | 10 | 早停等待轮数 |

## 输出文件结构

```
results/
├── logs/                               # 训练日志
│   ├── training_YYYYMMDD_HHMMSS.log   # 详细训练日志
│   └── training_history_*.json        # 训练历史数据
├── models/                            # 模型文件
│   └── caps_ac4c_model_*.pth          # 训练好的模型
├── evaluation/                        # 评估结果
│   └── caps_ac4c_direct_report/       # 综合报告
│       ├── training_history.png       # 训练曲线
│       ├── confusion_matrix.png       # 混淆矩阵
│       ├── roc_curve.png             # ROC曲线
│       ├── precision_recall_curve.png # PR曲线
│       ├── capsule_tsne.png          # 胶囊表示可视化
│       ├── cgr_samples.png           # CGR编码样本
│       ├── evaluation_metrics.csv     # 评估指标
│       └── classification_report.txt  # 分类报告
└── final_summary.json                 # 最终结果摘要
```

## 性能指标说明

训练完成后，系统会输出以下评估指标：

- **准确率 (Accuracy)**: 正确预测的比例
- **精确率 (Precision)**: 预测为正例中真正为正例的比例
- **召回率 (Recall)**: 真正例中被正确预测的比例
- **F1分数**: 精确率和召回率的调和平均
- **AUC-ROC**: 受试者工作特征曲线下面积
- **MCC**: 马修斯相关系数

## 可视化结果

系统自动生成多种可视化结果：

1. **训练历史图**: 显示损失和准确率变化
2. **混淆矩阵**: 分类结果统计
3. **ROC曲线**: 真阳性率vs假阳性率
4. **PR曲线**: 精确率vs召回率
5. **t-SNE图**: 胶囊网络学习的特征表示
6. **CGR样本**: DNA序列的二维图像编码

## 常见问题解答

### Q: 内存不足怎么办？
A: 尝试减小批大小或使用CPU模式：
```bash
python main.py --device cpu
```

### Q: 如何使用预训练模型？
A: 可以使用trainer.py中的load_model方法：
```python
from trainer import ModelTrainer
trainer = ModelTrainer()
model = trainer.load_model('path/to/model.pth')
```

### Q: 如何调整训练轮数？
A: 修改trainer.py中的配置：
```python
trainer.config['epochs'] = 100  # 设置为100轮
```

### Q: 数据格式要求是什么？
A: CSV文件需包含两列：
- `sequence`: RNA序列字符串（A, U, G, C）
- `label`: 整数标签（0或1）

### Q: 训练时间过长怎么办？
A: 使用GPU训练或减少数据量进行测试：
```bash
python main.py --device cuda  # 使用GPU
```

## 技术细节

### CGR编码原理
混沌游戏表示法将一维序列转换为二维图像：
- 每个核苷酸对应一个角点
- 当前位置向对应角点移动一半距离
- 统计每个像素的访问频率

### 胶囊网络架构
- **卷积层**: 特征提取（3层）
- **主胶囊**: 局部特征胶囊化
- **动态路由**: 胶囊间的注意机制
- **类型胶囊**: 最终分类输出

### 损失函数
结合边际损失和重构损失：
```
总损失 = 边际损失 + λ × 重构损失
```

## 引用

如果使用本实现，请引用相关论文和本仓库。

## 联系方式

如有问题或建议，请提交Issue或联系开发者。