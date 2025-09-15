#ifndef DEFAULTVIEW_H
#define DEFAULTVIEW_H

#include "baseview.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class DefaultView : public BaseView
{
    Q_OBJECT

public:
    explicit DefaultView(QWidget *parent = nullptr);

private:
    void setupUI() override;

    QVBoxLayout* layout;

    QLabel* title;
    QLabel* subtitle;
    QLabel* features;
};

#endif