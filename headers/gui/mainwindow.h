#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sidebar.h"
#include "workspace.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void onAddItemClicked();
        void onSearchItemClicked();
    
    private:
        Sidebar* sidebar;
        Workspace* workspace;
};

#endif // MAINWINDOW