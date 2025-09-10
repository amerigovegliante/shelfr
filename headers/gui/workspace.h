#ifndef WORKSPACE_H
#define WORKSPACE_H

#include "defaultview.h"
#include "additemview.h"
#include <QFrame>
#include <QStackedWidget>
#include <QVBoxLayout>

class Workspace: public QFrame
{
    Q_OBJECT

    public:
        explicit Workspace(QWidget* parent = nullptr);
        virtual ~Workspace() override = default;

        void showDefaultView();
        void showAddItemView();
        void showSearchItemView();
        void showAddCollectionView();
        void showSearchCollectionView();

    private:
        QStackedWidget* stackedWidget;
        QVBoxLayout* layout;

        DefaultView* defaultView;
        AddItemView* addItemView;
        QWidget* searchItemView;
        QWidget* addCollectionView;
        QWidget* searchCollectionView;
};

#endif