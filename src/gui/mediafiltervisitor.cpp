#include "../../headers/gui/mediafiltervisitor.h"
#include "../../headers/core/book.h"
#include "../../headers/core/film.h"
#include "../../headers/core/music.h"
#include "../../headers/core/videogame.h"

MediaFilterVisitor::MediaFilterVisitor(const QString& searchText) 
    : searchText(searchText.toLower()), matchFound(false) 
{
}

bool MediaFilterVisitor::matches() const {
    return matchFound;
}

void MediaFilterVisitor::visit(Book& book) {
    matchFound = book.getTitle().toLower().contains(searchText) ||
                 book.getAuthor().toLower().contains(searchText) ||
                 book.getGenre().toLower().contains(searchText);
}

void MediaFilterVisitor::visit(Film& film) {
    matchFound = film.getTitle().toLower().contains(searchText) ||
                 film.getDirector().toLower().contains(searchText) ||
                 film.getGenre().toLower().contains(searchText);
}

void MediaFilterVisitor::visit(Music& music) {
    matchFound = music.getTitle().toLower().contains(searchText) ||
                 music.getLabel().toLower().contains(searchText) ||
                 music.getGenre().toLower().contains(searchText);
}

void MediaFilterVisitor::visit(Videogame& videogame) {
    matchFound = videogame.getTitle().toLower().contains(searchText) ||
                 videogame.getDeveloper().toLower().contains(searchText) ||
                 videogame.getPublisher().toLower().contains(searchText);
}