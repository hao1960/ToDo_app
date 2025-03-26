@echo off
echo Qt 应用程序部署工具
echo ===================

set APP_PATH=e:\QT_app\ToDo_app\build\Desktop_Qt_6_8_2_MinGW_64_bit-Release\release
set QT_PATH=E:\Qt\6.8.2\mingw_64

echo 正在部署应用程序...
if not exist "%QT_PATH%\bin\windeployqt.exe" (
    echo 错误: 未找到 windeployqt.exe 工具
    echo 请确认 Qt 安装路径是否正确: %QT_PATH%
    goto :error
)

cd /d %APP_PATH%
echo 正在复制 Qt 依赖项到 %APP_PATH%...
"%QT_PATH%\bin\windeployqt.exe" --release ToDo_app.exe

if %ERRORLEVEL% NEQ 0 (
    echo windeployqt 运行失败，尝试手动复制关键 DLL...
    
    echo 复制核心 Qt DLL...
    copy "%QT_PATH%\bin\Qt6Core.dll" .
    copy "%QT_PATH%\bin\Qt6Gui.dll" .
    copy "%QT_PATH%\bin\Qt6Widgets.dll" .
    copy "%QT_PATH%\bin\libgcc_s_seh-1.dll" .
    copy "%QT_PATH%\bin\libstdc++-6.dll" .
    copy "%QT_PATH%\bin\libwinpthread-1.dll" .
    
    echo 创建并复制插件目录...
    if not exist ".\platforms" mkdir platforms
    copy "%QT_PATH%\plugins\platforms\qwindows.dll" .\platforms\
)

echo.
echo 部署完成！请尝试运行 ToDo_app.exe
echo 如果仍然无法运行，请尝试安装 Visual C++ 运行时库

goto :eof

:error
echo.
echo 部署失败！请检查 Qt 安装路径是否正确。
exit /b 1
