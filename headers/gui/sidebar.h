#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>

class Sidebar : public QFrame
{
    Q_OBJECT

public:
    explicit Sidebar(QWidget *parent = nullptr);

signals:
    void addItemClicked();
    void searchItemClicked();

private slots:
    void onThemeToggled(bool checked);
    void onThemeChanged();

private:
    QVBoxLayout *layout;
    QHBoxLayout *themeLayout;
    QPushButton *addItemButton;
    QPushButton *searchItemButton;
    QCheckBox *themeSwitch;
    QLabel *themeLabel;
    QLabel *title;
};

#endif // SIDEBAR_H