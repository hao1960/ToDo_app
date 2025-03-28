#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QKeyEvent>
#include <QPixmap>
#include <QMap>
#include <QTabWidget>
#include <QListWidget>
#include <QStandardItemModel>
#include "fonthelper.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // 背景配色方案枚举
    enum ColorScheme {
        Default,    // 默认白色背景
        Blue,       // 蓝色系：52b69a、34a0a4、168aad
        Pink,       // 粉色系：ffb3c1、ff8fa3、ff758f
        Green,      // 绿色系：d9ed92、b5e48c、99d98c
        Purple,     // 紫色系：c77dff、9d4edd、7b2cbf
        LightBlue,  // 淡蓝粉：a2d2ff、bde0fe、ffafcc
        LightBrown  // 淡棕色：fefae0、faedcd、d4a373
    };
    
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    bool eventFilter(QObject *obj, QEvent *event) override; // 添加事件过滤器
    void paintEvent(QPaintEvent *event) override; // 添加绘制事件处理

private slots:
    void addTask();//增加任务
    void deleteTask();//删除任务
    void editTask(QListWidgetItem* item);//修改任务
    void searchTask();//查找任务
    void saveTasks();//保存数据
    void loadTasks();//启动应用加载数据
    void handleTaskStateChange(QListWidgetItem* item);//监听复选框状态变化
    void filterTasks(int index);//根据任务完成状态的过滤功能
    void setBackgroundImage();//设置背景图片
    void resetBackgroundImage();//恢复默认背景
    void addCategory();//添加新的任务分类
    void deleteCategory(); // 添加删除分类功能
    void onTabChanged(int index);//标签页切换事件
    void setColorScheme(int scheme);//设置背景配色方案

private:
    Ui::MainWindow *ui;
    QTabWidget *m_tabWidget; // 任务分类标签页
    QMap<QString, QListWidget*> m_categoryLists; // 存储各个分类的任务列表
    int m_currentTabIndex; // 当前选中的标签页索引
    QListWidget*taskList;
    QStandardItemModel *taskModel; // 任务模型
    QPixmap m_backgroundImage; // 背景图片
    QString m_backgroundImagePath; // 背景图片路径
    FontHelper m_fontHelper; // 字体图标帮助类
    QString m_currentCategory; // 当前选中的分类
    QString m_dataDir; // 应用数据存储目录
    ColorScheme m_colorScheme; // 当前选择的配色方案
    void saveSettings(); // 保存设置（包括背景图片路径和配色方案）
    void loadSettings(); // 加载设置
    void initTabWidget(); // 初始化标签页控件
    void saveTasksByCategory(const QString &category); // 根据分类保存任务
    void loadTasksByCategory(const QString &category); // 根据分类加载任务
    QListWidget* createTaskListWidget(); // 创建一个新的任务列表控件
    void setupIcons(); // 设置界面图标
    void saveCategories(); // 添加保存分类的方法声明
    void enhanceLabelsVisibility(); // 增强标签可见性的方法
    bool isImageDark(const QImage &image); // 检查图片是否偏暗
    QImage enhanceImageBrightness(const QImage &image, int percent); // 增强图片亮度
    void initializeApp(); // 添加缺失的函数声明
    void applyColorScheme(ColorScheme scheme); // 应用背景配色方案
    void setupColorSchemeSelector(); // 设置配色方案选择器
};
#endif // MAINWINDOW_H
