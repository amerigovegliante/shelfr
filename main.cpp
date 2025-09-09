#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "headers/gui/mainwindow.h"
#include "headers/gui/thememanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ThemeManager::instance().setTheme(ThemeManager::Dark);  // Puoi anche usare ThemeManager::Light

    MainWindow mainWindow;
    mainWindow.show();
    
    return app.exec();
}
