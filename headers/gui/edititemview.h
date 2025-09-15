#ifndef EDITITEMVIEW_H
#define EDITITEMVIEW_H

#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>

#include "baseview.h"
#include "../core/jsonmanager.h"

class EditItemView : public BaseView
{
    Q_OBJECT

public:
    explicit EditItemView(JsonManager* jsonManager,QWidget *parent = nullptr);

    void setMedia(Media*);

signals:
    void mediaUpdated(Media* media);
    
private slots:
    void onSaveChanges();
    void onBrowseImageClicked();

private:
    void setupUI() override;

    Media* media;

    QFormLayout* formLayout;

    QLabel* title;
    QLabel* subtitle;
    QLabel* features;

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

    JsonManager* jsonManager;
};

#endif