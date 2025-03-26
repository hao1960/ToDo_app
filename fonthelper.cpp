#include "fonthelper.h"
#include <QFile>
#include <QDebug>
#include <QFontDatabase>

FontHelper::FontHelper(QObject *parent) : QObject(parent), m_fontId(-1)
{
    // 加载字体文件
    m_fontId = QFontDatabase::addApplicationFont(":/fonts/fontawesome-webfont.ttf");
    if (m_fontId != -1) {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(m_fontId);
        if (!fontFamilies.isEmpty()) {
            m_fontFamily = fontFamilies.at(0);
        }
    }
}

QFont FontHelper::iconFont(int size)
{
    QFont font;
    if (m_fontId != -1) {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(m_fontId);
        if (!fontFamilies.isEmpty()) {
            font = QFont(fontFamilies.at(0));
        }
    }
    font.setPointSize(size);
    return font;
}

QString FontHelper::iconToString(Icons icon)
{
    return QString(QChar(icon));
} 