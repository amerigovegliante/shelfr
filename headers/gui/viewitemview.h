#ifndef VIEWITEMVIEW_H
#define VIEWITEMVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QScrollArea>
#include "../../headers/core/media.h"
#include "baseview.h"

class ViewItemView : public BaseView
{
    Q_OBJECT

public:
    explicit ViewItemView(QWidget* parent = nullptr);
    void setMedia(Media* media);
    void clear();

signals:
    void backRequested();

private:
    void setupUI() override;
    void updateView();
    QString formatMediaDetails(Media* media);

    Media* currentMedia;
    
    QLabel* titleLabel;
    QLabel* typeLabel;
    QLabel* yearLabel;
    QLabel* genreLabel;
    QTextEdit* descriptionEdit;
    QLabel* imageLabel;
    QTextEdit* detailsEdit;
    QPushButton* backButton;
    
    QVBoxLayout* mainLayout;
    QHBoxLayout* headerLayout;
    QHBoxLayout* contentLayout;
};

#endif // VIEWITEMVIEW_H