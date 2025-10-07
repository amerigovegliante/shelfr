#include "../../headers/gui/additemview.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>

AddItemView::AddItemView(JsonManager* jsonManager, QWidget* parent) 
    : BaseView(parent), jsonManager(jsonManager) // Inizializza il puntatore
{
    setupUI();
    setupConnections();
}

void AddItemView::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    QLabel *formTitleLabel = new QLabel("Add New Media Item", this);
    formTitleLabel->setObjectName("view-title");
    formTitleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(formTitleLabel);

    mediaTypeCombo = new QComboBox(this);
    mediaTypeCombo->addItems({"Book", "Film", "Music", "Video Game"});
    
    titleEdit = new QLineEdit(this);
    titleEdit->setPlaceholderText("Insert Title...");

    genreEdit = new QLineEdit(this);
    genreEdit->setPlaceholderText("Insert Genre...");

    yearEdit = new QSpinBox(this);
    yearEdit->setRange(0, QDate::currentDate().year());
    yearEdit->setSpecialValueText("Insert Year...");

    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setMaximumHeight(100);
    descriptionEdit->setPlaceholderText("Insert Description...");

    browseImageButton = new QPushButton("Select Image...", this);

    addButton = new QPushButton("Save...",this);
    addButton->setIcon(QIcon(":/icons/save.png"));
    addButton->setIconSize(QSize(24,24));
    addButton->setObjectName("media-save-button");

    browseImageButton->setObjectName("imagebrowser");

    pagesEditBook = new QSpinBox(this);
    pagesEditBook->setMinimum(0);
    pagesEditBook->setMaximum(INT_MAX);
    pagesEditBook->setSpecialValueText("Pages...");
    isbnEditBook = new QLineEdit(this);
    isbnEditBook->setPlaceholderText("ISBN...");
    publisherEditBook = new QLineEdit(this);
    publisherEditBook->setPlaceholderText("Publisher...");
    authorEditBook = new QLineEdit(this);
    authorEditBook->setPlaceholderText("Author...");

    durationEditMovie = new QSpinBox(this);
    durationEditMovie->setMinimum(0);
    durationEditMovie->setMaximum(INT_MAX);
    durationEditMovie->setSpecialValueText("Duration (minutes)...");
    ratingEditMovie = new QSpinBox(this);
    ratingEditMovie->setMinimum(1);
    ratingEditMovie->setMaximum(5);
    ratingEditMovie->setSpecialValueText("Rating...");
    studioEditMovie = new QLineEdit(this);
    studioEditMovie->setPlaceholderText("Studio...");
    directorEditMovie = new QLineEdit(this);
    directorEditMovie->setPlaceholderText("Director...");
    formatEditMusic = new QLineEdit(this);
    formatEditMusic->setPlaceholderText("Format...");
    labelEditMusic = new QLineEdit(this);
    labelEditMusic->setPlaceholderText("Label...");
    durationEditMusic = new QSpinBox(this);
    durationEditMusic->setMinimum(0);
    durationEditMusic->setMaximum(INT_MAX);
    durationEditMusic->setSpecialValueText("Duration (minutes)...");
    platformEditVideogame = new QLineEdit(this);
    platformEditVideogame->setPlaceholderText("Platform...");
    developerEditVideogame = new QLineEdit(this);
    developerEditVideogame->setPlaceholderText("Developer...");
    publisherEditVideogame = new QLineEdit(this);
    publisherEditVideogame->setPlaceholderText("Publisher...");
    playtimeEditVideogame = new QSpinBox(this);
    playtimeEditVideogame->setSpecialValueText("Playtime (hours)...");

    QFormLayout *formLayout = new QFormLayout();    

    formLayout->addRow(mediaTypeCombo);
    formLayout->addRow(browseImageButton);
    formLayout->addRow(genreEdit, titleEdit);
    formLayout->addRow(descriptionEdit);
    formLayout->addRow(yearEdit);

    formLayout->addRow(pagesEditBook, isbnEditBook);
    formLayout->addRow(publisherEditBook, authorEditBook);

    formLayout->addRow(durationEditMovie, ratingEditMovie);
    formLayout->addRow(studioEditMovie, directorEditMovie);
    
    formLayout->addRow(formatEditMusic);
    formLayout->addRow(labelEditMusic, durationEditMusic);
    
    formLayout->addRow(platformEditVideogame, developerEditVideogame);
    formLayout->addRow(publisherEditVideogame, playtimeEditVideogame);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(addButton);
    mainLayout->addStretch();
    
    toggleFields();
}

void AddItemView::setupConnections()
{
    connect(mediaTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),this, &AddItemView::onMediaTypeChanged);
    connect(addButton, &QPushButton::clicked, this, &AddItemView::onAddButtonClicked);
    connect(browseImageButton, &QPushButton::clicked, this, &AddItemView::onBrowseImageClicked);
}

void AddItemView::onMediaTypeChanged(int index)
{
    Q_UNUSED(index);
    toggleFields();
}

void AddItemView::toggleFields()
{
    QString mediaType = mediaTypeCombo->currentText();

    pagesEditBook->setVisible(false);
    isbnEditBook->setVisible(false);
    publisherEditBook->setVisible(false);
    authorEditBook->setVisible(false);

    durationEditMovie->setVisible(false);
    ratingEditMovie->setVisible(false);
    studioEditMovie->setVisible(false);
    directorEditMovie->setVisible(false);

    formatEditMusic->setVisible(false);
    labelEditMusic->setVisible(false);
    durationEditMusic->setVisible(false);

    platformEditVideogame->setVisible(false);
    developerEditVideogame->setVisible(false);
    publisherEditVideogame->setVisible(false);
    playtimeEditVideogame->setVisible(false);
    
    if (mediaType == "Book") {
        pagesEditBook->setVisible(true);
        isbnEditBook->setVisible(true);
        publisherEditBook->setVisible(true);
        authorEditBook->setVisible(true);
        durationEditMovie->setVisible(false);
        ratingEditMovie->setVisible(false);
        studioEditMovie->setVisible(false);
        directorEditMovie->setVisible(false);
        formatEditMusic->setVisible(false);
        labelEditMusic->setVisible(false);
        durationEditMusic->setVisible(false);
        platformEditVideogame->setVisible(false);
        developerEditVideogame->setVisible(false);
        publisherEditVideogame->setVisible(false);
        playtimeEditVideogame->setVisible(false);
    } else if (mediaType == "Film") {
        pagesEditBook->setVisible(false);
        isbnEditBook->setVisible(false);
        publisherEditBook->setVisible(false);
        authorEditBook->setVisible(false);
        durationEditMovie->setVisible(true);
        ratingEditMovie->setVisible(true);
        studioEditMovie->setVisible(true);
        directorEditMovie->setVisible(true);
        formatEditMusic->setVisible(false);
        labelEditMusic->setVisible(false);
        durationEditMusic->setVisible(false);
        platformEditVideogame->setVisible(false);
        developerEditVideogame->setVisible(false);
        publisherEditVideogame->setVisible(false);
        playtimeEditVideogame->setVisible(false);
    } else if (mediaType == "Music") {
        pagesEditBook->setVisible(false);
        isbnEditBook->setVisible(false);
        publisherEditBook->setVisible(false);
        authorEditBook->setVisible(false);
        durationEditMovie->setVisible(false);
        ratingEditMovie->setVisible(false);
        studioEditMovie->setVisible(false);
        directorEditMovie->setVisible(false);
        formatEditMusic->setVisible(true);
        labelEditMusic->setVisible(true);
        durationEditMusic->setVisible(true);
        platformEditVideogame->setVisible(false);
        developerEditVideogame->setVisible(false);
        publisherEditVideogame->setVisible(false);
        playtimeEditVideogame->setVisible(false);
    } else if (mediaType == "Video Game") {
        pagesEditBook->setVisible(false);
        isbnEditBook->setVisible(false);
        publisherEditBook->setVisible(false);
        authorEditBook->setVisible(false);
        durationEditMovie->setVisible(false);
        ratingEditMovie->setVisible(false);
        studioEditMovie->setVisible(false);
        directorEditMovie->setVisible(false);
        formatEditMusic->setVisible(false);
        labelEditMusic->setVisible(false);
        durationEditMusic->setVisible(false);
        platformEditVideogame->setVisible(true);
        developerEditVideogame->setVisible(true);
        publisherEditVideogame->setVisible(true);
        playtimeEditVideogame->setVisible(true);
    }
}

void AddItemView::onAddButtonClicked()
{
    QString newTitle = titleEdit->text().trimmed();

    if (newTitle.isEmpty()) {
        return;
    }

    for (const QJsonValue& value : jsonManager->getMedia()) {
        QJsonObject obj = value.toObject();
        if (obj["title"].toString().compare(newTitle, Qt::CaseInsensitive) == 0) {
            QMessageBox::warning(this, "Error", "A media item with this title already exists!");
            return;
        }
    }

    saveMediaToJson();
    
    clearForm();
    emit itemAdded();
    
    QMessageBox::information(this, "Success", "Media added successfully!");
}

void AddItemView::clearForm()
{
    descriptionEdit->clear();
    titleEdit->clear();
    genreEdit->clear();
    
    yearEdit->setValue(0);
    pagesEditBook->setValue(0);
    durationEditMovie->setValue(0);
    ratingEditMovie->setValue(1);
    durationEditMusic->setValue(0);
    playtimeEditVideogame->setValue(0);
    
    isbnEditBook->clear();
    publisherEditBook->clear();
    authorEditBook->clear(); 
    studioEditMovie->clear();
    directorEditMovie->clear();
    formatEditMusic->clear();
    labelEditMusic->clear();
    platformEditVideogame->clear();
    developerEditVideogame->clear();
    publisherEditVideogame->clear();

    yearEdit->setSpecialValueText("Insert Year...");
    pagesEditBook->setSpecialValueText("Pages...");
    durationEditMovie->setSpecialValueText("Duration (minutes)...");
    ratingEditMovie->setSpecialValueText("Rating...");
    durationEditMusic->setSpecialValueText("Duration (minutes)...");
    playtimeEditVideogame->setSpecialValueText("Playtime (hours)...");

    currentImagePath.clear();
    browseImageButton->setText("Select Image...");

    toggleFields();
}

void AddItemView::onBrowseImageClicked() 
{
    QString imagePath = QFileDialog::getOpenFileName(
        this,
        "Select Media Image",
        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
        "Image Files (*.png *.jpg  *.jpeg *.bmp  *.gif);; All Files (*)"
    );

    if(!imagePath.isEmpty())
    {
        currentImagePath = imagePath;
        
        QFileInfo fileInfo(imagePath);
        browseImageButton->setText(fileInfo.fileName());
    } else {
        currentImagePath = "defaultimagepath";
    }
}

void AddItemView::saveMediaToJson()
{
    QString mediaType = mediaTypeCombo->currentText();
    QMap<QString, QVariant> data;
    
    data["title"] = titleEdit->text();
    data["year"] = yearEdit->value();
    data["description"] = descriptionEdit->toPlainText();
    data["genre"] = genreEdit->text();
    data["imagePath"] = currentImagePath;

    if (mediaType == "Book") {
        data["author"] = authorEditBook->text();
        data["pages"] = pagesEditBook->value();
        data["isbn"] = isbnEditBook->text();
        data["publisher"] = publisherEditBook->text();
    }
    else if (mediaType == "Film") {
        data["director"] = directorEditMovie->text();
        data["duration"] = durationEditMovie->value();
        data["rating"] = ratingEditMovie->value();
        data["studio"] = studioEditMovie->text();
    }
    else if (mediaType == "Music") {
        data["artist"] = authorEditBook->text();
        data["duration"] = durationEditMusic->value();
        data["format"] = formatEditMusic->text();
        data["label"] = labelEditMusic->text();
    }
    else if (mediaType == "Video Game") {
        data["developer"] = developerEditVideogame->text();
        data["platform"] = platformEditVideogame->text();
        data["publisher"] = publisherEditVideogame->text();
        data["playtime"] = playtimeEditVideogame->value();
    }
    
    QJsonObject mediaJson = JsonManager::mediaToJson(mediaType, data);
    jsonManager->addMedia(mediaJson);
}