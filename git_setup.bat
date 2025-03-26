@echo off
echo 正在初始化Git仓库...

:: 初始化Git仓库
git init

:: 添加所有文件到暂存区
git add .

:: 创建第一次提交
git commit -m "初始提交：ToDo任务管理应用 v2.0.0"

:: 添加远程仓库 - 需要替换为您的GitHub用户名
git remote add origin https://github.com/YourUsername/todo-app.git

:: 推送到GitHub（您需要输入GitHub账号密码或使用令牌）
echo 准备推送到GitHub...
echo 请输入您的GitHub用户名和密码或使用令牌进行认证
git push -u origin master

echo 完成！
pause 