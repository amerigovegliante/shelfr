#ifndef VIDEOGAME_H 
#define VIDEOGAME_H

#include "media.h"

class Videogame: public Media
{
    private:
        QString platform;
        QString developer;
        QString publisher;
        int playtime;
    public:
        Videogame(const QString&, const QString&, const QString&, const QString&, int, const QString&, const QString&, const QString&, int);

        virtual ~Videogame() override = default;

        QString getPlatform() const;
        QString getDeveloper() const;
        QString getPublisher() const;
        QString getGenre() const;
        int getPlaytime() const;

        void setPlatform(const QString&);
        void setDeveloper(const QString&);
        void setPublisher(const QString&);
        void setGenre(const QString&);
        void setPlaytime(int);
};

#endif