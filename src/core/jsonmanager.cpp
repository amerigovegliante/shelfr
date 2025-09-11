#include "../../headers/core/jsonmanager.h"

#include <QFile>
#include <QJsonDocument>
#include <QDebug>

JsonManager::JsonManager() : fileName("media.json")
{
    loadFromFile();
}

bool JsonManager::loadFromFile()
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open file for reading:" << fileName;
        mediaArray = QJsonArray(); // Array vuoto
        return false;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isArray()) {
        mediaArray = doc.array();
    } else {
        mediaArray = QJsonArray();
    }
    
    return true;
}

bool JsonManager::saveToFile() const
{
    QFile file(fileName);
    
    qDebug() << "Attempting to save to:" << fileName;
    qDebug() << "File exists:" << file.exists();
    qDebug() << "Is writable:" << file.isWritable();
    
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open file for writing:" << fileName;
        qWarning() << "Error:" << file.errorString();
        return false;
    }
    
    QJsonDocument doc(mediaArray);
    QByteArray jsonData = doc.toJson(QJsonDocument::Indented);
    
    qDebug() << "JSON data size:" << jsonData.size();
    qDebug() << "JSON content:" << jsonData;
    
    file.write(jsonData);
    file.close();
    
    qDebug() << "File written successfully!";
    return true;
}

void JsonManager::addMedia(const QJsonObject &mediaObject)
{
    mediaArray.append(mediaObject);
    bool success = saveToFile();

    qDebug() << "Add media - Success:" << success;
    qDebug() << "Current array size:" << mediaArray.size();
}

QJsonArray JsonManager::getMedia() const
{
    return mediaArray;
}

bool JsonManager::removeMedia(int index)
{
    if (index >= 0 && index < mediaArray.size()) {
        mediaArray.removeAt(index);
        return saveToFile();
    }
    return false;
}

QJsonObject JsonManager::mediaToJson(const QString &type, const QMap<QString, QVariant> &data)
{
    QJsonObject json;
    json["type"] = type;
    json["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        json[it.key()] = QJsonValue::fromVariant(it.value());
    }
    
    return json;
}