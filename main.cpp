#include <QApplication>
#include "headers/gui/mainwindow.h"
#include "headers/gui/thememanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Imposta il tema iniziale
    ThemeManager::instance().setTheme(ThemeManager::Dark);
    
    MainWindow mainWindow;
    mainWindow.show();
    
    return app.exec();
}