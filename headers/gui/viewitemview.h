#ifndef VIEWITEMVIEW_H
#define VIEWITEMVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QScrollArea>
#include "../../headers/core/media.h"

class ViewItemView : public QWidget
{
    Q_OBJECT

public:
    explicit ViewItemView(QWidget* parent = nullptr);
    void setMedia(Media* media);
    void clear();

signals:
    void backRequested();

private:
    void setupUI();
    void updateView();
    QString formatMediaDetails(Media* media);

    Media* currentMedia;
    
    // Widgets
    QLabel* titleLabel;
    QLabel* typeLabel;
    QLabel* yearLabel;
    QLabel* genreLabel;
    QTextEdit* descriptionEdit;
    QLabel* imageLabel;
    QTextEdit* detailsEdit;
    QPushButton* backButton;
    
    // Layouts
    QVBoxLayout* mainLayout;
    QHBoxLayout* headerLayout;
    QHBoxLayout* contentLayout;
};

#endif // VIEWITEMVIEW_H