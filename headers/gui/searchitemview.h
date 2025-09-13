#ifndef SEARCHITEMVIEW_H
#define SEARCHITEMVIEW_H

#include <QWidget>
#include <QScrollArea>
#include <QLineEdit>
#include <QPushButton>
#include <QList>
#include <QHash>
#include <QGridLayout>

#include "../core/jsonmanager.h"

// Forward declarations
class Media;
class MediaCard;
class MediaCardVisitor;
class MediaFilterVisitor;

class SearchItemView : public QWidget
{
    Q_OBJECT

public:
    explicit SearchItemView(JsonManager* jsonManager, QWidget* parent = nullptr);
    ~SearchItemView();
    
    void refresh();

signals:
    void mediaDeleted(); // Segnale per notificare la delete

private slots:
    void onSearchTextChanged(const QString& text);
    void onClearSearchClicked();
    void onDeleteMediaRequested(Media* mediaToDelete); // Slot per la delete

private:
    
    void setupUI();
    void loadMediaItems();
    void filterMediaByTitle(const QString& searchText);
    void clearLayout();
    void clearMediaList();
    Media* createMediaFromJson(const QJsonObject& mediaObj);
    void rebuildGridLayout();
    void removeMediaFromLayout(Media* media); // Rimuove un media specifico

    JsonManager* jsonManager;
    QScrollArea* scrollArea;
    QWidget* scrollWidget;
    QGridLayout* gridLayout;
    
    QList<Media*> mediaList;
    QList<Media*> allMediaList;
    QList<Media*> visibleMediaList;

    // Mappa per accesso rapido alle card
    QHash<Media*, MediaCard*> mediaCardMap;

    // Widgets per la ricerca
    QLineEdit* searchLineEdit;
    QPushButton* clearSearchButton;
};

#endif // SEARCHITEMVIEW_H