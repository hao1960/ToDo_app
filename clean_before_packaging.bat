@echo off
echo 清理任务数据文件，准备打包...

REM 删除已有的任务数据文件
del /q "release\tasks_*.json" 2>nul
del /q "build\Desktop_Qt_*\release\tasks_*.json" 2>nul

REM 删除用户设置文件(如果存在)
del /q "%APPDATA%\Your Organization\ToDo_App\ToDo_App.ini" 2>nul

echo 清理完成！现在可以创建安装包了。
pause
