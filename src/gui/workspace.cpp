#include "../../headers/gui/workspace.h"
#include <QLabel>

Workspace::Workspace(QWidget* parent) : QFrame(parent)
{
    this->setObjectName("workspace");

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 20, 20, 20);

    stackedWidget = new QStackedWidget(this);
    
    layout->addWidget(stackedWidget);

    defaultView = new DefaultView(this);
    addItemView = new AddItemView(this);
    searchItemView = new QWidget();
    addCollectionView = new QWidget();
    searchCollectionView = new QWidget();

    defaultView->setLayout(new QVBoxLayout());

    addItemView->setLayout(new QVBoxLayout());

    searchItemView->setLayout(new QVBoxLayout());
    searchItemView->layout()->addWidget(new QLabel("This is the Search View", searchItemView));

    addCollectionView->setLayout(new QVBoxLayout());
    addCollectionView->layout()->addWidget(new QLabel("This is the Add Collection View", addCollectionView));

    searchCollectionView->setLayout(new QVBoxLayout());
    searchCollectionView->layout()->addWidget(new QLabel("This is the Search Collection View", searchCollectionView));

    stackedWidget->addWidget(defaultView);
    stackedWidget->addWidget(addItemView);
    stackedWidget->addWidget(searchItemView);
    stackedWidget->addWidget(addCollectionView);
    stackedWidget->addWidget(searchCollectionView);

    showDefaultView();
}

void Workspace::showDefaultView()
{
    Workspace::stackedWidget->setCurrentIndex(0);
    qDebug() << "Show Default View!";
}

void Workspace::showAddItemView()
{
    Workspace::stackedWidget->setCurrentIndex(1);
    qDebug() << "Show Add Item View!";
}

void Workspace::showSearchItemView()
{
    Workspace::stackedWidget->setCurrentIndex(2);
    qDebug() << "Show Search Item View!";
}

void Workspace::showAddCollectionView()
{
    Workspace::stackedWidget->setCurrentIndex(3);
    qDebug() << "Show Add Collection View!";
}

void Workspace::showSearchCollectionView()
{
    Workspace::stackedWidget->setCurrentIndex(4);
    qDebug() << "Show Search Collection View!";
}