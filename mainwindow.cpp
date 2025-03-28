#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QCheckBox>
#include <QLabel>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QPainter>
#include <QFileDialog>
#include <QSettings>
#include <QStandardPaths>
#include <QDir>
#include <QTabBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStyle>
#include <QMenu>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_currentTabIndex(0)
{
    ui->setupUi(this);
    
    // 初始化taskModel
    taskModel = new QStandardItemModel(this);

    // 设置窗口属性，允许背景绘制
    setAttribute(Qt::WA_StyledBackground);

    // 应用背景颜色 - 使用新的Coolors配色方案
    setStyleSheet("QMainWindow { background-color: #F8F8F8; }"); // 浅灰白色背景，突出其他颜色
    
    // 设置图标
    setupIcons();

    // 初始化标签页控件
    initTabWidget();

    // 连接按钮信号与槽函数
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addTask);//输入任务并点击按钮
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::deleteTask);//点击任务再按按钮
    //搜索
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::searchTask); // 实时搜索
    //过滤功能
    connect(ui->filterBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::filterTasks);
    //设置背景图片
    connect(ui->backgroundButton, &QPushButton::clicked, this, &MainWindow::setBackgroundImage);
    //添加分类
    connect(ui->addCategoryButton, &QPushButton::clicked, this, &MainWindow::addCategory);
    //删除分类
    ui->tabWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tabWidget, &QWidget::customContextMenuRequested, this, [this](const QPoint &pos) {
        QMenu contextMenu(this);
        QAction *deleteAction = contextMenu.addAction(m_fontHelper.iconToString(FontHelper::FA_TRASH) + " 删除分类");
        deleteAction->setFont(m_fontHelper.iconFont(10));
        
        connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteCategory);
        contextMenu.exec(ui->tabWidget->mapToGlobal(pos));
    });
    //标签页切换
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);

    // 为任务输入框安装事件过滤器
    ui->inputTask->installEventFilter(this);
    // 为搜索框安装事件过滤器
    ui->searchLineEdit->installEventFilter(this);

    // 设置按钮样式 - 使用Coolors提供的配色方案，增强对比度和可见性
    QString addButtonStyle = "QPushButton {"
                         "background-color: #2A9D8F;" // 薄荷绿色 - 适合添加操作
                         "color: white;"
                         "border-radius: 8px;"
                         "padding: 8px 15px;"
                         "font-weight: bold;"
                         "border: 1px solid #1c6e64;" // 添加深色边框增强可见性
                         "}"
                         "QPushButton:hover {"
                         "background-color: #264653;" // 悬停时深青色
                         "}";
    
    QString deleteButtonStyle = "QPushButton {"
                              "background-color: #E76F51;" // 珊瑚色 - 适合删除操作
                              "color: white;"
                              "border-radius: 8px;"
                              "padding: 8px 15px;"
                              "font-weight: bold;"
                              "border: 1px solid #b25340;" // 添加深色边框增强可见性
                              "}"
                              "QPushButton:hover {"
                              "background-color: #B25340;" // 悬停时更深的珊瑚色
                              "}";
    
    QString backgroundButtonStyle = "QPushButton {"
                                  "background-color: #F4A261;" // 橙色 - 适合设置操作
                                  "color: white;"
                                  "border-radius: 8px;"
                                  "padding: 8px 15px;"
                                  "font-weight: bold;"
                                  "border: 1px solid #e67e22;" // 添加深色边框增强可见性
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: #E67E22;" // 悬停时更深的橙色
                                  "}";
    
    QString categoryButtonStyle = "QPushButton {"
                                "background-color: #E9C46A;" // 暖黄色 - 适合分类操作
                                "color: #264653;" // 文字使用深青色，增加对比度
                                "border-radius: 8px;"
                                "padding: 8px 15px;"
                                "font-weight: bold;"
                                "border: 1px solid #d4b157;" // 添加深色边框增强可见性
                                "}"
                                "QPushButton:hover {"
                                "background-color: #D4B157;" // 悬停时更深的黄色
                                "}";
    
    // 恢复背景按钮使用深青色
    QString resetButtonStyle = "QPushButton {"
                              "background-color: #264653;" // 深青色
                              "color: white;"
                              "border-radius: 8px;"
                              "padding: 8px 15px;"
                              "font-weight: bold;"
                              "border: 1px solid #1a323c;" // 添加深色边框增强可见性
                              "}"
                              "QPushButton:hover {"
                              "background-color: #1A323C;" // 悬停时更深的青色
                              "}";
    
    // 设置输入框样式，增强在背景图片上的可见性
    QString inputStyle = "QLineEdit, QTextEdit, QComboBox {"
                        "background-color: rgba(255, 255, 255, 0.85);" // 半透明背景
                        "border: 2px solid #2A9D8F;" // 使用薄荷绿色边框增强边界
                        "border-radius: 6px;"
                        "padding: 6px;"
                        "font-weight: bold;" // 加粗文字提高可读性
                        "color: #264653;" // 文字使用深青色增强对比
                        "}"
                        "QLineEdit:focus, QTextEdit:focus {"
                        "border: 2px solid #264653;" // 聚焦时使用深青色
                        "background-color: white;" // 聚焦时使用纯白背景
                        "}";
    
    ui->addButton->setStyleSheet(addButtonStyle);
    ui->deleteButton->setStyleSheet(deleteButtonStyle);
    ui->backgroundButton->setStyleSheet(backgroundButtonStyle);
    ui->addCategoryButton->setStyleSheet(categoryButtonStyle);
    
    ui->searchLineEdit->setStyleSheet(inputStyle);
    ui->inputTask->setStyleSheet(inputStyle);
    ui->filterBox->setStyleSheet(inputStyle + "QComboBox::drop-down { border: 0px; }");
    
    // 加载设置（包括背景图片）
    loadSettings();

    // 添加默认分类（如果没有分类）
    if (m_categoryLists.isEmpty()) {
        m_categoryLists["一般任务"] = createTaskListWidget();
        ui->tabWidget->addTab(m_categoryLists["一般任务"], "一般任务");
        loadTasksByCategory("一般任务");
    }
    
    // 创建并添加恢复背景按钮 - 始终显示在界面上
    QPushButton* resetButton = new QPushButton(m_fontHelper.iconToString(FontHelper::FA_TIMES) + " 恢复默认背景", this);
    resetButton->setFont(m_fontHelper.iconFont(10));
    resetButton->setStyleSheet(resetButtonStyle);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetBackgroundImage);
    ui->horizontalLayout->addWidget(resetButton);

    // 设置窗口标题和图标
    setWindowTitle("ToDo 任务管理");
    setMinimumSize(800, 600); // 设置最小窗口大小
       
    // 增强标签可见性    // 初始化应用 - 添加这一行
    enhanceLabelsVisibility();
}

void MainWindow::setupIcons()
{
    // 恢复FontAwesome功能
    
    // 搜索标签 - 修复图标堆积问题
    QLabel* searchIconLabel = new QLabel(this);
    searchIconLabel->setFont(m_fontHelper.iconFont(14));
    searchIconLabel->setText(m_fontHelper.iconToString(FontHelper::FA_SEARCH));
    QHBoxLayout* searchLayout = new QHBoxLayout();
    searchLayout->addWidget(searchIconLabel);
    searchLayout->addWidget(new QLabel("搜索：", this));
    searchLayout->setContentsMargins(0, 0, 0, 0);
    searchLayout->setSpacing(2);
    QWidget* searchWidget = new QWidget(this);
    searchWidget->setLayout(searchLayout);
    ui->horizontalLayout->replaceWidget(ui->searchLabel, searchWidget);
    ui->searchLabel->hide();
    
    // 过滤标签 - 修复图标堆积问题
    QLabel* filterIconLabel = new QLabel(this);
    filterIconLabel->setFont(m_fontHelper.iconFont(14));
    filterIconLabel->setText(m_fontHelper.iconToString(FontHelper::FA_FILTER));
    QHBoxLayout* filterLayout = new QHBoxLayout();
    filterLayout->addWidget(filterIconLabel);
    filterLayout->addWidget(new QLabel("过滤：", this));
    filterLayout->setContentsMargins(0, 0, 0, 0);
    filterLayout->setSpacing(2);
    QWidget* filterWidget = new QWidget(this);
    filterWidget->setLayout(filterLayout);
    ui->horizontalLayout->replaceWidget(ui->filterLabel, filterWidget);
    ui->filterLabel->hide();
    
    // 添加按钮
    ui->addButton->setFont(m_fontHelper.iconFont(10));
    ui->addButton->setText(m_fontHelper.iconToString(FontHelper::FA_PLUS) + " 添加");
    
    // 删除按钮
    ui->deleteButton->setFont(m_fontHelper.iconFont(10));
    ui->deleteButton->setText(m_fontHelper.iconToString(FontHelper::FA_TRASH) + " 删除");
    
    // 背景按钮
    ui->backgroundButton->setFont(m_fontHelper.iconFont(10));
    ui->backgroundButton->setText(m_fontHelper.iconToString(FontHelper::FA_IMAGE) + " 设置背景");
    
    // 添加分类按钮
    ui->addCategoryButton->setFont(m_fontHelper.iconFont(10));
    ui->addCategoryButton->setText(m_fontHelper.iconToString(FontHelper::FA_FOLDER) + " 新分类");
    
    // 任务标签
    QLabel* taskIconLabel = new QLabel(this);
    taskIconLabel->setFont(m_fontHelper.iconFont(14));
    taskIconLabel->setText(m_fontHelper.iconToString(FontHelper::FA_LIST));
    QHBoxLayout* taskLayout = new QHBoxLayout();
    taskLayout->addWidget(taskIconLabel);
    taskLayout->addWidget(new QLabel("任务：", this));
    taskLayout->setContentsMargins(0, 0, 0, 0);
    taskLayout->setSpacing(2);
    QWidget* taskWidget = new QWidget(this);
    taskWidget->setLayout(taskLayout);
    ui->horizontalLayout_2->replaceWidget(ui->taskLabel, taskWidget);
    ui->taskLabel->hide();
}

void MainWindow::initTabWidget() {
    // 获取已保存的分类列表
    QSettings settings("ToDo_App", "Categories");
    QStringList categories = settings.value("categories", QStringList() << "一般任务").toStringList();
    
    // 清空已有标签页
    ui->tabWidget->clear();
    m_categoryLists.clear();
    
    // 美化标签页样式 - 使用新的Coolors配色方案，增强对比度
    ui->tabWidget->setStyleSheet("QTabWidget::pane {"
                               "background-color: rgba(255, 255, 255, 200);" // 增加背景不透明度
                               "border-radius: 10px;"
                               "border: 1px solid #E0E0E0;"
                               "}"
                               "QTabBar::tab {"
                               "background-color: #E9C46A;" // 暖黄色标签
                               "color: #264653;" // 深青色文字
                               "padding: 10px 20px;"
                               "margin-right: 5px;"
                               "margin-bottom: 5px;"
                               "border-top-left-radius: 8px;"
                               "border-top-right-radius: 8px;"
                               "font-weight: bold;" // 加粗文字增强可读性
                               "}"
                               "QTabBar::tab:selected {"
                               "background-color: #2A9D8F;" // 选中标签为薄荷绿
                               "color: white;"
                               "font-weight: bold;"
                               "}"
                               "QTabBar::tab:hover:!selected {"
                               "background-color: #D4B157;" // 悬停为深黄色
                               "}");
    
    // 创建每个分类的标签页
    for (const QString &category : categories) {
        m_categoryLists[category] = createTaskListWidget();
        ui->tabWidget->addTab(m_categoryLists[category], category);
        loadTasksByCategory(category);
    }
}

QListWidget* MainWindow::createTaskListWidget() {
    QListWidget* listWidget = new QListWidget();
    
    // 设置样式表，使用新的Coolors配色方案，增强对比度
    listWidget->setStyleSheet("QListWidget {"
                             "background-color: rgba(255, 255, 255, 240);" // 增加背景不透明度
                             "border-radius: 10px;"
                             "border: 1px solid #E0E0E0;"
                             "outline: 0px;" /* 移除外部轮廓 */
                             "padding: 8px;"
                             "}"
                             "QListWidget::item {"
                             "background-color: #FFFFFF;"
                             "border-radius: 8px;"
                             "margin: 5px;"
                             "padding: 15px;"
                             "border: 1px solid #E0E0E0;"
                             "}"
                             "QListWidget::item:hover {"
                             "background-color: #F5F9F8;"
                             "border: 1px solid #2A9D8F;"
                             "}"
                             "QListWidget::item:selected {"
                             "background-color: #DEF2F1;" /* 薄荷绿背景 */
                             "border: 1px solid #2A9D8F;"
                             "color: #264653;" /* 深青色文字 */
                             "outline: 0px;" /* 移除选中时的虚线框 */
                             "}");
    
    // 设置自动换行
    listWidget->setWordWrap(true);
    listWidget->setTextElideMode(Qt::ElideNone);
    
    // 禁用项目的焦点矩形点矩形
    listWidget->setFocusPolicy(Qt::NoFocus);
    
    // 连接双击事件
    connect(listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::editTask);
    
    // 连接复选框状态改变事件
    connect(listWidget, &QListWidget::itemChanged, this, &MainWindow::handleTaskStateChange);
    
    // 设置右键菜单
    listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(listWidget, &QListWidget::customContextMenuRequested, [this, listWidget](const QPoint &pos) {
        // 获取右键点击的项
        QListWidgetItem* item = listWidget->itemAt(pos);
        if (item) {
            // 显示右键菜单
            QMenu contextMenu(this);
            
            // 添加编辑选项
            QAction *editAction = contextMenu.addAction(m_fontHelper.iconToString(FontHelper::FA_PENCIL) + " 编辑任务");
            editAction->setFont(m_fontHelper.iconFont(10));
            
            // 添加删除选项
            QAction *deleteAction = contextMenu.addAction(m_fontHelper.iconToString(FontHelper::FA_TRASH) + " 删除任务");
            deleteAction->setFont(m_fontHelper.iconFont(10));
            
            // 设置菜单样式
            contextMenu.setStyleSheet("QMenu {"
                                     "background-color: white;"
                                     "border: 1px solid #E0E0E0;"
                                     "border-radius: 6px;"
                                     "padding: 5px;"
                                     "}"
                                     "QMenu::item {"
                                     "padding: 6px 30px 6px 20px;"
                                     "border-radius: 4px;"
                                     "margin: 3px;"
                                     "color: #264653;"
                                     "}"
                                     "QMenu::item:selected {"
                                     "background-color: #DEF2F1;"
                                     "color: #264653;"
                                     "}");
            
            // 连接编辑操作
            connect(editAction, &QAction::triggered, [this, item]() {
                editTask(item);
            });
            
            // 连接删除操作
            connect(deleteAction, &QAction::triggered, [this, item]() {
                // 获取当前分类
                QString currentCategory = ui->tabWidget->tabText(m_currentTabIndex);
                
                // 删除任务
                delete item;
                 
                // 保存任务
                saveTasksByCategory(currentCategory);
            });
                 
            contextMenu.exec(listWidget->mapToGlobal(pos));
        }
    });
        
    return listWidget;
}

void MainWindow::onTabChanged(int index) {
    // 清除旧标签页的选中状态
    if (m_currentTabIndex >= 0 && m_currentTabIndex < ui->tabWidget->count()) {
        QString oldCategory = ui->tabWidget->tabText(m_currentTabIndex);
        QListWidget* oldList = m_categoryLists[oldCategory];
        if (oldList) {
            oldList->clearSelection(); // 清除选择
            oldList->clearFocus();     // 清除焦点
        }
    }
       
    // 更新当前标签页索引
    m_currentTabIndex = index;
}

void MainWindow::addCategory() {
    bool ok;
    QString categoryName = QInputDialog::getText(this, tr("添加新分类"),
                                           tr("请输入分类名称:"), QLineEdit::Normal,
                                           "", &ok);
    if (ok && !categoryName.isEmpty()) {
        // 检查分类是否已存在
        if (m_categoryLists.contains(categoryName)) {
            QMessageBox::warning(this, tr("添加失败"), tr("该分类名称已存在"));
            return;
        }
        
        // 创建新分类的列表控件
        m_categoryLists[categoryName] = createTaskListWidget();
        
        // 添加到标签页
        int newTabIndex = ui->tabWidget->addTab(m_categoryLists[categoryName], categoryName);
        ui->tabWidget->setCurrentIndex(newTabIndex);
           
        // 保存分类列表
        saveCategories();
    }
}

void MainWindow::deleteCategory() {
    // 不能删除最后一个分类
    if (ui->tabWidget->count() <= 1) {
        QMessageBox::warning(this, tr("删除失败"), tr("至少需要保留一个分类"));
        return;
    }
    
    // 获取当前分类名称
    QString categoryName = ui->tabWidget->tabText(m_currentTabIndex);
    
    // 确认是否删除
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("确认删除"), 
                                 QString(tr("您确定要删除分类\"%1\"吗？\n所有该分类下的任务也将被删除。")).arg(categoryName),
                                 QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // 获取要删除的列表控件
        QListWidget* listToDelete = m_categoryLists[categoryName];
        
        // 从Map中移除
        m_categoryLists.remove(categoryName);
        
        // 从标签页中移除
        ui->tabWidget->removeTab(m_currentTabIndex);
        
        // 删除列表控件
        delete listToDelete;
        
        // 删除对应的任务文件
        QString safeCategory = categoryName;
        QString fileName = "tasks_" + safeCategory.replace(" ", "_") + ".json";
        QFile::remove(fileName);
           
        // 保存分类列表
        saveCategories();
    }
}

// 保存分类列表
void MainWindow::saveCategories() {
    QSettings settings("ToDo_App", "Categories");
    QStringList categories;
    for (auto it = m_categoryLists.begin(); it != m_categoryLists.end(); ++it) {
        categories << it.key();
    }
    settings.setValue("categories", categories);
}

// 绘制事件，用于绘制背景图片
void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    
    if (!m_backgroundImage.isNull()) {
        // 先绘制背景图片
        painter.drawPixmap(rect(), m_backgroundImage.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        
        // 添加半透明蒙版，降低透明度使背景图片更清晰可见
        painter.fillRect(rect(), QColor(255, 255, 255, 100)); // 从160降低到100，使背景更清晰
    } else {
        // 如果没有背景图片，绘制一个渐变背景
        QLinearGradient gradient(0, 0, width(), height());
        gradient.setColorAt(0, QColor("#FFFFFF"));
        gradient.setColorAt(0.5, QColor("#F9FAFB"));
        gradient.setColorAt(1, QColor("#F0F2F5"));
        painter.fillRect(rect(), gradient);
        
        // 添加一些装饰性元素 - 底部的装饰条
        int stripeHeight = 8;
        QRect bottomStripe(0, height() - stripeHeight, width(), stripeHeight);
        QLinearGradient stripGradient(0, 0, width(), 0);
        stripGradient.setColorAt(0, QColor("#2A9D8F"));
        stripGradient.setColorAt(0.25, QColor("#E9C46A"));
        stripGradient.setColorAt(0.5, QColor("#F4A261"));
        stripGradient.setColorAt(0.75, QColor("#E76F51"));
        stripGradient.setColorAt(1, QColor("#264653"));
        painter.fillRect(bottomStripe, stripGradient);
    }
        
    QMainWindow::paintEvent(event); // 在绘制完背景后调用父类的paintEvent
}

// 设置背景图片
void MainWindow::setBackgroundImage() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("选择背景图片"),
                                                  QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).first(),
                                                  tr("图片文件 (*.png *.jpg *.jpeg *.bmp)"));
    if (!fileName.isEmpty()) {
        m_backgroundImagePath = fileName;
        
        // 加载图片
        QImage originalImage(fileName);
        if (originalImage.isNull()) {
            QMessageBox::warning(this, tr("图片加载失败"), tr("无法加载所选图片，请选择其他图片。"));
            return;
        }
        
        // 检查图片亮度
        bool isDarkImage = isImageDark(originalImage);
        
        // 如果图片偏暗，应用亮度增强处理
        if (isDarkImage) {
            QMessageBox enhanceMsg;
            enhanceMsg.setWindowTitle("图片较暗");
            enhanceMsg.setText("您选择的背景图片较暗，这可能会影响文字可读性。");
            enhanceMsg.setInformativeText("是否要自动提亮图片以增强文字可见性？");
            enhanceMsg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            enhanceMsg.setDefaultButton(QMessageBox::Yes);
            
            if (enhanceMsg.exec() == QMessageBox::Yes) {
                // 增强图片亮度
                originalImage = enhanceImageBrightness(originalImage, 30); // 增加30%亮度
            }
        }
        
        // 转换为QPixmap并保存
        m_backgroundImage = QPixmap::fromImage(originalImage);
        saveSettings(); // 保存设置
        update(); // 重绘窗口以显示新背景
        
        // 提示用户添加的背景是否合适
        QMessageBox successMsg;
        successMsg.setWindowTitle("背景已设置");
        successMsg.setText("背景图片已成功设置！");
        successMsg.setInformativeText("如果背景看起来太暗或影响文字阅读，您可以尝试使用亮色或浅色的图片，或者点击\"恢复默认背景\"按钮恢复简约渐变背景。");
        successMsg.setIcon(QMessageBox::Information);
        successMsg.setStandardButtons(QMessageBox::Ok);
        successMsg.setDefaultButton(QMessageBox::Ok);
        successMsg.setStyleSheet("QMessageBox {"
                               "background-color: white;"
                               "}"
                               "QLabel {"
                               "color: #212529;"
                               "min-width: 300px;"
                               "}");
        successMsg.exec();
    }
}

// 检查图片是否偏暗
bool MainWindow::isImageDark(const QImage &image) {
    // 采样图片以检查平均亮度
    int totalBrightness = 0;
    int samplesCount = 0;
    const int sampleStep = 20; // 每20个像素采样一次
    
    for (int y = 0; y < image.height(); y += sampleStep) {
        for (int x = 0; x < image.width(); x += sampleStep) {
            QColor pixelColor = image.pixelColor(x, y);
            // 计算亮度 (0.299*R + 0.587*G + 0.114*B)
            int brightness = (0.299 * pixelColor.red() + 
                             0.587 * pixelColor.green() + 
                             0.114 * pixelColor.blue());
            totalBrightness += brightness;
            samplesCount++;
        }
    }
    
    if (samplesCount == 0) return false;
    
    // 计算平均亮度
    int averageBrightness = totalBrightness / samplesCount;
       
    // 如果平均亮度低于128（中值），则认为图片偏暗
    return averageBrightness < 128;
}

// 增强图片亮度强图片亮度
QImage MainWindow::enhanceImageBrightness(const QImage &image, int percent) {
    QImage result = image;
    
    // 亮度增加比例，percent范围为0-100
    float factor = 1.0 + (percent / 100.0);
    
    for (int y = 0; y < result.height(); y++) {
        for (int x = 0; x < result.width(); x++) {
            QColor pixelColor = result.pixelColor(x, y);
            
            // 提高亮度，但限制在0-255范围
            int r = qMin(255, static_cast<int>(pixelColor.red() * factor));
            int g = qMin(255, static_cast<int>(pixelColor.green() * factor));
            int b = qMin(255, static_cast<int>(pixelColor.blue() * factor));
                   
            result.setPixelColor(x, y, QColor(r, g, b, pixelColor.alpha()));
        }
    }
        
    return result;
}

// 恢复默认背景
void MainWindow::resetBackgroundImage() {
    // 清除背景图片
    m_backgroundImagePath = "";
    m_backgroundImage = QPixmap(); // 空图片
    
    // 保存设置
    saveSettings();
    
    // 重绘窗口
    update();
       
    // 显示确认消息
    QMessageBox::information(this, tr("背景已重置"), tr("已恢复默认背景"));
}

// 保存设置
void MainWindow::saveSettings() {
    QSettings settings("ToDo_App", "Settings");
    settings.setValue("BackgroundImagePath", m_backgroundImagePath);
}

// 加载设置
void MainWindow::loadSettings() {
    QString settingsPath = m_dataDir + "/settings.ini";
    QSettings settings(settingsPath, QSettings::IniFormat);
    m_backgroundImagePath = settings.value("BackgroundImagePath", "").toString();
    if (!m_backgroundImagePath.isEmpty() && QFile::exists(m_backgroundImagePath)) {
        m_backgroundImage.load(m_backgroundImagePath);
    }
}

// 事件过滤器实现
bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    // 检查事件是否来自任务输入框且是否为按键事件
    if (obj == ui->inputTask && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        // 检查是否按下了Ctrl+Enter组合键Enter组合键
        if ((keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) && 
            keyEvent->modifiers() == Qt::ControlModifier) {
            // 调用添加任务函数
            addTask();
            return true; // 事件已处理
        }
        return false; // 让QTextEdit处理其他按键事件
    }
    // 检查事件是否来自搜索框且是否为按键事件为按键事件
    else if (obj == ui->searchLineEdit && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        // 检查是否按下了回车键
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            // 调用搜索任务函数
            searchTask();
            return true; // 事件已处理
        }
    }
    // 对于其他情况，让父类处理
    return QMainWindow::eventFilter(obj, event);
}

// 增加任务
void MainWindow::addTask() {
    QString taskText = ui->inputTask->toPlainText().trimmed();
    if (taskText.isEmpty() || m_categoryLists.isEmpty()) return;
    
    // 获取当前分类的列表控件
    QString currentCategory = ui->tabWidget->tabText(m_currentTabIndex);
    QListWidget* currentList = m_categoryLists[currentCategory];
    
    if (!currentList) return;

    // 创建新的 QListWidgetItem
    QListWidgetItem* item = new QListWidgetItem(taskText);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);

    // 设置字体和颜色 - 使用新的配色方案，增强可见性
    QFont font = item->font();
    font.setPointSize(14);
    font.setBold(true); // 粗体增强可读性
    item->setFont(font);
    item->setForeground(QColor("#264653")); // 深青色文字
    item->setBackground(QColor("#FFFFFF")); // 白色背景

    // 调整 item 的高度，允许多行
    QSize itemSize = item->sizeHint();
    // 根据文本行数设置高度
    int lineCount = taskText.count('\n') + 1;
    int height = std::max(60, lineCount * 30); // 更宽敞的高度
    itemSize.setHeight(height);
    item->setSizeHint(itemSize);

    // 添加动画效果
    item->setBackground(QColor("#DEF2F1")); // 先设置为突出色

    // 将 item 添加到列表
    currentList->addItem(item);
    
    // 选中新添加的任务
    currentList->setCurrentItem(item);
        
    // 动画效果：滚动到新添加的项目
    currentList->scrollToItem(item);

    // 清空输入框
    ui->inputTask->clear();

    // 保存任务
    saveTasksByCategory(currentCategory);
    
    // 使用延迟效果恢复正常背景色，创建"闪烁"效果
    QTimer::singleShot(600, [item]() {
        if (item) { // 检查item是否仍然有效
            item->setBackground(QColor("#FFFFFF")); // 恢复为白色背景
        }
    });
}

// 删除任务
void MainWindow::deleteTask()
{
    if (m_categoryLists.isEmpty()) return;
    
    // 获取当前分类的列表控件
    QString currentCategory = ui->tabWidget->tabText(m_currentTabIndex);
    QListWidget* currentList = m_categoryLists[currentCategory];
    
    if (!currentList) return;
    
    // 获取当前选中的项目
    QListWidgetItem* item = currentList->currentItem();
    if (item) {
        delete item; // 删除选中项目
           
        // 保存任务
        saveTasksByCategory(currentCategory);
    }
}

// 修改任务
void MainWindow::editTask(QListWidgetItem* item)
{
    if (!item) return;  // 避免空指针异常

    // 获取当前分类
    QString currentCategory = ui->tabWidget->tabText(m_currentTabIndex);
    QListWidget* currentList = m_categoryLists[currentCategory];
    if (!currentList) return;

    // 临时断开itemChanged信号连接，避免编辑时触发handleTaskStateChange
    disconnect(currentList, &QListWidget::itemChanged, this, &MainWindow::handleTaskStateChange);

    // 记录当前任务在列表中的位置
    int currentRow = currentList->row(item);
    
    // 获取当前任务的文本和复选框状态
    QString currentText = item->text();
    bool isCompleted = (item->checkState() == Qt::Checked);

    // 创建一个更适合多行文本的对话框
    QDialog dialog(this);
    dialog.setWindowTitle("编辑任务");
    dialog.resize(550, 350);
    
    // 设置对话框样式 - 使用新的配色方案，确保在背景图片上可见
    dialog.setStyleSheet("QDialog { "
                        "background-color: rgba(255, 255, 255, 0.95); " // 高透明度白色背景
                        "border-radius: 15px; "
                        "border: 2px solid #2A9D8F; " // 使用薄荷绿色边框增强边界
                        "}");
    
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->setContentsMargins(25, 25, 25, 25);
    layout->setSpacing(20);
    
    // 创建带图标的标题标签
    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->setSpacing(12);
    
    QLabel *iconLabel = new QLabel(&dialog);
    iconLabel->setFont(m_fontHelper.iconFont(22));
    iconLabel->setText(m_fontHelper.iconToString(FontHelper::FA_PENCIL));
    iconLabel->setStyleSheet("color: #2A9D8F;");
    
    QLabel *label = new QLabel("修改您的任务：", &dialog);
    QFont titleFont = label->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    label->setFont(titleFont);
    label->setStyleSheet("color: #264653;");
    
    titleLayout->addWidget(iconLabel);
    titleLayout->addWidget(label);
    titleLayout->addStretch();
    
    QTextEdit *textEdit = new QTextEdit(&dialog);
    textEdit->setPlainText(currentText);
    textEdit->setStyleSheet("QTextEdit { "
                           "background-color: #FFFFFF; "
                           "border: 1px solid #E0E0E0; "
                           "border-radius: 10px; "
                           "padding: 15px; "
                           "font-size: 14px; "
                           "color: #264653; "
                           "}"
                           "QTextEdit:focus { "
                           "border: 2px solid #2A9D8F; "
                           "}");
    
    // 设置文本编辑框为焦点
    textEdit->setFocus();
    // 将光标放在文本末尾
    textEdit->moveCursor(QTextCursor::End);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(15);
    
    QPushButton *okButton = new QPushButton(&dialog);
    okButton->setText(m_fontHelper.iconToString(FontHelper::FA_CHECK) + " 确定");
    okButton->setFont(m_fontHelper.iconFont(12));
    okButton->setStyleSheet("QPushButton { "
                           "background-color: #2A9D8F; "
                           "color: white; "
                           "border-radius: 8px; "
                           "padding: 10px 20px; "
                           "font-weight: bold; "
                           "}"
                           "QPushButton:hover { "
                           "background-color: #264653; "
                           "}");
    
    QPushButton *cancelButton = new QPushButton(&dialog);
    cancelButton->setText(m_fontHelper.iconToString(FontHelper::FA_TIMES) + " 取消");
    cancelButton->setFont(m_fontHelper.iconFont(12));
    cancelButton->setStyleSheet("QPushButton { "
                              "background-color: #F9FAFB; "
                              "color: #264653; "
                              "border: 1px solid #E0E0E0; "
                              "border-radius: 8px; "
                              "padding: 10px 20px; "
                              "font-weight: bold; "
                              "}"
                              "QPushButton:hover { "
                              "background-color: #F0F2F5; "
                              "}");
    
    connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(okButton);
    
    layout->addLayout(titleLayout);
    layout->addWidget(textEdit);
    layout->addLayout(buttonLayout);
    
    // 运行对话框并判断是否点击了"确定"
    if (dialog.exec() == QDialog::Accepted) {
        QString newText = textEdit->toPlainText().trimmed();
        if (!newText.isEmpty()) {
            // 彻底解决方案：删除旧项，创建新项
            delete item;
            
            // 创建新项
            QListWidgetItem* newItem = new QListWidgetItem(newText);
            newItem->setFlags(newItem->flags() | Qt::ItemIsUserCheckable);
            newItem->setCheckState(isCompleted ? Qt::Checked : Qt::Unchecked);
            
            // 设置样式
            QFont font = newItem->font();
            font.setPointSize(14);
            font.setStrikeOut(isCompleted);
            newItem->setFont(font);
            
            // 使用新配色方案
            if (isCompleted) {
                newItem->setForeground(QColor("#88A5A1")); // 淡薄荷色
                newItem->setBackground(QColor("#F5F9F8")); // 非常淡的薄荷背景
            } else {
                newItem->setForeground(QColor("#264653")); // 深青色文字
                newItem->setBackground(QColor("#FFFFFF")); // 白色背景
            }
            
            // 调整新项的高度
            QSize itemSize = newItem->sizeHint();
            int lineCount = newText.count('\n') + 1;
            int height = std::max(60, lineCount * 30); // 更宽敞的高度
            itemSize.setHeight(height);
            newItem->setSizeHint(itemSize);
            
            // 插入新项到原来的位置
            currentList->insertItem(currentRow, newItem);
            currentList->setCurrentItem(newItem);
               
            // 保存任务
            saveTasksByCategory(currentCategory);
        }
    }
       
    // 重新连接itemChanged信号
    connect(currentList, &QListWidget::itemChanged, this, &MainWindow::handleTaskStateChange);
}

//搜索任务
void MainWindow::searchTask() {
    QString keyword = ui->searchLineEdit->text().trimmed();
    if (m_categoryLists.isEmpty()) return;
    // 遍历所有分类，搜索匹配的任务
    for (auto it = m_categoryLists.begin(); it != m_categoryLists.end(); ++it) {
        QListWidget* listWidget = it.value();
        if (!listWidget) continue;
        if (keyword.isEmpty()) {
            // 如果搜索框为空，显示所有任务
            for (int i = 0; i < listWidget->count(); ++i) {
                listWidget->item(i)->setHidden(false);
            }
        } else {
            // 遍历列表并隐藏不匹配的任务
            for (int i = 0; i < listWidget->count(); ++i) {
                QListWidgetItem* item = listWidget->item(i);
                if (!item->text().contains(keyword, Qt::CaseInsensitive)) {
                    item->setHidden(true);  // 不匹配则隐藏
                } else {
                    item->setHidden(false); // 匹配则显示
                }
            }
        }
    }
}

//数据持久化：根据分类保存任务
void MainWindow::saveTasksByCategory(const QString &category) {
    QListWidget* listWidget = m_categoryLists.value(category);
    if (!listWidget) return;
    
    QJsonArray taskArray;
    for (int i = 0; i < listWidget->count(); ++i) {
        QListWidgetItem* item = listWidget->item(i);
        QJsonObject taskObject;
        taskObject["task"] = item->text();
        taskObject["completed"] = (item->checkState() == Qt::Checked);
        taskArray.append(taskObject);
    }

    QJsonObject tasksObject;
    tasksObject["tasks"] = taskArray;

    // 使用分类名作为文件名的一部分，创建一个局部副本进行修改
    QString categoryName = category;
    QString fileName = "tasks_" + categoryName.replace(" ", "_") + ".json";
    QString filePath = m_dataDir + "/" + fileName;
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(tasksObject);
        file.write(doc.toJson());
        file.close();
    }
}

//保存所有分类的任务
void MainWindow::saveTasks() {
    for (auto it = m_categoryLists.begin(); it != m_categoryLists.end(); ++it) {
        saveTasksByCategory(it.key());
    }
}

//根据分类加载任务
void MainWindow::loadTasksByCategory(const QString &category) {
    QListWidget* listWidget = m_categoryLists.value(category);
    if (!listWidget) return;
    
    // 清空当前列表
    listWidget->clear();
    
    // 使用分类名作为文件名的一部分，创建一个局部副本进行修改
    QString categoryName = category;
    QString fileName = "tasks_" + categoryName.replace(" ", "_") + ".json";
    QString filePath = m_dataDir + "/" + fileName;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return;

    QByteArray saveData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(saveData);
    QJsonArray taskArray = doc.object()["tasks"].toArray();

    for (int i = 0; i < taskArray.size(); ++i) {
        QJsonObject taskObject = taskArray[i].toObject();
        QString taskText = taskObject["task"].toString();
        bool isCompleted = taskObject["completed"].toBool();

        QListWidgetItem* item = new QListWidgetItem(taskText, listWidget);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(isCompleted ? Qt::Checked : Qt::Unchecked);

        // 调整item高度
        QSize itemSize = item->sizeHint();
        int lineCount = taskText.count('\n') + 1;
        int height = std::max(60, lineCount * 30); // 更宽敞高度        int height = std::max(60, lineCount * 30); // 更宽敞高度
        itemSize.setHeight(height);
        item->setSizeHint(itemSize);

        // 根据完成状态设置样式，增强可见性
        QFont font = item->font();
        font.setPointSize(14);
        font.setBold(!isCompleted); // 未完成任务使用粗体增强可读性font.setBold(!isCompleted); // 未完成任务使用粗体增强可读性
        font.setStrikeOut(isCompleted); // 已完成任务添加删除线ikeOut(isCompleted); // 已完成任务添加删除线
        item->setFont(font);
        
        // 使用新的配色方案
        if (isCompleted) {
            item->setForeground(QColor("#88A5A1")); // 淡薄荷色
            item->setBackground(QColor("#F5F9F8")); // 非常淡的薄荷背景
        } else {
            item->setForeground(QColor("#264653")); // 深青色文字
            item->setBackground(QColor("#FFFFFF")); // 白色背景
        }
    }
}

//加载所有任务
void MainWindow::loadTasks() {
    for (auto it = m_categoryLists.begin(); it != m_categoryLists.end(); ++it) {
        loadTasksByCategory(it.key());
    }
}

//复选框监视任务完成状态
void MainWindow::handleTaskStateChange(QListWidgetItem* item) {
    if (!item) return;
    
    // 获取当前分类
    QString currentCategory = ui->tabWidget->tabText(m_currentTabIndex);
    
    if (item->checkState() == Qt::Checked) {
        // 任务已完成 - 设置样式
        QFont font = item->font();
        font.setStrikeOut(true);
        font.setBold(false); // 去除粗体
        item->setFont(font);
        item->setForeground(QColor("#88A5A1")); // 淡薄荷色
        
        // 修改背景以指示完成状态
        item->setBackground(QColor("#F5F9F8")); // 非常淡的薄荷背景
    } else {
        // 任务未完成 - 恢复样式
        QFont font = item->font();
        font.setStrikeOut(false);
        font.setBold(true); // 使用粗体增强可读性
        item->setFont(font);
        item->setForeground(QColor("#264653")); // 深青色文字字
           
        // 恢复背景    // 恢复背景
        item->setBackground(QColor("#FFFFFF")); // 白色背景etBackground(QColor("#FFFFFF")); // 白色背景
    }
       
    // 保存任务状态变化    // 保存任务状态变化
    saveTasksByCategory(currentCategory);
}

//过滤功能功能
void MainWindow::filterTasks(int index) {
    if (m_categoryLists.isEmpty()) return;
    
    // 遍历所有分类，过滤各自的任务
    for (auto it = m_categoryLists.begin(); it != m_categoryLists.end(); ++it) {
        QListWidget* listWidget = it.value();
        if (!listWidget) continue;
                
        for (int i = 0; i < listWidget->count(); ++i) {
            QListWidgetItem* item = listWidget->item(i);

        // 检查复选框状态
        bool isChecked = (item->checkState() == Qt::Checked);

        switch (index) {
        case 0: // "所有"
            item->setHidden(false);
            break;
        case 1: // "未完成"
            item->setHidden(isChecked); // 已完成则隐藏
            break;
        case 2: // "已完成"
            item->setHidden(!isChecked); // 未完成则隐藏
            break;
            }
        }
    }
}

// 新增方法：增强标签的可见性
void MainWindow::enhanceLabelsVisibility() {
    // 为所有标签添加背景和边框，确保在任何背景下都清晰可见
    QString labelStyle = "QLabel {"
                        "background-color: rgba(255, 255, 255, 0.75);"
                        "border-radius: 4px;"
                        "padding: 2px 5px;"
                        "color: #264653;"
                        "font-weight: bold;"
                        "}";
    
    // 应用样式到搜索和过滤区域的标签
    QList<QLabel*> labels = findChildren<QLabel*>();
    for (QLabel* label : labels) {
        if (!label->text().isEmpty() && !m_fontHelper.isIconFont(label->font())) {
            label->setStyleSheet(labelStyle);
        }
    }
}

void MainWindow::initializeApp() {
    // 检查是否首次运行（通过查找默认任务文件）
    QSettings settings;
    bool firstRun = !settings.contains("initialized") || settings.value("initialized").toBool() == false;
    
    if (firstRun) {
        // 首次运行时初始化默认设置
        settings.setValue("initialized", true);
        
        // 创建默认分类
        QStringList defaultCategories = {"工作", "个人", "购物"};
        settings.setValue("categories", defaultCategories);
        
        // 为每个默认分类创建空的任务文件
        foreach (const QString &category, defaultCategories) {
            QString fileName = QString("tasks_%1.json").arg(category);
            QFile file(QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).filePath(fileName));
            
            if (!file.exists()) {
                // 创建包含空任务列表的文件
                if (file.open(QIODevice::WriteOnly)) {
                    QJsonObject tasksObject;
                    QJsonArray tasksArray;
                    tasksObject["tasks"] = tasksArray;
                    
                    QJsonDocument document(tasksObject);
                    file.write(document.toJson());
                    file.close();
                }
            }
        }
        
        // 设置当前分类为第一个默认分类
        m_currentCategory = defaultCategories.first();
    }
    
    // 加载分类和任务
    initTabWidget(); // 初始化标签页，这会加载分类
    loadTasks();
}

MainWindow::~MainWindow()
{
    // 保存所有任务
    saveTasks();
    
    delete ui;
}
