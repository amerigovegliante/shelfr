#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QString>

class ThemeManager : public QObject
{
    Q_OBJECT

public:
    enum Theme { Light, Dark };
    Q_ENUM(Theme)

    static ThemeManager& instance();

    Theme currentTheme() const;
    void setTheme(Theme theme);
    void toggleTheme();

    bool isDark() const;
    bool isLight() const;

signals:
    void themeChanged(Theme newTheme);

private:
    ThemeManager(QObject *parent = nullptr);
    void loadTheme(Theme theme);

    Theme m_currentTheme;
};

#endif // THEMEMANAGER_H