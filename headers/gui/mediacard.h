#ifndef MEDIACARD_H
#define MEDIACARD_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "../../headers/core/media.h"

class MediaCard : public QFrame
{
    Q_OBJECT

public:
    explicit MediaCard(Media *media, QWidget *parent = nullptr);
    ~MediaCard();

    Media* getMedia() const;
    QPushButton* getDeleteButton() const;
    void updateCard();

signals:
    void clicked(Media *media);
    void editRequested(Media *media);
    void viewRequested(Media* media);
    void deleteRequested(Media *media);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void setupUI();
    void setupContextMenu();
    void setupButtons();

    Media* media;
    QLabel* imageLabel;
    QLabel* titleLabel;
    QLabel* descLabel;

    QPushButton* editButton;
    QPushButton* deleteButton;
    QPushButton* viewButton;
    QHBoxLayout* buttonLayout;
};

#endif // MEDIACARD_H