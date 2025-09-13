#include "../../headers/gui/mediacardvisitor.h"
#include "../../headers/gui/mediacard.h"
#include "../../headers/core/book.h"
#include "../../headers/core/film.h"
#include "../../headers/core/music.h"
#include "../../headers/core/videogame.h"

MediaCardVisitor::MediaCardVisitor(QWidget* parent) 
    : parentWidget(parent), currentCard(nullptr) 
{
}

MediaCard* MediaCardVisitor::getCard() const {
    return currentCard;
}

void MediaCardVisitor::visit(Book& book) {
    currentCard = new MediaCard(&book, parentWidget);
    // Puoi customizzare la card per i libri se necessario
}

void MediaCardVisitor::visit(Film& film) {
    currentCard = new MediaCard(&film, parentWidget);
}

void MediaCardVisitor::visit(Music& music) {
    currentCard = new MediaCard(&music, parentWidget);
}

void MediaCardVisitor::visit(Videogame& videogame) {
    currentCard = new MediaCard(&videogame, parentWidget);
}