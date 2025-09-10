#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QFrame>

class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QCheckBox;
class QLabel;

class Sidebar : public QFrame
{
    Q_OBJECT

public:
    explicit Sidebar(QWidget *parent = nullptr);

signals:
    void addItemClicked();
    void searchItemClicked();
    void addCollectionClicked();
    void searchCollectionClicked();

private slots:
    void onThemeToggled(bool checked);
    void onThemeChanged();

private:
    QVBoxLayout *layout;
    QHBoxLayout *themeLayout;
    QPushButton *addItemButton;
    QPushButton *searchItemButton;
    QPushButton *addCollectionButton;
    QPushButton *searchCollectionButton;
    QCheckBox *themeSwitch;
    QLabel *themeLabel;
    QLabel *title;
};

#endif // SIDEBAR_H