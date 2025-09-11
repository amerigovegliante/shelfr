#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QString>
#include <QJsonArray>
#include <QJsonObject>

class JsonManager 
{
    public:
        JsonManager();

        bool loadFromFile();
        bool saveToFile() const;

        void addMedia(const QJsonObject&);
        QJsonArray getMedia() const;
        bool removeMedia(int);

        static QJsonObject mediaToJson(const QString&, const QMap<QString, QVariant>&);
    
    private:
        QString fileName;
        QJsonArray mediaArray;
};

#endif