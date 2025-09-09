#include <QApplication>
#include <QFile>
#include <QDebug>
#include "headers/gui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Carica il CSS
    QFile styleFile(":/styles/style.css");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        app.setStyleSheet(styleSheet);
        qDebug() << "CSS loaded successfully";
        styleFile.close();
    } else {
        qDebug() << "Failed to load CSS file";
    }
    
    MainWindow mainWindow;
    mainWindow.show();
    
    return app.exec();
}