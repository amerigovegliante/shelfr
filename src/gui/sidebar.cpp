#include "../../headers/gui/sidebar.h"
#include <QDebug>

Sidebar::Sidebar(QWidget* parent) : QFrame(parent)
{
    this->setObjectName("sidebar");
    this->setFrameStyle(QFrame::Box);
    this->setLineWidth(1);
    this->setFixedWidth(200);

    layout = new QVBoxLayout(this);
    layout->setSpacing(10);
    layout->setContentsMargins(10, 10, 10, 10);

    addItemButton = new QPushButton("Add Item", this);
    searchItemButton = new QPushButton("Search Item", this);
    addCollectionButton = new QPushButton("Add Collection", this);
    searchCollectionButton = new QPushButton("Search Collection", this);

    layout->addWidget(addItemButton);
    layout->addWidget(searchItemButton);
    layout->addWidget(addCollectionButton);
    layout->addWidget(searchCollectionButton);
    
    layout->addStretch();

    connect(addItemButton, &QPushButton::clicked, this, &Sidebar::addItemClicked);
    connect(searchItemButton, &QPushButton::clicked, this, &Sidebar::searchItemClicked);
    connect(addCollectionButton, &QPushButton::clicked, this, &Sidebar::addCollectionClicked);
    connect(searchCollectionButton, &QPushButton::clicked, this, &Sidebar::searchCollectionClicked);
}
