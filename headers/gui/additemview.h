#ifndef ADDITEMVIEW_H
#define ADDITEMVIEW_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QString>
#include <QSpinBox>

#include "../core/jsonmanager.h"

class AddItemView : public QWidget
{
    Q_OBJECT

public:
    explicit AddItemView(QWidget *parent = nullptr);
    void clearForm();

signals:
    void itemAdded();

private slots:
    void onMediaTypeChanged(int index);
    void onAddButtonClicked();
    void onBrowseImageClicked();

private:
    void setupUI();
    void setupConnections();
    void toggleFields();
    void saveMediaToJson();

    // Form fields
    QComboBox* mediaTypeCombo;
    QTextEdit* descriptionEdit;
    QLineEdit* titleEdit;
    QLineEdit* genreEdit;
    QSpinBox* yearEdit;


    QPushButton* addButton;
    QPushButton* browseImageButton;
    QString currentImagePath;
    
    QSpinBox* pagesEditBook;
    QLineEdit* isbnEditBook;
    QLineEdit* publisherEditBook;
    QLineEdit* authorEditBook; 

    QSpinBox* durationEditMovie;
    QSpinBox* ratingEditMovie;
    QLineEdit* studioEditMovie;
    QLineEdit* directorEditMovie;

    QLineEdit* formatEditMusic;
    QLineEdit* labelEditMusic;
    QSpinBox* durationEditMusic;
    
    QLineEdit* platformEditVideogame;
    QLineEdit* developerEditVideogame;
    QLineEdit* publisherEditVideogame;
    QSpinBox* playtimeEditVideogame;

    JsonManager jsonManager;
};

#endif // ADDITEMVIEW_H