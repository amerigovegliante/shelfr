#include "../../headers/gui/workspace.h"
#include <QLabel>

Workspace::Workspace(QWidget* parent) : QFrame(parent)
{
    this->setObjectName("workspace");

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 20, 20, 20);

    stackedWidget = new QStackedWidget(this);
    
    layout->addWidget(stackedWidget);

    addItemView = new QWidget();
    searchItemView = new QWidget();
    addCollectionView = new QWidget();
    searchCollectionView = new QWidget();

    addItemView->setLayout(new QVBoxLayout());
    addItemView->layout()->addWidget(new QLabel("This is the Add Item View", addItemView));

    searchItemView->setLayout(new QVBoxLayout());
    searchItemView->layout()->addWidget(new QLabel("This is the Add Item View", searchItemView));

    addCollectionView->setLayout(new QVBoxLayout());
    addCollectionView->layout()->addWidget(new QLabel("This is the Add Item View", addCollectionView));

    searchCollectionView->setLayout(new QVBoxLayout());
    searchCollectionView->layout()->addWidget(new QLabel("This is the Add Item View", searchCollectionView));

    stackedWidget->addWidget(addItemView);
}