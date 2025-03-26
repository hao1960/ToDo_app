@echo off
echo 正在创建发布标签...

:: 创建发布标签
git tag -a v2.0.0 -m "ToDo任务管理应用 v2.0.0 正式发布"

:: 推送标签到GitHub
git push origin v2.0.0

echo 标签已推送到GitHub，现在您可以在GitHub网站上创建Release：
echo 1. 访问https://github.com/YourUsername/todo-app/releases
echo 2. 点击"Draft a new release"
echo 3. 选择标签"v2.0.0"
echo 4. 填写发布标题"ToDo任务管理应用 v2.0.0"
echo 5. 填写发布说明（可从CHANGELOG.md复制）
echo 6. 上传installer/ToDo任务管理器_Setup.exe文件
echo 7. 点击"Publish release"

pause 