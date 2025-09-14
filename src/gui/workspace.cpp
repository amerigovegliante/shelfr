#include "../../headers/gui/workspace.h"

Workspace::Workspace(QWidget* parent) : QFrame(parent)
{
    jsonManager = new JsonManager(this);
    this->setObjectName("workspace");

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 20, 20, 20);

    stackedWidget = new QStackedWidget(this);
    layout->addWidget(stackedWidget);

    // Crea le view
    defaultView = new DefaultView(this);
    addItemView = new AddItemView(jsonManager, this);
    searchItemView = new SearchItemView(jsonManager, this);
    viewItemView = new ViewItemView(this);

    // 🔥 AGGIUNGI LE VIEW NELL'ORDINE CORRETTO
    stackedWidget->addWidget(defaultView);      // Indice 0
    stackedWidget->addWidget(addItemView);      // Indice 1  
    stackedWidget->addWidget(searchItemView);   // Indice 2
    stackedWidget->addWidget(viewItemView);     // Indice 3

    // 🔥 RIMUOVI QUESTE LINEE - LE VIEW HANNO GIÀ IL LORO LAYOUT
    // defaultView->setLayout(new QVBoxLayout());
    // addItemView->setLayout(new QVBoxLayout());
    // searchItemView->setLayout(new QVBoxLayout());
    // searchItemView->layout()->addWidget(new QLabel("This is the Search View", searchItemView));

    // Connessioni
    connect(jsonManager, &JsonManager::mediaDataChanged, this, [this]() {
        qDebug() << "Media data changed, refreshing search view...";
        searchItemView->refresh();
    });
    
    connect(addItemView, &AddItemView::itemAdded, this, [this]() {
        qDebug() << "Item added, refreshing search view...";
        searchItemView->refresh();
    });
    
    connect(searchItemView, &SearchItemView::mediaDeleted, this, [this]() {
        qDebug() << "Media deleted, refreshing search view...";
        searchItemView->refresh();
    });

    connect(searchItemView, &SearchItemView::viewMediaRequested, this, &Workspace::onViewMediaRequested);
    connect(viewItemView, &ViewItemView::backRequested, this, &Workspace::onBackFromViewRequested);

    showDefaultView();
}

void Workspace::showDefaultView()
{
    stackedWidget->setCurrentWidget(defaultView); // 🔥 USA setCurrentWidget invece degli indici
    qDebug() << "Show Default View!";
}

void Workspace::showAddItemView()
{
    stackedWidget->setCurrentWidget(addItemView);
    qDebug() << "Show Add Item View!";
}

void Workspace::showSearchItemView()
{
    stackedWidget->setCurrentWidget(searchItemView);
    qDebug() << "Show Search Item View!";
}

void Workspace::showViewItemView() // 🔥 AGGIUNGI QUESTO METODO
{
    stackedWidget->setCurrentWidget(viewItemView);
    qDebug() << "Show View Item View!";
}

void Workspace::onViewMediaRequested(Media* media)
{
    viewItemView->setMedia(media);
    stackedWidget->setCurrentWidget(viewItemView); // 🔥 USA setCurrentWidget
    qDebug() << "Showing detailed view for:" << media->getTitle();
}

void Workspace::onBackFromViewRequested()
{
    // 🔥 TORNA ALLA VIEW CORRETTA (searchItemView invece di indice fisso)
    stackedWidget->setCurrentWidget(searchItemView);
    viewItemView->clear();
    qDebug() << "Back to search view";
}