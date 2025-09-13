#ifndef MUSIC_H 
#define MUSIC_H

#include "media.h"

class Music: public Media
{
    private:
        QString format; // vinyl or cd
        QString label;
        int duration;
    public:
        Music(const QString&, const QString&, const QString&, const QString&, int, const QString&, const QString&, int);
        Music(const Music&);

        virtual void accept(MediaVisitorInterface&) override;
        virtual ~Music() override = default;
        Music* clone() const override;

        QString getFormat() const;
        QString getLabel() const;
        int getDuration() const;

        void setFormat(const QString&);
        void setLabel(const QString&);
        void setDuration(int);
};

#endif