#include "../../headers/gui/mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Shelfr - Media Library");
    resize(1280, 720);

    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    sidebar = new Sidebar(centralWidget);
    
    mainLayout->addWidget(sidebar);
    mainLayout->addStretch();

    connect(sidebar, &Sidebar::addItemClicked, this, &MainWindow::onAddItemClicked);
    connect(sidebar, &Sidebar::searchItemClicked, this, &MainWindow::onSearchItemClicked);
    connect(sidebar, &Sidebar::addCollectionClicked, this, &MainWindow::onAddCollectionClicked);
    connect(sidebar, &Sidebar::searchCollectionClicked, this, &MainWindow::onSearchCollectionClicked);

    setCentralWidget(centralWidget);
    
    qDebug() << "MainWindow created";
}

MainWindow::~MainWindow(){}

void MainWindow::onAddItemClicked()
{
    qDebug() << "add item clicked";
}

void MainWindow::onSearchItemClicked()
{
    qDebug() << "search item clicked";
}

void MainWindow::onAddCollectionClicked()
{
    qDebug() << "add collection clicked";
}

void MainWindow::onSearchCollectionClicked()
{
    qDebug() <<"search collection clicked";
}