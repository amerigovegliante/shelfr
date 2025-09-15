#include "../../headers/gui/viewitemview.h"
#include "../../headers/core/book.h"
#include "../../headers/core/film.h"
#include "../../headers/core/music.h"
#include "../../headers/core/videogame.h"
#include <QDebug>
#include <QFile>

ViewItemView::ViewItemView(QWidget* parent) 
    : BaseView(parent), currentMedia(nullptr)
{
    setupUI();
}

void ViewItemView::setupUI()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    headerLayout = new QHBoxLayout();
    
    backButton = new QPushButton("← Back", this);
    backButton->setFixedWidth(100);
    
    titleLabel = new QLabel("Media Details", this);
    titleLabel->setObjectName("view-title");
    titleLabel->setAlignment(Qt::AlignCenter);
    
    headerLayout->addWidget(backButton);
    headerLayout->addStretch();
    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(new QLabel("")); 

    contentLayout = new QHBoxLayout();
    
    QVBoxLayout* leftLayout = new QVBoxLayout();
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setMinimumSize(300, 300);
    imageLabel->setMaximumSize(400, 400);
    imageLabel->setScaledContents(true);
    imageLabel->setStyleSheet("border: 2px solid #ccc; border-radius: 10px;");
    leftLayout->addWidget(imageLabel);
    leftLayout->addStretch();

    QVBoxLayout* rightLayout = new QVBoxLayout();
    
    typeLabel = new QLabel(this);
    typeLabel->setObjectName("media-type");
    
    yearLabel = new QLabel(this);
    genreLabel = new QLabel(this);
    
    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setReadOnly(true);
    descriptionEdit->setMaximumHeight(100);
    descriptionEdit->setObjectName("media-description");
    
    detailsEdit = new QTextEdit(this);
    detailsEdit->setReadOnly(true);
    detailsEdit->setObjectName("media-details");
    
    rightLayout->addWidget(typeLabel);
    rightLayout->addWidget(yearLabel);
    rightLayout->addWidget(genreLabel);
    rightLayout->addWidget(new QLabel("Description:"));
    rightLayout->addWidget(descriptionEdit);
    rightLayout->addWidget(new QLabel("Details:"));
    rightLayout->addWidget(detailsEdit);

    contentLayout->addLayout(leftLayout);
    contentLayout->addLayout(rightLayout);

    mainLayout->addLayout(headerLayout);
    mainLayout->addLayout(contentLayout);

    connect(backButton, &QPushButton::clicked, this, &ViewItemView::backRequested);
}

void ViewItemView::setMedia(Media* media)
{
    currentMedia = media;
    updateView();
}

void ViewItemView::clear()
{
    currentMedia = nullptr;
    titleLabel->setText("Media Details");
    typeLabel->clear();
    yearLabel->clear();
    genreLabel->clear();
    descriptionEdit->clear();
    detailsEdit->clear();
    imageLabel->clear();
    imageLabel->setPixmap(QPixmap());
}

void ViewItemView::updateView()
{
    if (!currentMedia) {
        clear();
        return;
    }

    titleLabel->setText(currentMedia->getTitle());
    typeLabel->setText("Type: " + currentMedia->getType());
    yearLabel->setText("Year: " + QString::number(currentMedia->getYear()));
    genreLabel->setText("Genre: " + currentMedia->getGenre());
    descriptionEdit->setText(currentMedia->getDescription());

    if (!currentMedia->getImagePath().isEmpty() && QFile::exists(currentMedia->getImagePath())) {
        QPixmap pixmap(currentMedia->getImagePath());
        imageLabel->setPixmap(pixmap.scaled(imageLabel->width(), imageLabel->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    detailsEdit->setText(formatMediaDetails(currentMedia));
}

QString ViewItemView::formatMediaDetails(Media* media)
{
    QString details;
    
    if (Book* book = dynamic_cast<Book*>(media)) {
        details = QString("Author: %1\nPages: %2\nISBN: %3\nPublisher: %4")
            .arg(book->getAuthor())
            .arg(book->getPages())
            .arg(book->getISBN())
            .arg(book->getPublisher());
    }
    else if (Film* film = dynamic_cast<Film*>(media)) {
        details = QString("Director: %1\nDuration: %2 minutes\nRating: %3/5\nStudio: %4")
            .arg(film->getDirector())
            .arg(film->getDuration())
            .arg(film->getRating())
            .arg(film->getStudio());
    }
    else if (Music* music = dynamic_cast<Music*>(media)) {
        details = QString("Duration: %1 minutes\nFormat: %2\nLabel: %3")
            .arg(music->getDuration())
            .arg(music->getFormat())
            .arg(music->getLabel());
    }
    else if (Videogame* game = dynamic_cast<Videogame*>(media)) {
        details = QString("Developer: %1\nPlatform: %2\nPublisher: %3\nPlaytime: %4 hours")
            .arg(game->getDeveloper())
            .arg(game->getPlatform())
            .arg(game->getPublisher())
            .arg(game->getPlaytime());
    }
    
    return details;
}