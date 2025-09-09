#include "../../headers/gui/sidebar.h"
#include "../../headers/gui/thememanager.h"
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <QLabel>
#include <QHBoxLayout>

Sidebar::Sidebar(QWidget* parent) : QFrame(parent)
{
    this->setObjectName("sidebar");
    this->setFrameStyle(QFrame::Box);
    this->setLineWidth(1);
    this->setFixedWidth(300);

    layout = new QVBoxLayout(this);
    layout->setSpacing(10);
    layout->setContentsMargins(10, 10, 10, 10);

    addItemButton = new QPushButton("Add Item", this);
    searchItemButton = new QPushButton("Search Item", this);
    addCollectionButton = new QPushButton("Add Collection", this);
    searchCollectionButton = new QPushButton("Search Collection", this);
    
    themeSwitch = new QCheckBox(this);
    themeSwitch->setChecked(ThemeManager::instance().isDark());
    themeLabel = new QLabel((ThemeManager::instance().isDark()) ? "Dark" : "Light", this);
    
    themeLabel->setObjectName("theme-label");

    themeLayout = new QHBoxLayout();

    title = new QLabel("Shelfr", this);

    title->setObjectName("title");
    title->setAlignment(Qt::AlignCenter);

    themeLayout->addWidget(themeSwitch);
    themeLayout->addWidget(themeLabel);
    themeLayout->setAlignment(Qt::AlignHCenter);
    themeLayout->addStretch();
    
    layout->addWidget(title);
    layout->addWidget(addItemButton);
    layout->addWidget(searchItemButton);
    layout->addWidget(addCollectionButton);
    layout->addWidget(searchCollectionButton);
    
    layout->addStretch();

    layout->addLayout(themeLayout);

    connect(themeSwitch, &QCheckBox::toggled, this, &Sidebar::onThemeToggled);
    connect(&ThemeManager::instance(), &ThemeManager::themeChanged,this, &Sidebar::onThemeChanged);

    connect(addItemButton, &QPushButton::clicked, this, &Sidebar::addItemClicked);
    connect(searchItemButton, &QPushButton::clicked, this, &Sidebar::searchItemClicked);
    connect(addCollectionButton, &QPushButton::clicked, this, &Sidebar::addCollectionClicked);
    connect(searchCollectionButton, &QPushButton::clicked, this, &Sidebar::searchCollectionClicked);
}

void Sidebar::onThemeToggled(bool checked)
{
    ThemeManager::instance().setTheme(checked ? ThemeManager::Dark : ThemeManager::Light);
}

void Sidebar::onThemeChanged(ThemeManager::Theme theme)
{
    bool isDark = (theme == ThemeManager::Dark);
    themeLabel->setText(isDark ? "Dark" : "Light");
}