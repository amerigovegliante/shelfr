#ifndef BASEVIEW_H
#define BASEVIEW_H

#include <QWidget>

class BaseView : public QWidget
{
    public:
        explicit BaseView(QWidget* parent = nullptr);
        virtual ~BaseView() = default;
    private:
        virtual void setupUI() = 0;
};

#endif