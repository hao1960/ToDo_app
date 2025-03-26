# ToDo 任务列表应用

## 项目概述

ToDo 任务列表是一个使用 Qt 框架开发的桌面应用程序，旨在帮助用户管理日常任务。该应用提供了直观的用户界面，允许用户添加、编辑、删除和标记任务，以及搜索和过滤任务列表。

## 功能特点

- **任务管理**：添加、编辑和删除任务
- **任务状态**：标记任务为已完成或未完成
- **实时搜索功能**：输入关键词时即时过滤显示匹配的任务，也可按回车键进行搜索
- **过滤功能**：按完成状态筛选任务（全部、未完成、已完成）
- **数据持久化**：自动保存任务数据，应用重启后保持任务状态
- **用户友好界面**：清晰的布局和简单的操作流程
- **响应式设计**：界面会随窗口大小变化自动调整布局
- **快捷输入**：在任务输入框按Ctrl+Enter键即可快速添加任务
- **格式化文本**：支持输入和保存包含换行和缩进的多行文本
- **智能背景**：支持自定义背景图片，自动检测暗色图片并提供提亮处理，确保文字在任何背景下清晰可见
- **任务分类**：支持创建多个任务分类，更好地组织不同类型的任务
- **高对比度UI**：确保界面元素在各种背景图片下都保持清晰可见

## 技术架构

- **开发框架**：Qt 5/6
- **编程语言**：C++
- **数据存储**：JSON 文件格式
- **用户界面**：Qt Widgets 布局管理器
- **设置存储**：QSettings 用于保存用户配置
- **图标库**：FontAwesome 4.7.0

## 如何使用

### 添加任务

1. 在"任务"输入框中输入任务内容（可包含多行文本和缩进）
2. 点击"添加"按钮或直接按Ctrl+Enter键
3. 任务将添加到当前选中的分类中

### 编辑任务

1. 双击需要编辑的任务
2. 在弹出的对话框中修改任务内容（支持多行编辑）
3. 点击"确定"保存修改

### 删除任务

1. 单击选择要删除的任务
2. 点击"删除"按钮

### 标记任务完成/未完成

- 点击任务前的复选框可切换任务状态
- 已完成的任务会显示为灰色并带有删除线

### 搜索任务

- 在"搜索"输入框中输入关键词
- 应用会实时过滤显示匹配的任务
- 也可以按回车键确认搜索
- 搜索功能会在所有分类中查找匹配的任务

### 过滤任务

- 使用"过滤"下拉菜单选择要显示的任务类型（所有、未完成、已完成）
- 过滤功能会作用于所有分类的任务

### 设置背景图片

- 点击界面上方的"设置背景"按钮
- 在文件对话框中选择本地图片文件
- 图片将被设置为应用的背景
- 如果选择的图片较暗，系统会询问是否自动提亮图片以增强可读性
- 背景设置会自动保存，下次启动应用时会自动加载
- 可随时点击"恢复默认背景"按钮返回默认渐变背景

### 管理任务分类

1. **创建新分类**:

   - 点击界面顶部的"+"按钮
   - 在弹出的对话框中输入分类名称
   - 点击"确定"创建新分类
2. **切换分类**:

   - 点击顶部的分类标签可以在不同分类之间切换
   - 每个分类都有独立的任务列表
3. **任务存储**:

   - 每个分类的任务都会单独保存
   - 切换分类后，添加、编辑或删除的任务只会影响当前分类

## 系统要求

- 操作系统：Windows、macOS 或 Linux
- 需要安装 Qt 运行库

## 开发环境

- Cursor+Claude3.7
- Qt Creator
- C++17 及以上
- Qt 5.12 及以上版本

## 项目结构

- `main.cpp`：应用程序入口
- `mainwindow.h/cpp`：主窗口类定义和实现
- `mainwindow.ui`：用户界面设计文件
- `ToDo_app.pro`：项目配置文件
- `tasks_分类名.json`：各个分类的任务数据存储文件

## 界面改进

- 增加了输入框的提示文本，以便用户更容易理解每个输入框的用途
- 为搜索和过滤功能添加了标签，使界面更直观
- 移除了多余的搜索按钮，采用实时搜索提高用户体验
- 使用布局管理器代替固定几何布局，使界面元素能够随窗口大小变化而自动调整
- 添加了回车键快捷添加任务功能，提高用户输入效率
- 为搜索框添加了回车键确认搜索功能，增强用户交互体验
- 实现多行文本输入和格式保留，使任务描述更加丰富和结构化
- 添加了自定义背景图片功能，使界面更加个性化和美观
- 智能背景处理系统自动检测暗色图片并提供提亮选项，确保最佳视觉体验
- 增强标签和文本对比度，确保在各种背景图片下都清晰可见
- 为所有按钮和输入框添加深色边框和半透明背景，增强在背景图片上的可见性
- 任务列表使用半透明样式，保证在有背景图片时仍然清晰可读
- 使用标签页实现任务分类，让用户可以更好地组织不同类型的任务

## 高级功能

1. **智能背景处理**：

   - 自动检测暗色背景图片
   - 提供智能提亮功能，优化文字可见性
   - 半透明背景适配，确保界面元素在任何背景下都清晰可见
   - 可随时在自定义背景和默认渐变背景之间切换
2. **视觉增强**：

   - 任务完成状态可视化（已完成任务使用删除线和灰色显示）
   - 未完成任务使用粗体增强可见性
   - 标签背景半透明处理，确保在各种背景下的可读性
   - 新增任务时的"闪烁"效果提供良好的视觉反馈
3. **数据持久化**：所有任务数据保存在JSON文件中
4. **多行任务**：支持多行文本的任务描述
5. **设置保存**：应用设置（如背景图片）会被保存并在下次启动时恢复
6. **任务分类**：可以创建多个分类来组织不同的任务列表

## 数据存储

### 任务数据

应用将各个分类的任务数据分别保存在对应的JSON文件中，格式为：

```json
{
  "tasks": [
    {
      "task": "任务内容（可包含换行和缩进格式）",
      "completed": true/false
    },
    ...
  ]
}
```

### 分类数据

分类信息使用QSettings存储，保存分类的名称列表。

### 设置数据

用户设置（如背景图片路径）使用 Qt 的 QSettings 存储，保证应用重启后仍能保持用户的偏好设置。

## 联系信息

如有问题或建议，请联系[开发者邮箱]。

## 许可证

[在此添加许可证信息]

## 如何安装Font Awesome

1. **下载Font Awesome 4.7.0**

   - 从 https://fontawesome.com/v4.7.0/assets/font-awesome-4.7.0.zip 下载
   - 或访问 https://github.com/FortAwesome/Font-Awesome/tree/v4.7.0
2. **安装字体文件**

   - 将下载的包中的 `fonts/fontawesome-webfont.ttf` 文件复制到项目的 `fonts/` 目录
3. **重新编译项目**

   - 项目已包含必要的 `FontHelper` 类和资源配置
   - 重新运行 qmake 然后构建项目

## 背景图片增强功能详解

### 智能检测与提亮

应用能够自动检测用户选择的背景图片是否偏暗。如果图片整体亮度值低于阈值，系统会询问用户是否需要自动提亮处理：

1. **亮度检测算法**：

   - 采用广泛接受的亮度公式：亮度 = 0.299*R + 0.587*G + 0.114*B
   - 通过采样分析图片的平均亮度
   - 对于亮度值低于128（中间值）的图片判定为"偏暗"
2. **智能提亮处理**：

   - 默认提供30%的亮度增强
   - 保持图片色调不变的同时提高亮度
   - 用户可选择是否应用此处理

### 界面元素适配

为确保在任何背景下都能保持良好的用户体验，系统针对各界面元素进行了优化：

1. **标签增强**：

   - 所有文本标签添加半透明白色背景
   - 使用深青色文字和粗体样式增强可读性
   - 添加圆角和边距使界面更美观
2. **按钮可见性增强**：

   - 每种按钮使用不同颜色区分功能：添加(薄荷绿)、删除(珊瑚色)、设置(橙色)等
   - 添加深色边框增强边界可见性
   - 悬停效果使用深色变体提供清晰的用户反馈
3. **输入框优化**：

   - 使用半透明背景与薄荷绿色边框
   - 聚焦时自动切换到纯白背景增强可读性
   - 粗体文字和深色文本确保在任何背景下都清晰可见
4. **任务列表适配**：

   - 增加列表背景不透明度确保内容可见
   - 未完成任务使用粗体增强可读性
   - 已完成任务使用删除线和柔和颜色提供明确的状态区分

## 版本更新历史

### v2.0.0 (当前版本)

- 添加智能背景图片处理功能，自动检测暗色图片并提供提亮选项
- 优化界面元素，增强在各种背景下的可见性
- 重新设计按钮和输入框样式，添加深色边框增强对比度
- 为标签添加半透明背景，确保在任何背景下都清晰可见
- 任务文本使用粗体显示，增强可读性
- 优化编辑对话框，确保在背景图片上的清晰可见性
- 添加新任务时的视觉反馈效果

### v1.5.0

- 添加任务分类功能，支持创建和管理多个任务分类
- 实现基本的背景图片功能
- 使用FontAwesome添加图标支持
- 优化任务编辑对话框，支持多行文本编辑

### v1.0.0

- 初始版本发布
- 实现基本的任务添加、编辑、删除和完成状态管理
- 添加搜索和过滤功能
- 数据持久化存储

## 使用的图标

应用程序使用以下FontAwesome图标：

- 添加任务 (FA_PLUS)
- 删除任务 (FA_TRASH)
- 编辑任务 (FA_PENCIL)
- 搜索 (FA_SEARCH)
- 过滤 (FA_FILTER)
- 设置背景 (FA_IMAGE)
- 任务列表 (FA_LIST)

## 应用程序打包指南

要将ToDo应用打包成可分发的软件，可以按照以下步骤操作：

### Windows平台打包

#### 1. 使用Qt Creator内置部署工具

1. **编译Release版本**：

   - 在Qt Creator中选择"Release"配置
   - 构建项目(Ctrl+B)
2. **使用windeployqt工具**：

   - 打开Qt命令提示符(Qt Command Prompt)
   - 导航到项目的build目录
   - 运行以下命令：
     ```
     windeployqt --release ToDo_app.exe
     ```
3. **创建安装程序(可选)**：

   - 安装Qt Installer Framework
   - 创建配置文件和包信息
   - 使用binarycreator工具创建安装程序

#### 2. 使用InnoSetup创建安装包

1. **下载并安装InnoSetup**：

   - 从 https://jrsoftware.org/isinfo.php 下载InnoSetup
   - 按照安装向导完成安装
2. **创建安装脚本**：

   - 运行InnoSetup脚本向导
   - 设置应用程序信息、文件、快捷方式等
   - 指定需要包含的文件(应用程序可执行文件和DLL)
   - 生成安装脚本(.iss文件)
3. **编译安装程序**：

   - 在InnoSetup中编译脚本
   - 生成的安装程序(.exe)可用于分发

#### 3. 使用NSIS创建安装包

NSIS (Nullsoft Scriptable Install System) 是功能更丰富的安装包制作工具，特别适合需要更多自定义选项的应用。

1. **下载并安装NSIS**：

   - 从 https://nsis.sourceforge.io/Download 下载NSIS
   - 按照安装向导完成安装
2. **创建NSIS脚本**：

   - 使用NSIS脚本编辑器或文本编辑器创建.nsi脚本
   - 设置应用信息、安装路径、打包文件等
3. **使用NSIS脚本向导(可选)**：

   - 运行NSIS提供的脚本向导简化脚本创建过程
   - 根据向导生成基本脚本后进行自定义修改
4. **编译NSIS脚本**：

   - 右键点击.nsi脚本文件，选择"Compile NSIS Script"
   - 生成的安装程序(.exe)可用于分发
5. **高级功能**：

   - 添加卸载功能
   - 添加自定义安装页面
   - 添加多语言支持
   - 添加注册表操作

示例NSIS脚本(.nsi)：

```nsi
!include "MUI2.nsh"

; 基本信息
Name "ToDo任务管理器"
OutFile "ToDo任务管理器_Setup.exe"
InstallDir "$PROGRAMFILES\ToDo任务管理器"
InstallDirRegKey HKCU "Software\ToDo任务管理器" ""

; 界面设置
!define MUI_ABORTWARNING
!define MUI_ICON "appicon.ico"
!define MUI_UNICON "appicon.ico"

; 安装页面
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "license.txt"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

; 卸载页面
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

; 语言
!insertmacro MUI_LANGUAGE "SimpChinese"

Section "主程序" SecMain
  SetOutPath "$INSTDIR"
  
  ; 添加文件
  File "release\ToDo_app.exe"
  File /r "release\*.dll"
  File /r "release\platforms"
  File /r "release\styles"
  File /r "release\fonts"
  
  ; 创建快捷方式
  CreateDirectory "$SMPROGRAMS\ToDo任务管理器"
  CreateShortcut "$SMPROGRAMS\ToDo任务管理器\ToDo任务管理器.lnk" "$INSTDIR\ToDo_app.exe"
  CreateShortcut "$DESKTOP\ToDo任务管理器.lnk" "$INSTDIR\ToDo_app.exe"
  
  ; 写入卸载信息到注册表
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ToDo任务管理器" "DisplayName" "ToDo任务管理器"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ToDo任务管理器" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ToDo任务管理器" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ToDo任务管理器" "NoRepair" 1
  WriteUninstaller "$INSTDIR\uninstall.exe"
SectionEnd

Section "Uninstall"
  ; 删除文件和目录
  Delete "$INSTDIR\ToDo_app.exe"
  Delete "$INSTDIR\*.dll"
  RMDir /r "$INSTDIR\platforms"
  RMDir /r "$INSTDIR\styles"
  RMDir /r "$INSTDIR\fonts"
  Delete "$INSTDIR\uninstall.exe"
  RMDir "$INSTDIR"
  
  ; 删除快捷方式
  Delete "$SMPROGRAMS\ToDo任务管理器\ToDo任务管理器.lnk"
  RMDir "$SMPROGRAMS\ToDo任务管理器"
  Delete "$DESKTOP\ToDo任务管理器.lnk"
  
  ; 删除注册表项
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ToDo任务管理器"
SectionEnd
```

### macOS平台打包

1. **创建应用程序包(App Bundle)**：

   - 在Qt Creator中选择"Release"配置
   - 构建项目
2. **使用macdeployqt工具**：

   - 打开终端
   - 导航到项目的build目录
   - 运行以下命令：
     ```
     macdeployqt ToDo_app.app -dmg
     ```
   - 这将创建一个包含所有必要依赖的.app包和.dmg磁盘映像文件

### Linux平台打包

1. **使用linuxdeployqt工具**：

   - 安装linuxdeployqt(https://github.com/probonopd/linuxdeployqt)
   - 构建Release版本
   - 运行linuxdeployqt生成AppImage
2. **创建Debian/Ubuntu包**：

   - 安装必要的打包工具：
     ```
     sudo apt-get install build-essential debhelper
     ```
   - 创建debian目录和控制文件
   - 运行dpkg-buildpackage命令构建.deb包
3. **创建RPM包(Fedora/RHEL)**：

   - 安装rpm-build包
   - 创建.spec文件
   - 运行rpmbuild命令构建.rpm包

### 通用打包注意事项

1. **包含所有依赖项**：

   - 确保应用程序包含所有必要的Qt库
   - 包含使用的字体文件(FontAwesome)
   - 包含SSL库(如果使用网络功能)
2. **静态链接(可选)**：

   - 在.pro文件中添加 `CONFIG += static` 选项
   - 重新编译项目以静态链接Qt库
   - 这会增加可执行文件大小，但减少依赖
3. **测试打包的应用**：

   - 在没有安装Qt的"干净"系统上测试应用
   - 确认所有功能正常运行
   - 检查所有资源(图标、字体等)是否正确加载
4. **数据文件位置**：

   - 确保应用正确访问用户数据目录
   - 在Windows上通常是 `%APPDATA%\ToDo_App`
   - 在macOS上通常是 `~/Library/Application Support/ToDo_App`
   - 在Linux上通常是 `~/.local/share/ToDo_App`
5. **版本信息与图标**：

   - 在.pro文件中添加版本信息
   - 确保应用有适当的图标文件(.ico, .icns, .png)
   - 在资源文件中引用图标

### 应用图标制作

为了让应用在不同平台上都能显示专业的图标，需要为各个平台准备不同格式的图标文件：

1. **Windows图标(.ico)**：

   - 创建16x16, 32x32, 48x48, 64x64, 128x128和256x256像素的图标
   - 使用图标编辑工具如IcoFX, Axialis IconWorkshop或在线转换工具
   - 保存为.ico格式
   - 在应用.pro文件中添加：
     ```
     RC_ICONS = appicon.ico
     ```
2. **macOS图标(.icns)**：

   - 创建16x16, 32x32, 64x64, 128x128, 256x256, 512x512和1024x1024像素的图标
   - 使用macOS的Icon Composer或iconutil命令行工具
   - 保存为.icns格式
   - 在应用.pro文件中添加：
     ```
     ICON = appicon.icns
     ```
3. **Linux/通用图标(.png)**：

   - 创建多个尺寸(16x16到512x512)的PNG格式图标
   - 在.desktop文件中引用图标
   - 在应用.pro文件中添加：
     ```
     unix {
         icon.files = appicon.png
         icon.path = /usr/share/icons/hicolor/512x512/apps/
         INSTALLS += icon
     }
     ```

### 发布前的准备工作

在打包并发布应用前，确保完成以下准备工作：

1. **更新版本号**：

   - 在.pro文件中更新VERSION宏：
     ```
     VERSION = 2.0.0
     DEFINES += APP_VERSION=\\\"$$VERSION\\\"
     ```
   - 在代码中使用APP_VERSION宏显示版本信息
2. **添加应用元数据**：

   - 在.pro文件中添加公司信息和应用描述：
     ```
     QMAKE_TARGET_COMPANY = "您的公司名称"
     QMAKE_TARGET_PRODUCT = "ToDo任务管理器"
     QMAKE_TARGET_DESCRIPTION = "一个简单且功能强大的任务管理应用"
     QMAKE_TARGET_COPYRIGHT = "版权所有 (C) 2023"
     ```
3. **清理项目**：

   - 移除所有调试代码和打印语句
   - 执行静态代码分析确保代码质量
   - 运行内存检查工具(如Valgrind)检测内存泄漏
4. **优化应用大小**：

   - 使用Qt的资源系统优化资源文件
   - 考虑移除不必要的Qt模块
   - 在.pro文件中添加：
     ```
     QMAKE_CXXFLAGS_RELEASE += -O3
     ```
5. **完善文档**：

   - 更新用户手册和README文件
   - 创建变更日志(CHANGELOG)
   - 准备安装说明

示例InnoSetup脚本(.iss)：

```
[Setup]
AppName=ToDo任务管理器
AppVersion=2.0.0
DefaultDirName={pf}\ToDo任务管理器
DefaultGroupName=ToDo任务管理器
OutputDir=.
OutputBaseFilename=ToDo任务管理器_安装程序
Compression=lzma
SolidCompression=yes

[Files]
Source: "E:\QT_app\ToDo_app\build\release\ToDo_app.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\QT_app\ToDo_app\build\release\*.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\QT_app\ToDo_app\build\release\platforms\*"; DestDir: "{app}\platforms\"; Flags: ignoreversion recursesubdirs
Source: "E:\QT_app\ToDo_app\build\release\styles\*"; DestDir: "{app}\styles\"; Flags: ignoreversion recursesubdirs
Source: "E:\QT_app\ToDo_app\build\release\fonts\*"; DestDir: "{app}\fonts\"; Flags: ignoreversion recursesubdirs

[Icons]
Name: "{group}\ToDo任务管理器"; Filename: "{app}\ToDo_app.exe"
Name: "{commondesktop}\ToDo任务管理器"; Filename: "{app}\ToDo_app.exe"

[Run]
Filename: "{app}\ToDo_app.exe"; Description: "立即运行应用"; Flags: nowait postinstall skipifsilent
```

## 扩展功能

1. **数据持久化**：所有任务数据保存在JSON文件中
2. **多行任务**：支持多行文本的任务描述
3. **设置保存**：应用设置（如背景图片）会被保存并在下次启动时恢复
4. **任务分类**：可以创建多个分类来组织不同的任务列表

## 实现自动更新功能

要为应用添加自动更新功能，可以按照以下步骤实现：

1. **创建更新服务器**：

   - 搭建一个Web服务器或使用现有云服务
   - 创建版本信息JSON文件，例如：
     ```json
     {
       "version": "2.0.0",
       "url": "https://your-server.com/downloads/ToDo_app_2.0.0.exe",
       "releaseNotes": "新功能：\n1. 智能背景处理\n2. 界面元素适配优化\n3. 修复了若干bug",
       "mandatory": false
     }
     ```
2. **在应用中添加更新检查功能**：

   - 使用Qt的网络模块(QNetworkAccessManager)检查更新服务器
   - 比较服务器版本与本地版本
   - 提示用户可用更新并提供下载选项
3. **Qt Creator中实现自动更新**：

   - 在项目中添加新的类(如UpdateChecker)
   - 在mainwindow.cpp中添加检查更新代码
   - 提供用户自定义更新检查间隔选项
4. **简单实现示例**：

   ```cpp
   // updatechecker.h
   class UpdateChecker : public QObject {
       Q_OBJECT

   public:
       explicit UpdateChecker(QObject *parent = nullptr);
       void checkForUpdates();

   signals:
       void updateAvailable(const QString &version, const QString &url, const QString &notes);
       void noUpdateAvailable();
       void checkFailed(const QString &error);

   private slots:
       void onNetworkReply(QNetworkReply *reply);

   private:
       QNetworkAccessManager *manager;
       QString currentVersion;
   };

   // updatechecker.cpp (简化版本)
   void UpdateChecker::checkForUpdates() {
       QNetworkRequest request(QUrl("https://your-server.com/updates.json"));
       manager->get(request);
   }

   void UpdateChecker::onNetworkReply(QNetworkReply *reply) {
       if (reply->error() == QNetworkReply::NoError) {
           QByteArray data = reply->readAll();
           QJsonDocument document = QJsonDocument::fromJson(data);
           QJsonObject object = document.object();

           QString serverVersion = object["version"].toString();

           if (compareVersions(serverVersion, currentVersion) > 0) {
               emit updateAvailable(
                   serverVersion,
                   object["url"].toString(),
                   object["releaseNotes"].toString()
               );
           } else {
               emit noUpdateAvailable();
           }
       } else {
           emit checkFailed(reply->errorString());
       }

       reply->deleteLater();
   }
   ```
5. **安全注意事项**：

   - 使用HTTPS确保更新信息传输安全
   - 考虑对更新包进行数字签名
   - 验证下载文件的完整性(如使用校验和)

通过实现自动更新功能，您可以确保用户始终使用最新版本的应用，并方便地获取新功能和错误修复。

## 应用程序数字签名

为确保用户下载和使用的是来自可信来源的软件，对应用程序进行数字签名是非常重要的步骤，尤其是在分发Windows应用时。

### Windows应用程序签名

1. **获取代码签名证书**：

   - 从可信证书颁发机构(CA)购买代码签名证书，如DigiCert、Comodo、GlobalSign等
   - 或者为开发测试创建自签名证书(不推荐用于生产)
2. **使用Microsoft SignTool进行签名**：

   - 安装Windows SDK获取SignTool工具
   - 运行以下命令对可执行文件进行签名：
     ```
     signtool sign /f YourCertificate.pfx /p YourPassword /t http://timestamp.digicert.com /d "ToDo任务管理器" ToDo_app.exe
     ```
   - 时间戳服务器(/t参数)确保签名在证书过期后仍然有效
3. **验证签名**：

   - 使用以下命令验证签名是否成功：
     ```
     signtool verify /pa ToDo_app.exe
     ```

### macOS应用程序签名

1. **获取Apple开发者证书**：

   - 加入Apple开发者计划
   - 在Apple开发者网站上创建证书签名请求
   - 下载开发者证书到密钥链
2. **使用codesign对应用进行签名**：

   - 运行以下命令：
     ```
     codesign --force --options runtime --sign "Developer ID Application: Your Name (TeamID)" ToDo_app.app
     ```
3. **创建公证(Notarization)**：

   - 使用Apple的公证服务确保应用被macOS认可为可信：
     ```
     xcrun altool --notarize-app --primary-bundle-id "com.yourcompany.todo-app" --username "apple@id.com" --password "app-specific-password" --file ToDo_app.dmg
     ```

### Linux应用程序签名

1. **创建GPG密钥**：

   - 使用GPG生成密钥对
   - 发布公钥到密钥服务器
2. **签名应用包**：

   - 对.deb或.rpm包进行签名：
     ```
     dpkg-sig --sign builder package.deb  # 对Debian包签名
     rpm --addsign package.rpm           # 对RPM包签名
     ```
3. **验证签名**：

   - 安装时验证签名确保包的完整性

## 安全分发注意事项

在分发应用时，遵循以下安全最佳实践：

1. **HTTPS下载**：

   - 确保所有下载链接使用HTTPS协议
   - 配置服务器使用强加密套件和TLS 1.3
2. **提供校验和**：

   - 为每个下载提供SHA-256校验和
   - 说明如何验证下载文件的完整性
3. **透明的更新机制**：

   - 清晰说明更新内容
   - 允许用户选择是否安装更新(除关键安全更新外)
   - 提供更新历史记录
4. **隐私政策与权限**：

   - 提供清晰的隐私政策说明应用收集的数据
   - 仅请求必要的系统权限
   - 遵守GDPR等数据保护法规
5. **在安装程序中提供信息**：

   - 包含许可协议
   - 明确说明应用功能
   - 提供联系信息以报告问题

实施这些安全措施不仅能保护用户，也能提升应用的专业形象和可信度。

## 打包清单

在最终发布应用前，使用以下清单确保打包过程完整：

- [ ] 更新版本号和发布说明
- [ ] 构建Release版本并进行全面测试
- [ ] 使用部署工具收集所有依赖(windeployqt/macdeployqt)
- [ ] 对应用进行数字签名
- [ ] 创建安装程序并进行测试
- [ ] 在"干净"系统上验证安装和运行
- [ ] 准备下载页面和文档
- [ ] 设置更新服务器(如使用自动更新)
- [ ] 创建校验和并验证下载文件
- [ ] 备份源代码和发布文件

# ToDo 应用

一个使用Qt开发的简单ToDo任务管理桌面应用。

## 功能特点

- 添加、编辑和删除任务
- 标记任务为已完成
- 简洁易用的界面
- 数据本地存储

## 安装方法

1. 下载最新的安装包 `ToDo_app_setup.exe`
2. 运行安装程序并按照提示进行安装
3. 安装完成后，可以从桌面或开始菜单启动应用

## 开发环境

- Qt 5.12+
- MinGW 或 MSVC 编译器
- Windows 10/11 系统

## 构建方法

```bash
qmake ToDo_app.pro
make (或 mingw32-make / nmake，根据你的编译器)
```

## 打包方法

使用Inno Setup运行 `installer/ToDo_app_setup.iss` 可创建安装程序。

## 许可证

[MIT License](LICENSE)
