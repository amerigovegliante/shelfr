#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QMap>
#include <QVariant>
#include <QDateTime>
#include <QObject>

#include "media.h"

class JsonManager : public QObject
{
    Q_OBJECT

public:
        JsonManager(QObject* parent = nullptr);

        bool loadFromFile();
        bool saveToFile() const;
        void replaceMediaArray(const QJsonArray& newArray);

        QJsonObject convertMediaToJson(Media* media);
        Media* createMediaFromJson(const QJsonObject& mediaObj);

        void addMedia(const QJsonObject&);
        QJsonArray getMedia() const;
        bool removeMedia(int);

        void updateMedia(Media* media);

        static QJsonObject mediaToJson(const QString&, const QMap<QString, QVariant>&);
        
        void setFileName(const QString &newFileName);
        QString getFileName() const;

signals: 
    void mediaDataChanged();

private:
        QString fileName;
        QJsonArray mediaArray;
};

#endif