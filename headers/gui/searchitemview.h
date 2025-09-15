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
#include "baseview.h"
#include "viewitemview.h"

#include "../core/media.h"
#include "mediacard.h"
#include "mediacardvisitor.h"
#include "mediafiltervisitor.h"

class SearchItemView : public BaseView
{
    Q_OBJECT

public:
    explicit SearchItemView(JsonManager* jsonManager, QWidget* parent = nullptr);
    ~SearchItemView();
    
    void refresh();

signals:
    void mediaDeleted();
    void viewMediaRequested(Media* media);
    void editMediaRequested(Media* media);

private slots:
    void onSearchTextChanged(const QString& text);
    void onClearSearchClicked();
    void onDeleteMediaRequested(Media* mediaToDelete);
    void onViewMediaRequested(Media* media);
    void onCardEditRequested(Media* media);

private:
    
    void setupUI() override;
    void loadMediaItems();
    void filterMediaByTitle(const QString& searchText);
    void clearLayout();
    void clearMediaList();
    Media* createMediaFromJson(const QJsonObject& mediaObj);
    void rebuildGridLayout();
    void removeMediaFromLayout(Media* media);

    JsonManager* jsonManager;
    QScrollArea* scrollArea;
    QWidget* scrollWidget;
    QGridLayout* gridLayout;
    
    QList<Media*> mediaList;
    QList<Media*> allMediaList;
    QList<Media*> visibleMediaList;

    QHash<Media*, MediaCard*> mediaCardMap;

    QLineEdit* searchLineEdit;
    QPushButton* clearSearchButton;
};

#endif // SEARCHITEMVIEW_H