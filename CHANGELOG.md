# 更新日志

所有对本项目的显著更改都将记录在此文件中。

## [2.0.3] - 2025-03-28

* 增加可选背景色
* 移除背景蒙版

### 改进

- 优化数据存储路径，提升数据管理的可靠性和安全性

## [2.0.0] - 2023-03-26

### 新增

- 添加智能背景图片处理功能，自动检测暗色图片并提供提亮选项
- 增加任务分类功能，支持创建和管理多个任务分类
- 添加标签页管理任务分类的功能
- 实现任务状态可视化（已完成任务使用删除线和灰色显示）
- 未完成任务使用粗体增强可见性
- 添加新任务时的"闪烁"效果提供良好的视觉反馈

### 改进

- 优化界面元素，增强在各种背景下的可见性
- 重新设计按钮和输入框样式，添加深色边框增强对比度
- 为标签添加半透明背景，确保在任何背景下都清晰可见
- 优化编辑对话框，确保在背景图片上的清晰可见性
- 增强搜索功能，支持实时搜索结果显示
- 优化多行文本支持，使任务描述更加丰富和结构化
- 任务列表使用半透明样式，保证在有背景图片时仍然清晰可读

### 修复

- 修复了编辑对话框中文字不显示的问题
- 修复了某些情况下无法保存任务的bug
- 改进字体加载机制，确保FontAwesome图标正确显示
- 解决了在高DPI显示器上的缩放问题

## [1.0.0] - 2023-01-15

### 初始版本发布

- 实现基本的任务添加、编辑、删除和完成状态管理
- 添加搜索和过滤功能
- 实现数据持久化存储
