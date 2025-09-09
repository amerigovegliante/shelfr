#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sidebar.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void onAddItemClicked();
        void onSearchItemClicked();
        void onAddCollectionClicked();
        void onSearchCollectionClicked();
    
    private:
        Sidebar *sidebar;

};

#endif // MAINWINDOW