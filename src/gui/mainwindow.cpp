#include "../../headers/gui/mainwindow.h"
#include "../../headers/gui/workspace.h"

#include <QHBoxLayout>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Shelfr - Media Library");
    resize(1280, 720);

    QSplitter* mainSplitter = new QSplitter(Qt::Horizontal, this);

    sidebar = new Sidebar(mainSplitter);
    workspace = new Workspace(mainSplitter);

    sidebar->setMinimumWidth(200);
    sidebar->setMaximumWidth(300);
    
    workspace->setMinimumWidth(400);

    mainSplitter->addWidget(sidebar);
    mainSplitter->addWidget(workspace);
    mainSplitter->setSizes({200,1000});

    mainSplitter->setHandleWidth(2);
    mainSplitter->setChildrenCollapsible(true);

    connect(sidebar, &Sidebar::addItemClicked, this, &MainWindow::onAddItemClicked);
    connect(sidebar, &Sidebar::searchItemClicked, this, &MainWindow::onSearchItemClicked);

    setCentralWidget(mainSplitter);

}

MainWindow::~MainWindow(){}

void MainWindow::onAddItemClicked()
{
    workspace->showAddItemView();
}

void MainWindow::onSearchItemClicked()
{
    workspace->showSearchItemView();
}