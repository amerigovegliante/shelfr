#ifndef MEDIA_H
#define MEDIA_H

#include <QString>

class Media 
{       
    private:
        QString title;
        QString description;
        QString genre;
        QString imagepath;

        int year;
    public:
        Media(const QString&, const QString&, const QString&, const QString&, int);
        virtual ~Media();

        Media(const Media&);
        virtual Media* clone() = 0;

        QString getTitle() const;
        QString getDescription() const;
        QString getGenre() const;
        QString getImagePath() const;
        int getYear() const;

        void setTitle(const QString&);
        void setDescription(const QString&);
        void setGenre(const QString&);
        void setImagePath(const QString&);
        void setYear(int);
};

#endif