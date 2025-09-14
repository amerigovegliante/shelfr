#include "../../headers/gui/mediacard.h"

#include <QVBoxLayout>
#include <QFile>
#include <QMenu>
#include <QMouseEvent>
#include <QDebug>

MediaCard::MediaCard(Media* media, QWidget* parent): QFrame(parent), media(media)
{
    setObjectName("media-card");
    setMinimumWidth(250);
    setMaximumWidth(300);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    
    setupButtons();    // Prima crea i bottoni
    setupUI();         // Poi setupUI che aggiunge buttonLayout al layout
    setupContextMenu(); // Infine il context menu
} 

void MediaCard::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
}

void MediaCard::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(10);
    layout->setContentsMargins(15, 15, 15, 15);

    // Immagine
    imageLabel = new QLabel();
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setMinimumSize(200, 200);
    imageLabel->setMaximumSize(200, 200);
    imageLabel->setScaledContents(true);

    // Titolo
    titleLabel = new QLabel();
    titleLabel->setObjectName("media-title");
    titleLabel->setWordWrap(true);
    titleLabel->setAlignment(Qt::AlignCenter);

    // Descrizione
    descLabel = new QLabel();
    descLabel->setObjectName("media-description");
    descLabel->setWordWrap(true);

    layout->addWidget(imageLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(descLabel);

    // 🔥 IMPORTANTE: aggiungi il layout dei bottoni
    layout->addLayout(buttonLayout);

    updateCard();
}

void MediaCard::updateCard()
{
    if (!media) return;

    // Immagine
    if (!media->getImagePath().isEmpty() && QFile::exists(media->getImagePath())) {
        QPixmap pixmap(media->getImagePath());
        imageLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        imageLabel->setPixmap(QPixmap(":/images/default_media.png").scaled(200, 200));
    }

    // Titolo
    titleLabel->setText(media->getTitle());

    // Descrizione
    QString description = media->getDescription();
    if (description.length() > 100) {
        description = description.left(100) + "...";
    }
    descLabel->setText(description);
}

Media* MediaCard::getMedia() const
{
    return media;
}

void MediaCard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Verifica se il click è su un bottone
        QPoint pos = event->pos();
        if (deleteButton->geometry().contains(pos)) {
            // Click sul bottone delete - già gestito
        } else if (editButton->geometry().contains(pos)) {
            // Click sul bottone edit - già gestito
        } else {
            // Click sulla card - emetti viewRequested
            emit viewRequested(media);
        }
    }
    QFrame::mousePressEvent(event);
}

void MediaCard::setupContextMenu()
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    
    connect(this, &MediaCard::customContextMenuRequested, [this](const QPoint &pos) {
        QMenu menu(this);
        
        QAction *editAction = menu.addAction("Edit");
        QAction *deleteAction = menu.addAction("Delete");
        
        connect(editAction, &QAction::triggered, [this]() {
            emit editRequested(media);
        });
        
        connect(deleteAction, &QAction::triggered, [this]() {
            qDebug() << "Context menu delete for:" << media->getTitle();
            emit deleteRequested(media);
        });
        
        menu.exec(mapToGlobal(pos));
    });
}

void MediaCard::setupButtons()
{
    buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(5);
    buttonLayout->setContentsMargins(0, 10, 0, 0);

    // Bottone Edit
    editButton = new QPushButton("Edit", this);
    editButton->setObjectName("media-edit-button");

    // Bottone Delete
    deleteButton = new QPushButton("Delete", this);
    deleteButton->setObjectName("media-delete-button");

    connect(editButton, &QPushButton::clicked, this, [this]() {
        qDebug() << "Edit button clicked for:" << media->getTitle();
        emit editRequested(media);
    });

    connect(deleteButton, &QPushButton::clicked, this, [this]() {
        qDebug() << "=== DELETE BUTTON CLICKED ===";
        qDebug() << "Media:" << media->getTitle();
        emit deleteRequested(media);
    });

    buttonLayout->addWidget(editButton, 1);
    buttonLayout->addWidget(deleteButton, 1);
    buttonLayout->addStretch();

    // Debug per verificare che i bottoni siano creati
    qDebug() << "MediaCard buttons created for:" << media->getTitle();
}

MediaCard::~MediaCard() {}

QPushButton* MediaCard::getDeleteButton() const 
{ 
    return deleteButton; 
}