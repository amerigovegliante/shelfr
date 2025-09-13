#ifndef MEDIACARDVISITOR_H
#define MEDIACARDVISITOR_H

#include "../core/mediavisitorinterface.h"
#include <QWidget>

class MediaCard;

class MediaCardVisitor : public MediaVisitorInterface
{
public:
    MediaCardVisitor(QWidget* parent = nullptr);
    MediaCard* getCard() const;

    void visit(Book& book) override;
    void visit(Film& film) override;
    void visit(Music& music) override;
    void visit(Videogame& videogame) override;

private:
    MediaCard* currentCard;
    QWidget* parentWidget;
};

#endif // MEDIACARDVISITOR_H