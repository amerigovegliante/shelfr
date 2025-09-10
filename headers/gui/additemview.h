#ifndef ADDITEMVIEW_H
#define ADDITEMVIEW_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QString>
#include <QSpinBox>

class AddItemView : public QWidget
{
    Q_OBJECT

public:
    explicit AddItemView(QWidget *parent = nullptr);
    void clearForm();

signals:
    void itemAdded();

private slots:
    void onMediaTypeChanged(int index);
    void onAddButtonClicked();
    void onBrowseImageClicked();

private:
    void setupUI();
    void setupConnections();
    void toggleFields();

    // Form fields
    QComboBox* mediaTypeCombo;
    QTextEdit* descriptionEdit;
    QLineEdit* titleEdit;

    QLabel* yearLabel;
    QSpinBox* yearEdit;

    QPushButton* addButton;
    QPushButton* browseImageButton;
    QString currentImagePath;
    
};

#endif // ADDITEMVIEW_H