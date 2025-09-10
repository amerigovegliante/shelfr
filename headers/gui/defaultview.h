#ifndef DEFAULTVIEW_H
#define DEFAULTVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class DefaultView : public QWidget
{
    Q_OBJECT

public:
    explicit DefaultView(QWidget *parent = nullptr);

private:
    void setupUI();

    QVBoxLayout* layout;

    QLabel* title;
    QLabel* subtitle;
    QLabel* features;
};

#endif