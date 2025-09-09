#ifndef COLLECTION_H
#define COLLECTION_H

#include "media.h"
#include <QString>
#include <QVector>
#include <QDate>

class Collection
{
    private:
        QString name;
        QString description;
        QDate creationDate;
        QVector<Media*> mediaList;
    public:
        Collection(const QString&, const QString&);

        void addMedia(Media* media);
        bool removeMedia(Media* media);
        void clear();

        QString getName() const;
        QString getDescription() const;
        QDate getCreationDate() const;
        QVector<Media*> getMediaList() const;

        void setName(const QString&);
        void setDescription(const QString&);

        int size() const;
        bool contains(Media* media) const;

        template<typename T>
        QVector<T*> filterByType() const;

        QVector<Media*> sortByYear() const;
        QVector<Media*> sortByTitle() const;


};

#endif // COLLECTION_H