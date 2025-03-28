; ToDo任务管理器 安装脚本
; 使用InnoSetup创建

#define MyAppName "ToDo任务管理器"
#define MyAppVersion "2.0.3"
#define MyAppPublisher "您的名称或组织"
#define MyAppURL "https://github.com/您的用户名/ToDo_app"
#define MyAppExeName "ToDo_app.exe"
#define MyAppIcoName "todolist.ico"

[Setup]
; 注意: AppId的值为唯一标识此应用程序
; 不要在其他安装程序中使用相同的AppId值
AppId={{8A3849C4-7B52-440B-BD22-8436FC52A4FB}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
; 启用图标设置
SetupIconFile=..\icons\{#MyAppIcoName}
UninstallDisplayIcon={app}\{#MyAppExeName}
Compression=lzma
SolidCompression=yes
WizardStyle=modern
; 创建安装程序到指定目录
OutputDir=E:\QT_app\ToDo_app\installer
OutputBaseFilename=ToDo任务管理器_安装程序
; 管理员权限设置 - 根据需要调整
PrivilegesRequiredOverridesAllowed=dialog
PrivilegesRequired=lowest
; 确保显示安装目录选择页面
DisableDirPage=no
AppendDefaultDirName=yes
DirExistsWarning=yes

[Languages]
Name: "chinese"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "创建桌面图标"; GroupDescription: "附加图标:"; Flags: unchecked
Name: "quicklaunchicon"; Description: "创建快速启动图标"; GroupDescription: "附加图标:"; Flags: unchecked; OnlyBelowVersion: 6.1; Check: not IsAdminInstallMode

[Files]
; 主程序文件
Source: "E:\QT_app\ToDo_app\release\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
; 必要的DLL和依赖库
Source: "E:\QT_app\ToDo_app\build\Desktop_Qt_6_8_2_MinGW_64_bit-Release\release\*.dll"; DestDir: "{app}"; Flags: ignoreversion
; Qt平台插件
Source: "E:\QT_app\ToDo_app\build\Desktop_Qt_6_8_2_MinGW_64_bit-Release\release\platforms\*"; DestDir: "{app}\platforms\"; Flags: ignoreversion recursesubdirs createallsubdirs
; Qt样式插件
Source: "E:\QT_app\ToDo_app\build\Desktop_Qt_6_8_2_MinGW_64_bit-Release\release\styles\*"; DestDir: "{app}\styles\"; Flags: ignoreversion recursesubdirs createallsubdirs
; 字体文件
Source: "E:\QT_app\ToDo_app\fonts\*"; DestDir: "{app}\fonts\"; Flags: ignoreversion recursesubdirs createallsubdirs
; 图标文件 - 确保图标也被复制到安装目录
Source: "E:\QT_app\ToDo_app\icons\{#MyAppIcoName}"; DestDir: "{app}"; Flags: ignoreversion
; 其他必要的资源文件和目录
Source: "E:\QT_app\ToDo_app\build\Desktop_Qt_6_8_2_MinGW_64_bit-Release\release\imageformats\*"; DestDir: "{app}\imageformats\"; Flags: ignoreversion recursesubdirs createallsubdirs; Check: DirExists('E:\QT_app\ToDo_app\release\imageformats\')
Source: "E:\QT_app\ToDo_app\build\Desktop_Qt_6_8_2_MinGW_64_bit-Release\release\iconengines\*"; DestDir: "{app}\iconengines\"; Flags: ignoreversion recursesubdirs createallsubdirs; Check: DirExists('E:\QT_app\ToDo_app\release\iconengines\')

; 注意：不要包含任何 tasks_*.json 文件，确保新安装的程序使用默认初始化过程

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\{#MyAppIcoName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\{#MyAppIcoName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\{#MyAppIcoName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

; 自定义代码
[Code]
function DirExists(const Dir: string): Boolean;
begin
  Result := DirExists(ExpandConstant(Dir));
end;
