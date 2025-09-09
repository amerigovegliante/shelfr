#ifndef SIDEBAR_H
#define SIDEBAR_H

#include "thememanager.h"
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

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

    private slots:
        void onThemeToggled(bool checked);
        void onThemeChanged(ThemeManager::Theme theme);

    private:
        QVBoxLayout* layout;

        QLabel* title;

        QCheckBox* themeSwitch;
        QLabel* themeLabel;
        QHBoxLayout* themeLayout;
        
        QPushButton* addItemButton;
        QPushButton* searchItemButton;
        QPushButton* addCollectionButton;
        QPushButton* searchCollectionButton;
};

#endif