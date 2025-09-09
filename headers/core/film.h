#ifndef FILM_H
#define FILM_H

#include "media.h"
#include <vector>

class Film : public Media
{
    private:
        int duration; // in minutes
        int rating; // from 1 to 5
        QString studio;
        QString director;
    public:    
        Film(const QString&, const QString&, const QString&, const QString&, int, int, int, const QString&, const QString&);

        virtual ~Film() override = default;

        int getDuration() const;
        int getRating() const;
        QString getStudio() const;
        QString getDirector() const;

        void setDuration(int);
        void setRating(int);
        void setStudio(const QString&);
        void setDirector(const QString&);
};

#endif