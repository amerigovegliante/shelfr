#include "../../headers/gui/edititemview.h"
#include "../../headers/core/book.h"
#include "../../headers/core/film.h"
#include "../../headers/core/music.h"
#include "../../headers/core/videogame.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>

EditItemView::EditItemView(JsonManager* jsonManager, QWidget *parent)
    : BaseView(parent), media(nullptr), jsonManager(jsonManager)
{
    setupUI();
}

void EditItemView::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    title = new QLabel("Edit Media Item", this);
    title->setStyleSheet("font-size: 18px; font-weight: bold;");
    mainLayout->addWidget(title);

    formLayout = new QFormLayout();
    formLayout->setSpacing(10);

    // campi base
    titleEdit = new QLineEdit(this);
    titleEdit->setEnabled(false);
    genreEdit = new QLineEdit(this);
    yearEdit = new QSpinBox(this);
    yearEdit->setRange(0, INT_MAX);

    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setFixedHeight(60);

    formLayout->addRow("Title:", titleEdit);
    formLayout->addRow("Genre:", genreEdit);
    formLayout->addRow("Year:", yearEdit);
    formLayout->addRow("Description:", descriptionEdit);

    mainLayout->addLayout(formLayout);

    addButton = new QPushButton("Save Changes", this);
    browseImageButton = new QPushButton("Browse Image", this);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(browseImageButton);

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(addButton, &QPushButton::clicked, this, &EditItemView::onSaveChanges);
    connect(browseImageButton, &QPushButton::clicked, this, &EditItemView::onBrowseImageClicked);

}

void EditItemView::onBrowseImageClicked()
{
    QString imagePath = QFileDialog::getOpenFileName(
        this,
        "Select Media Image",
        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
        "Image Files (*.png *.jpg *.jpeg *.bmp *.gif);;All Files (*)"
    );

    if (!imagePath.isEmpty()) {
        currentImagePath = imagePath;
        qDebug() << "Selected image:" << currentImagePath;

        QFileInfo fileInfo(imagePath);
        browseImageButton->setText(fileInfo.fileName());
    }
}


void EditItemView::onSaveChanges()
{
    if (!media) return;

    media->setTitle(titleEdit->text());
    media->setGenre(genreEdit->text());
    media->setYear(yearEdit->value());
    media->setDescription(descriptionEdit->toPlainText());
    media->setImagePath(currentImagePath);

    if (Book* b = dynamic_cast<Book*>(media)) {
        b->setPages(pagesEditBook->value());
        b->setISBN(isbnEditBook->text());
        b->setPublisher(publisherEditBook->text());
        b->setAuthor(authorEditBook->text());
    }
    else if (Film* f = dynamic_cast<Film*>(media)) {
        f->setDuration(durationEditMovie->value());
        f->setRating(ratingEditMovie->value());
        f->setStudio(studioEditMovie->text());
        f->setDirector(directorEditMovie->text());
    }
    else if (Music* mu = dynamic_cast<Music*>(media)) {
        mu->setFormat(formatEditMusic->text());
        mu->setLabel(labelEditMusic->text());
        mu->setDuration(durationEditMusic->value());
    }
    else if (Videogame* vg = dynamic_cast<Videogame*>(media)) {
        vg->setPlatform(platformEditVideogame->text());
        vg->setDeveloper(developerEditVideogame->text());
        vg->setPublisher(publisherEditVideogame->text());
        vg->setPlaytime(playtimeEditVideogame->value());
    }

    qDebug() << "Media updated in UI:" << media->getTitle();

    emit mediaUpdated(media);
}


void EditItemView::setMedia(Media* m)
{
    if(!m) return;

    media = m;

    currentImagePath = media->getImagePath();

    titleEdit->setText(media->getTitle());
    genreEdit->setText(media->getGenre());
    yearEdit->setValue(media->getYear());
    descriptionEdit->setPlainText(media->getDescription());

    while (formLayout->rowCount() > 4) {
        QLayoutItem* itemLabel = formLayout->itemAt(4, QFormLayout::LabelRole);
        QLayoutItem* itemField = formLayout->itemAt(4, QFormLayout::FieldRole);

        if (itemLabel) {
            delete itemLabel->widget();
        }
        if (itemField) {
            delete itemField->widget();
        }

        formLayout->removeRow(4);
    }

    if (Book* b = dynamic_cast<Book*>(media)) {
        pagesEditBook = new QSpinBox(this);
        pagesEditBook->setRange(1, 10000);
        pagesEditBook->setValue(b->getPages());

        isbnEditBook = new QLineEdit(b->getISBN(), this);
        publisherEditBook = new QLineEdit(b->getPublisher(), this);
        authorEditBook = new QLineEdit(b->getAuthor(), this);

        formLayout->addRow("Pages:", pagesEditBook);
        formLayout->addRow("ISBN:", isbnEditBook);
        formLayout->addRow("Publisher:", publisherEditBook);
        formLayout->addRow("Author:", authorEditBook);
    }
    else if (Film* f = dynamic_cast<Film*>(media)) {
        durationEditMovie = new QSpinBox(this);
        durationEditMovie->setRange(1, 600);
        durationEditMovie->setValue(f->getDuration());

        ratingEditMovie = new QSpinBox(this);
        ratingEditMovie->setRange(0, 10);
        ratingEditMovie->setValue(f->getRating());

        studioEditMovie = new QLineEdit(f->getStudio(), this);
        directorEditMovie = new QLineEdit(f->getDirector(), this);

        formLayout->addRow("Duration (min):", durationEditMovie);
        formLayout->addRow("Rating:", ratingEditMovie);
        formLayout->addRow("Studio:", studioEditMovie);
        formLayout->addRow("Director:", directorEditMovie);
    }
    else if (Music* mu = dynamic_cast<Music*>(media)) {
        formatEditMusic = new QLineEdit(mu->getFormat(), this);
        labelEditMusic = new QLineEdit(mu->getLabel(), this);

        durationEditMusic = new QSpinBox(this);
        durationEditMusic->setRange(1, 1000);
        durationEditMusic->setValue(mu->getDuration());

        formLayout->addRow("Format:", formatEditMusic);
        formLayout->addRow("Label:", labelEditMusic);
        formLayout->addRow("Duration:", durationEditMusic);
    }
    else if (Videogame* vg = dynamic_cast<Videogame*>(media)) {
        platformEditVideogame = new QLineEdit(vg->getPlatform(), this);
        developerEditVideogame = new QLineEdit(vg->getDeveloper(), this);
        publisherEditVideogame = new QLineEdit(vg->getPublisher(), this);

        playtimeEditVideogame = new QSpinBox(this);
        playtimeEditVideogame->setRange(0, 10000);
        playtimeEditVideogame->setValue(vg->getPlaytime());

        formLayout->addRow("Platform:", platformEditVideogame);
        formLayout->addRow("Developer:", developerEditVideogame);
        formLayout->addRow("Publisher:", publisherEditVideogame);
        formLayout->addRow("Playtime (h):", playtimeEditVideogame);
    }
    else {
        qDebug() << "Unknown media type in EditItemView";
    }
}
