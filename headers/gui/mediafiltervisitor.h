#ifndef MEDIAFILTERVISITOR_H
#define MEDIAFILTERVISITOR_H

#include "../core/mediavisitorinterface.h"
#include <QString>

class MediaFilterVisitor : public MediaVisitorInterface
{
public:
    MediaFilterVisitor(const QString& searchText);
    bool matches() const;

    void visit(Book& book) override;
    void visit(Film& film) override;
    void visit(Music& music) override;
    void visit(Videogame& videogame) override;

private:
    QString searchText;
    bool matchFound;
};

#endif // MEDIAFILTERVISITOR_H