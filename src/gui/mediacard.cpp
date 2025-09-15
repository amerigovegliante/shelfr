#include "../../headers/gui/mediacard.h"

#include <QVBoxLayout>
#include <QFile>
#include <QMenu>
#include <QMouseEvent>

MediaCard::MediaCard(Media* media, QWidget* parent): QFrame(parent), media(media)
{
    setObjectName("media-card");
    setMinimumWidth(250);
    setMaximumWidth(300);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    
    setupButtons();
    setupUI(); 
    setupContextMenu();
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

    imageLabel = new QLabel();
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setMinimumSize(200, 200);
    imageLabel->setMaximumSize(200, 200);
    imageLabel->setScaledContents(true);

    titleLabel = new QLabel();
    titleLabel->setObjectName("media-title");
    titleLabel->setWordWrap(true);
    titleLabel->setAlignment(Qt::AlignCenter);

    descLabel = new QLabel();
    descLabel->setObjectName("media-description");
    descLabel->setWordWrap(true);

    layout->addWidget(imageLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(descLabel);

    layout->addLayout(buttonLayout);

    updateCard();
}

void MediaCard::updateCard()
{
    if (!media) return;

    if (!media->getImagePath().isEmpty() && QFile::exists(media->getImagePath())) {
        QPixmap pixmap(media->getImagePath());
        imageLabel->setPixmap(pixmap.scaled(imageLabel->width(), imageLabel->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    titleLabel->setText(media->getTitle());

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
        QPoint pos = event->pos();
        if (deleteButton->geometry().contains(pos)) {
        } else if (editButton->geometry().contains(pos)) {
        } else {
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

    editButton = new QPushButton("Edit", this);
    editButton->setObjectName("media-edit-button");

    deleteButton = new QPushButton("Delete", this);
    deleteButton->setObjectName("media-delete-button");

    connect(editButton, &QPushButton::clicked, this, [this]() {
        emit editRequested(media);
    });

    connect(deleteButton, &QPushButton::clicked, this, [this]() {
        emit deleteRequested(media);
    });

    buttonLayout->addWidget(editButton, 1);
    buttonLayout->addWidget(deleteButton, 1);
    buttonLayout->addStretch();
}

MediaCard::~MediaCard() {}

QPushButton* MediaCard::getDeleteButton() const 
{ 
    return deleteButton; 
}