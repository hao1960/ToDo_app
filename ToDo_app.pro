QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# 添加版本信息
VERSION = 2.0.3
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# 添加应用程序元数据
QMAKE_TARGET_COMPANY = "个人开发"
QMAKE_TARGET_PRODUCT = "ToDo任务管理器"
QMAKE_TARGET_DESCRIPTION = "一个简单且功能强大的任务管理应用"
QMAKE_TARGET_COPYRIGHT = "版权所有 (C) 2023"

# 优化发布版本
QMAKE_CXXFLAGS_RELEASE += -O3

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fonthelper.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    fonthelper.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    ToDo_app_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# 资源文件
RESOURCES += \
    resources.qrc

# 应用图标设置
win32 {
    RC_ICONS = $$PWD/icons/todolist.ico
}
macx {
    ICON = $$PWD/icons/todolist.icns
}
unix:!macx {
    # Linux图标
    icon.files = $$PWD/icons/todolist.png
    icon.path = $$PREFIX/share/icons/hicolor/256x256/apps
    INSTALLS += icon
    
    # .desktop文件
    desktop.files = ToDo_app.desktop
    desktop.path = $$PREFIX/share/applications
    INSTALLS += desktop
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target