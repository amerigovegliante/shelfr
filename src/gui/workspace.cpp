#include "../../headers/gui/workspace.h"

Workspace::Workspace(QWidget* parent) : QFrame(parent)
{
    jsonManager = new JsonManager(this);
    this->setObjectName("workspace");

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 20, 20, 20);

    stackedWidget = new QStackedWidget(this);
    layout->addWidget(stackedWidget);

    defaultView = new DefaultView(this);
    addItemView = new AddItemView(jsonManager, this);
    searchItemView = new SearchItemView(jsonManager, this);
    viewItemView = new ViewItemView(this);
    editItemView = new EditItemView(jsonManager,this);

    stackedWidget->addWidget(defaultView);      
    stackedWidget->addWidget(addItemView);      
    stackedWidget->addWidget(searchItemView);  
    stackedWidget->addWidget(viewItemView);    
    stackedWidget->addWidget(editItemView);

    connect(jsonManager, &JsonManager::mediaDataChanged, this, [this]() {
        searchItemView->refresh();
    });
    
    connect(addItemView, &AddItemView::itemAdded, this, [this]() {
        searchItemView->refresh();
    });
    
    connect(searchItemView, &SearchItemView::mediaDeleted, this, [this]() {
        searchItemView->refresh();
    });

    connect(searchItemView, &SearchItemView::viewMediaRequested, this, &Workspace::onViewMediaRequested);
    connect(viewItemView, &ViewItemView::backRequested, this, &Workspace::onBackFromViewRequested);

    connect(searchItemView, &SearchItemView::editMediaRequested,this, &Workspace::onEditMediaRequested);

    connect(editItemView, &EditItemView::mediaUpdated, this, [this](Media* updated) {
    if (updated) {
        jsonManager->updateMedia(updated);
        jsonManager->saveToFile();
        searchItemView->refresh();  
        showSearchItemView();       
    }
});


    showDefaultView();
}

void Workspace::onEditMediaRequested(Media* media) {
    editItemView->setMedia(media);
    stackedWidget->setCurrentWidget(editItemView);
}

void Workspace::showDefaultView()
{
    stackedWidget->setCurrentWidget(defaultView); 
}

void Workspace::showAddItemView()
{
    stackedWidget->setCurrentWidget(addItemView);
}

void Workspace::showSearchItemView()
{
    stackedWidget->setCurrentWidget(searchItemView);
}

void Workspace::showViewItemView()
{
    stackedWidget->setCurrentWidget(viewItemView);
}

void Workspace::onViewMediaRequested(Media* media)
{
    viewItemView->setMedia(media);
    stackedWidget->setCurrentWidget(viewItemView); 
}

void Workspace::onBackFromViewRequested()
{
    stackedWidget->setCurrentWidget(searchItemView);
    viewItemView->clear();
}