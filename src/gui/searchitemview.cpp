#include "../../headers/gui/searchitemview.h"

#include "../../headers/gui/mediacardvisitor.h"
#include "../../headers/gui/mediafiltervisitor.h"
#include "../../headers/core/media.h"
#include "../../headers/core/book.h"
#include "../../headers/core/film.h"
#include "../../headers/core/music.h"
#include "../../headers/core/videogame.h"
#include "../../headers/gui/mediacard.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>

SearchItemView::SearchItemView(JsonManager* jsonManager, QWidget* parent)
    : QWidget(parent), jsonManager(jsonManager), gridLayout(nullptr)
{
    setupUI();
    loadMediaItems();
}

SearchItemView::~SearchItemView()
{
    clearLayout();
    clearMediaList();
}

void SearchItemView::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(20);

    QLabel* titleLabel = new QLabel("Search Media Items", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("view-title");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

    // Barra di ricerca
    QHBoxLayout* searchLayout = new QHBoxLayout();
    searchLayout->setSpacing(10);
    
    QLabel* searchLabel = new QLabel("Search:", this);
    searchLabel->setFixedWidth(60);
    
    searchLineEdit = new QLineEdit(this);
    searchLineEdit->setPlaceholderText("Enter title to search...");
    searchLineEdit->setClearButtonEnabled(true);
    
    clearSearchButton = new QPushButton("Clear", this);
    clearSearchButton->setFixedWidth(80);
    clearSearchButton->setObjectName("clear-search-btn");

    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchLineEdit);
    searchLayout->addWidget(clearSearchButton);

    // Scroll area con GridLayout
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    
    scrollWidget = new QWidget();
    gridLayout = new QGridLayout(scrollWidget);
    gridLayout->setSpacing(20);
    gridLayout->setContentsMargins(15, 15, 15, 15);
    gridLayout->setAlignment(Qt::AlignTop);
    
    scrollArea->setWidget(scrollWidget);

    // Aggiungi tutto al layout principale
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(scrollArea);

    // Connessioni
    connect(searchLineEdit, &QLineEdit::textChanged, this, &SearchItemView::onSearchTextChanged);
    connect(clearSearchButton, &QPushButton::clicked, this, &SearchItemView::onClearSearchClicked);
}

void SearchItemView::onDeleteMediaRequested(Media* mediaToDelete)
{
    
    // 🔥 VERIFICA CHE IL MEDIA SIA NELLA LISTA
    if (!allMediaList.contains(mediaToDelete)) {
        qWarning() << "Media not in allMediaList:" << mediaToDelete;
        return;
    }

    // Conferma la delete
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Delete", 
                                "Delete '" + mediaToDelete->getTitle() + "'?",
                                QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::No) return;

    // 🔥 APPROCCIO SICURO: RIMUOVI PRIMA DAI DATI, POI DALLA UI
    try {
        // 1. Rimuovi dalle LISTE prima di eliminare
        allMediaList.removeOne(mediaToDelete);
        mediaList.removeOne(mediaToDelete);
        visibleMediaList.removeOne(mediaToDelete);

        // 2. Rimuovi la CARD dalla mappa e dal layout
        MediaCard* card = mediaCardMap.take(mediaToDelete);
        if (card) {
            disconnect(card, nullptr, this, nullptr);
            gridLayout->removeWidget(card);
            card->deleteLater(); // 🔥 DELETE LATER è più sicuro
        }

        // 3. Elimina il MEDIA
        delete mediaToDelete;
        mediaToDelete = nullptr; // 🔥 IMPORTANTE: imposta a nullptr

        // 4. Ricostruisci il layout
        rebuildGridLayout();

        // 5. 🔥 SALVA IL JSON (approccio più sicuro)
        jsonManager->loadFromFile(); // Ricarica i dati attuali
        jsonManager->saveToFile();   // Risalva

        qDebug() << "=== DELETE SUCCESSFUL ===";

    } catch (const std::exception& e) {
        qCritical() << "Exception during delete:" << e.what();
    } catch (...) {
        qCritical() << "Unknown exception during delete";
    }

    QJsonArray newArray;
    for (Media* media : allMediaList) {
        // Converti ogni media in JSON e aggiungi all'array
        QJsonObject json = jsonManager->convertMediaToJson(media);
        newArray.append(json);
    }
    
    jsonManager->replaceMediaArray(newArray);
}



void SearchItemView::removeMediaFromLayout(Media* media)
{
    MediaCard* card = mediaCardMap.value(media);
    if (!card) return;
    
    // Rimuovi la card dal layout
    gridLayout->removeWidget(card);
    
    // Ricostruisci il layout senza buchi
    rebuildGridLayout();
}

void SearchItemView::onSearchTextChanged(const QString& text)
{
    filterMediaByTitle(text);
}

void SearchItemView::onClearSearchClicked()
{
    searchLineEdit->clear();
    loadMediaItems();
}

void SearchItemView::refresh()
{
    qDebug() << "Refreshing SearchItemView...";
    loadMediaItems();
}

void SearchItemView::loadMediaItems()
{
    // Pulisci tutto prima di ricaricare
    clearLayout();
    clearMediaList();

    QJsonArray jsonArray = jsonManager->getMedia();
    MediaCardVisitor cardVisitor(scrollWidget);
    
    int row = 0;
    int col = 0;
    const int maxColumns = 3;
    
    for (const QJsonValue &value : jsonArray) {
        QJsonObject mediaObj = value.toObject();
        
        Media* media = jsonManager->createMediaFromJson(mediaObj);
        if (!media) continue;
        
        mediaList.append(media);
        allMediaList.append(media);
        visibleMediaList.append(media);
        
        media->accept(cardVisitor);
        MediaCard* card = cardVisitor.getCard();
        
        if (card) {
            gridLayout->addWidget(card, row, col);
            mediaCardMap[media] = card;
            
            // Connessioni UNICHE
            connect(card, &MediaCard::deleteRequested, this, &SearchItemView::onDeleteMediaRequested, Qt::UniqueConnection);
            connect(card, &MediaCard::editRequested, this, [this](Media* mediaToEdit) {
                qDebug() << "Edit requested:" << mediaToEdit->getTitle();
                // Qui gestisci l'edit
            }, Qt::UniqueConnection);
            
            connect(card, &MediaCard::clicked, this, [this](Media* clickedMedia) {
                qDebug() << "Media clicked:" << clickedMedia->getTitle();
            }, Qt::UniqueConnection);
            connect(card, &MediaCard::viewRequested, this, &SearchItemView::onViewMediaRequested);
            col++;
            if (col >= maxColumns) {
                col = 0;
                row++;
            }
        }
    }
}

// ... (createMediaFromJson rimane uguale) ...

void SearchItemView::filterMediaByTitle(const QString& searchText)
{
    if (searchText.isEmpty()) {
        visibleMediaList = allMediaList;
        rebuildGridLayout();
        return;
    }

    MediaFilterVisitor filterVisitor(searchText);
    visibleMediaList.clear();
    
    for (Media* media : allMediaList) {
        media->accept(filterVisitor);
        if (filterVisitor.matches()) {
            visibleMediaList.append(media);
        }
    }
    
    rebuildGridLayout();
}

void SearchItemView::rebuildGridLayout()
{
    // Rimuovi tutti gli elementi dal layout senza eliminarli
    QLayoutItem* item;
    while ((item = gridLayout->takeAt(0)) != nullptr) {
        delete item; // Solo l'item del layout, non il widget
    }

    // Riaggiungi i widget visibili mantenendo le card esistenti
    int row = 0;
    int col = 0;
    const int maxColumns = 3;

    for (Media* media : visibleMediaList) {
        MediaCard* card = mediaCardMap.value(media);
        if (card) {
            gridLayout->addWidget(card, row, col);
            
            col++;
            if (col >= maxColumns) {
                col = 0;
                row++;
            }
        }
    }
}

void SearchItemView::clearLayout()
{
    if (!gridLayout) return;
    
    // 🔥 DISCONNETTI TUTTE LE CONNESSIONI PRIMA
    QList<MediaCard*> cards = mediaCardMap.values();
    for (MediaCard* card : cards) {
        if (card) {
            disconnect(card, nullptr, this, nullptr);
            gridLayout->removeWidget(card);
            card->setParent(nullptr); // Rimuovi dal layout ma NON eliminare
        }
    }
    
    mediaCardMap.clear();
}

void SearchItemView::clearMediaList()
{
    // 🔥 Elimina SOLO i media, le card saranno eliminate dal clearLayout
    for (Media* media : mediaList) {
        if (media) {
            delete media;
        }
    }
    mediaList.clear();
    allMediaList.clear();
    visibleMediaList.clear();
}


void SearchItemView::onViewMediaRequested(Media* media)
{
    qDebug() << "View requested for:" << media->getTitle();
    emit viewMediaRequested(media);  // Inoltra alla Workspace
}