#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("ToDo 任务列表");  // 设置窗口标题
    w.resize(800, 600);                  // 设置窗口大小
    w.show();                             // 显示窗口

    return a.exec();
}
