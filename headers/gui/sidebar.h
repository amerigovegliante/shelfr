#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>

class Sidebar : public QFrame
{
    Q_OBJECT

    public:
        explicit Sidebar(QWidget* parent = nullptr);
        virtual ~Sidebar() override = default;

    signals:
        void addItemClicked();
        void searchItemClicked();
        void addCollectionClicked();
        void searchCollectionClicked();

    private:
        QVBoxLayout *layout;
        QPushButton* addItemButton;
        QPushButton* searchItemButton;
        QPushButton* addCollectionButton;
        QPushButton* searchCollectionButton;
};

#endif