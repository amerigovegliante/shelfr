#ifndef MEDIAVISITORINTERFACE_H
#define MEDIAVISITORINTERFACE_H

class Book;
class Film;
class Music;
class Videogame;

class MediaVisitorInterface 
{
    public:
        virtual ~MediaVisitorInterface() = default;

        virtual void visit(Book&) = 0;
        virtual void visit(Film&) = 0;
        virtual void visit(Music&) = 0;
        virtual void visit(Videogame&) = 0;
};

#endif