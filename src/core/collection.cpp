#include "../../headers/core/collection.h"

Collection::Collection(const QString& name, const QString& description):
    name(!(name.isNull() && name.isEmpty()) ? name : "Default Collection Name"),
    description(!(description.isNull() && description.isEmpty()) ? description : "Default Collection Description"),
    creationDate(QDate::currentDate())
{}

void Collection::addMedia(Media* media)
{
    if(media && !mediaList.contains(media))
    {
        mediaList.append(media);
        qDebug() << "Added media: " << media->getTitle() << "to collection " << name;
    }
}

bool Collection::removeMedia(Media* media)
{
    int index = mediaList.indexOf(media);
    if(index != -1)
    {
        qDebug() << "Media " << media->getTitle() << " has been removed from Collection " << name;
        mediaList.remove(index);
        return true;
    }
    return false;
}

void Collection::clear() 
{
    mediaList.clear();
}

QString Collection::getName() const { return name; }
QString Collection::getDescription() const { return description; }
QDate Collection::getCreationDate() const { return creationDate; }

QVector<Media*> Collection::getMediaList() const
{
    QVector<Media*> copy;
    copy.reserve(mediaList.size());

    for(Media* media : mediaList)
    {
        
    }
}

