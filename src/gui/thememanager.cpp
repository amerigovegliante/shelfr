#include "../../headers/gui/thememanager.h"
#include <QApplication>
#include <QFile>
#include <QDebug>

ThemeManager& ThemeManager::instance()
{
    static ThemeManager instance;
    return instance;
}

ThemeManager::ThemeManager(QObject *parent) 
    : QObject(parent), m_currentTheme(Dark)
{
    loadTheme(Dark);
}

ThemeManager::Theme ThemeManager::currentTheme() const
{
    return m_currentTheme;
}

void ThemeManager::setTheme(Theme theme)
{
    if (m_currentTheme != theme) {
        m_currentTheme = theme;
        loadTheme(theme);
        emit themeChanged(theme);
    }
}

void ThemeManager::toggleTheme()
{
    setTheme(isDark() ? Light : Dark);
}

void ThemeManager::loadTheme(Theme theme)
{
    QString themeName = (theme == Dark) ? "dark" : "light";

    QFile file(QString(":/styles/%1.css").arg(themeName));
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString styleSheet = QString::fromUtf8(file.readAll());
        qApp->setStyleSheet(styleSheet);
        file.close();
        
        qDebug() << "Theme loaded:" << themeName;
    } else {
        qWarning() << "Cannot load theme:" << themeName << file.errorString();
    }
}

bool ThemeManager::isDark() const
{
    return m_currentTheme == Dark;
}

bool ThemeManager::isLight() const
{
    return m_currentTheme == Light;
}