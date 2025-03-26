; ToDo任务管理器 安装脚本
; 使用InnoSetup创建

#define MyAppName "ToDo任务管理器"
#define MyAppVersion "2.0.0"
#define MyAppPublisher "您的名称或组织"
#define MyAppURL "https://github.com/您的用户名/ToDo_app"
#define MyAppExeName "ToDo_app.exe"
#define MyAppIcoName "appicon.ico"

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
; 如果你有图标文件，取消下面这行的注释并指定正确的路径
;SetupIconFile=E:\QT_app\ToDo_app\icons\{#MyAppIcoName}
Compression=lzma
SolidCompression=yes
WizardStyle=modern
; 创建安装程序到指定目录
OutputDir=E:\QT_app\ToDo_app\installer
OutputBaseFilename=ToDo任务管理器_安装程序
; 管理员权限设置 - 根据需要调整
PrivilegesRequiredOverridesAllowed=dialog
PrivilegesRequired=lowest

[Languages]
Name: "chinesesimplified"; MessagesFile: "compiler:Languages\ChineseSimplified.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 6.1; Check: not IsAdminInstallMode

[Files]
; 主程序文件
Source: "E:\QT_app\ToDo_app\release\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
; 必要的DLL和依赖库
Source: "E:\QT_app\ToDo_app\release\*.dll"; DestDir: "{app}"; Flags: ignoreversion
; Qt平台插件
Source: "E:\QT_app\ToDo_app\release\platforms\*"; DestDir: "{app}\platforms\"; Flags: ignoreversion recursesubdirs createallsubdirs
; Qt样式插件
Source: "E:\QT_app\ToDo_app\release\styles\*"; DestDir: "{app}\styles\"; Flags: ignoreversion recursesubdirs createallsubdirs
; 字体文件
Source: "E:\QT_app\ToDo_app\release\fonts\*"; DestDir: "{app}\fonts\"; Flags: ignoreversion recursesubdirs createallsubdirs
; 图标和资源文件(如果有)
;Source: "E:\QT_app\ToDo_app\release\icons\*"; DestDir: "{app}\icons\"; Flags: ignoreversion recursesubdirs createallsubdirs
; 其他必要的资源文件和目录
Source: "E:\QT_app\ToDo_app\release\imageformats\*"; DestDir: "{app}\imageformats\"; Flags: ignoreversion recursesubdirs createallsubdirs; Check: DirExists('E:\QT_app\ToDo_app\release\imageformats\')
Source: "E:\QT_app\ToDo_app\release\iconengines\*"; DestDir: "{app}\iconengines\"; Flags: ignoreversion recursesubdirs createallsubdirs; Check: DirExists('E:\QT_app\ToDo_app\release\iconengines\')

; 说明: 下面的"Flags: ignoreversion"指令将导致安装程序
; 覆盖任何以前安装的文件的版本

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

; 自定义代码
[Code]
function DirExists(const Dir: string): Boolean;
begin
  Result := DirExists(ExpandConstant(Dir));
end;
