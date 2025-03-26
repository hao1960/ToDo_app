# ToDo 任务列表应用

<div align="center">
<img src="icons/appicon.png" alt="ToDo应用图标" width="128"/>
  
[![Release](https://img.shields.io/github/v/release/YourUsername/todo-app)](https://github.com/YourUsername/todo-app/releases)
[![License](https://img.shields.io/github/license/YourUsername/todo-app)](LICENSE)
</div>

## 项目概述

ToDo 任务列表是一个使用 Qt 框架开发的桌面应用程序，旨在帮助用户管理日常任务。该应用提供了直观的用户界面，允许用户添加、编辑、删除和标记任务，以及搜索和过滤任务列表。

![应用截图](screenshots/main.png)

## 功能特点

- ✅ **任务管理**：添加、编辑和删除任务
- ✅ **任务状态**：标记任务为已完成或未完成
- 🔍 **实时搜索功能**：输入关键词时即时过滤显示匹配的任务
- 🔖 **任务分类**：支持创建多个任务分类，更好地组织不同类型的任务
- 🎨 **智能背景**：支持自定义背景图片，自动检测暗色图片并提供提亮处理
- 💾 **数据持久化**：自动保存任务数据，应用重启后保持任务状态

## 下载安装

### Windows

从[Releases页面](https://github.com/YourUsername/todo-app/releases)下载最新的安装包`ToDo任务管理器_Setup.exe`，双击运行即可完成安装。

### 从源码构建

1. 克隆仓库
   ```
   git clone https://github.com/YourUsername/todo-app.git
   cd todo-app
   ```

2. 使用Qt Creator打开`ToDo_app.pro`文件并构建项目

## 使用方法

### 添加任务

1. 在"任务"输入框中输入任务内容（可包含多行文本和缩进）
2. 点击"添加"按钮或直接按Ctrl+Enter键
3. 任务将添加到当前选中的分类中

### 编辑任务

1. 双击需要编辑的任务
2. 在弹出的对话框中修改任务内容
3. 点击"确定"保存修改

### 标记任务完成/未完成

- 点击任务前的复选框可切换任务状态
- 已完成的任务会显示为灰色并带有删除线

### 设置背景图片

- 点击界面上方的"设置背景"按钮
- 在文件对话框中选择本地图片文件
- 如果选择的图片较暗，系统会询问是否自动提亮图片以增强可读性

## 技术架构

- **开发框架**：Qt 5/6
- **编程语言**：C++
- **数据存储**：JSON 文件格式
- **用户界面**：Qt Widgets布局管理器
- **图标库**：FontAwesome 4.7.0

## 贡献指南

欢迎对本项目进行贡献！请按以下步骤操作：

1. Fork本仓库
2. 创建您的特性分支 (`git checkout -b feature/amazing-feature`)
3. 提交您的更改 (`git commit -m '添加了一些很棒的功能'`)
4. 推送到分支 (`git push origin feature/amazing-feature`)
5. 开启一个Pull Request

## 许可证

本项目采用MIT许可证 - 查看[LICENSE](LICENSE)文件了解详情

## 联系方式

如有问题或建议，欢迎在Issues中提出，或通过以下方式联系我：

- GitHub Issues: [https://github.com/YourUsername/todo-app/issues](https://github.com/YourUsername/todo-app/issues)
- Email: your-email@example.com (可选)

## 致谢

- [Qt框架](https://www.qt.io/)
- [FontAwesome](https://fontawesome.com/)
- 所有贡献者和用户 