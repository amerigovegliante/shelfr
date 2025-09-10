#include "../../headers/gui/additemview.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDebug>
#include <QStandardPaths>
#include <QFileDialog>

AddItemView::AddItemView(QWidget *parent) : QWidget(parent)
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

    yearLabel = new QLabel("Year: ", this);
    yearEdit = new QSpinBox(this);
    yearEdit->setRange(0, QDate::currentDate().year());

    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setMaximumHeight(100);
    descriptionEdit->setPlaceholderText("Insert Description...");

    browseImageButton = new QPushButton("Select Image...", this);

    addButton = new QPushButton("Add Item", this);

    browseImageButton->setObjectName("imagebrowser");

    QFormLayout *formLayout = new QFormLayout();    

    formLayout->addRow("Select Media Type: ", mediaTypeCombo);
    formLayout->addRow(browseImageButton);
    formLayout->addRow(titleEdit);
    formLayout->addRow(descriptionEdit);
    formLayout->addRow(yearLabel, yearEdit);
    
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
    
    // Mostra solo i campi rilevanti in base al media type
    if (mediaType == "Book") {
        //
    } else if (mediaType == "Film") {
        //
    } else if (mediaType == "Music") {
        //
    } else if (mediaType == "Video Game") {
        //
    }
}

void AddItemView::onAddButtonClicked()
{
    // Basic validation
    if (titleEdit->text().isEmpty()) {
        qDebug() << "Title is required!";
        return;
    }
    
    QString mediaType = mediaTypeCombo->currentText();
    qDebug() << "Adding" << mediaType << ":" << titleEdit->text();
    
    // Qui aggiungerai la logica per creare l'oggetto Media appropriato
    // e aggiungerlo alla collection
    
    clearForm();
    emit itemAdded();
}

void AddItemView::clearForm()
{
    //
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
        currentImagePath = imagePath;  // Salva il percorso assoluto
        qDebug() << "Selected image:" << currentImagePath;
        
        // Opzionale: cambia il testo del bottone per mostrare il filename
        QFileInfo fileInfo(imagePath);
        browseImageButton->setText(fileInfo.fileName());
    }
}