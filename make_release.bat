@echo off
echo 正在构建ToDo应用发布版本...

:: 清理旧的构建文件
echo 清理旧的构建文件...
if exist build\release (
    rd /s /q build\release
)
mkdir build\release

:: 设置Qt环境变量
set QTDIR=E:\Qt\6.8.2\mingw_64
set MINGWDIR=E:\Qt\Tools\mingw1310_64
set PATH=%QTDIR%\bin;%MINGWDIR%\bin;%PATH%

:: 确保在正确的目录中
cd /d %~dp0

:: 运行qmake
echo 正在运行qmake...
qmake -spec win32-g++ "CONFIG+=release"

:: 运行make clean和make
echo 正在清理和编译应用...
mingw32-make clean
mingw32-make -j4

:: 检查编译是否成功
if not exist build\release\ToDo_app.exe (
    echo 错误：编译失败，未生成ToDo_app.exe
    pause
    exit /b 1
)

:: 运行windeployqt收集依赖
echo 正在收集依赖...
cd build\release
windeployqt --release ToDo_app.exe

:: 复制MinGW运行时库
echo 正在复制MinGW运行时库...
copy "%MINGWDIR%\bin\libgcc_s_seh-1.dll" .
copy "%MINGWDIR%\bin\libstdc++-6.dll" .
copy "%MINGWDIR%\bin\libwinpthread-1.dll" .
cd ..\..

echo 完成!
echo 应用程序已构建在build\release目录中
echo 可以使用InnoSetup编译installer\ToDo_app_setup.iss文件创建安装程序
pause