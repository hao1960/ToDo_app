#ifndef FONTHELPER_H
#define FONTHELPER_H

#include <QObject>
#include <QFont>
#include <QFontDatabase>
#include <QMap>
#include <QString>

class FontHelper : public QObject
{
    Q_OBJECT
public:
    explicit FontHelper(QObject *parent = nullptr);
    
    // FontAwesome图标代码
    enum Icons {
        FA_PLUS = 0xf067,
        FA_TRASH = 0xf1f8,
        FA_PENCIL = 0xf040,
        FA_SEARCH = 0xf002,
        FA_FILTER = 0xf0b0,
        FA_IMAGE = 0xf03e,
        FA_CHECK = 0xf00c,
        FA_SAVE = 0xf0c7,
        FA_LIST = 0xf03a,
        FA_FOLDER = 0xf07b,
        FA_FOLDER_PLUS = 0xf07b, // 使用FA_FOLDER作为替代，FontAwesome 4.7.0没有folder-plus图标
        FA_CALENDAR = 0xf073,
        FA_COGS = 0xf085,
        FA_TIMES = 0xf00d  // 添加X图标用于取消按钮
    };
    
    QFont iconFont(int size = 14);
    QString iconToString(Icons icon);
    
    // 判断字体是否为图标字体
    bool isIconFont(const QFont& font) const
    {
        return font.family() == m_fontFamily;
    }

private:
    int m_fontId;
    QString m_fontFamily;
};

#endif // FONTHELPER_H 