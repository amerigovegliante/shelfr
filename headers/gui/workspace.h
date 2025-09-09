#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QFrame>
#include <QStackedWidget>
#include <QVBoxLayout>

class Workspace: public QFrame
{
    Q_OBJECT

    public:
        explicit Workspace(QWidget* parent = nullptr);
        virtual ~Workspace() override = default;

        void showAddItemView();
        void showSearchItemView();
        void showAddCollectionView();
        void showSearchCollectionView();

    private:
        QStackedWidget* stackedWidget;
        QVBoxLayout* layout;

        QWidget* addItemView;
        QWidget* searchItemView;
        QWidget* addCollectionView;
        QWidget* searchCollectionView;
};

#endif