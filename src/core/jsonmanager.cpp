#include "../../headers/core/jsonmanager.h"

#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>

#include "../../headers/core/media.h"
#include "../../headers/core/book.h"
#include "../../headers/core/film.h"
#include "../../headers/core/music.h"
#include "../../headers/core/videogame.h"

JsonManager::JsonManager(QObject* parent) : QObject(parent), fileName("media.json")
{
    // Usa la directory dell'eseguibile (cartella di build)
    QString appDir = QCoreApplication::applicationDirPath();
    fileName = QDir(appDir).filePath("media.json");
    
    qDebug() << "JSON file location:" << fileName;
    loadFromFile();
}

bool JsonManager::loadFromFile()
{
    QFile file(fileName);
    
    // Se il file non esiste, crea un array vuoto
    if (!file.exists()) {
        qDebug() << "File doesn't exist, creating new array";
        mediaArray = QJsonArray();
        
        // Salva array vuoto per creare il file
        return saveToFile();
    }
    
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open file for reading:" << fileName;
        qWarning() << "Error:" << file.errorString();
        mediaArray = QJsonArray();
        return false;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    
    if (error.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << error.errorString();
        mediaArray = QJsonArray();
        return false;
    }
    
    if (doc.isArray()) {
        mediaArray = doc.array();
        qDebug() << "Loaded" << mediaArray.size() << "media items from" << fileName;
    } else {
        qWarning() << "JSON document is not an array, creating empty array";
        mediaArray = QJsonArray();
    }
    
    return true;
}

bool JsonManager::saveToFile() const
{
    // Assicurati che la directory esista
    QFileInfo fileInfo(fileName);
    QDir dir = fileInfo.dir();
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qWarning() << "Failed to create directory:" << dir.path();
            return false;
        }
    }
    
    QFile file(fileName);
    
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open file for writing:" << fileName;
        qWarning() << "Error:" << file.errorString();
        return false;
    }
    
    QJsonDocument doc(mediaArray);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    
    return true;
}

void JsonManager::addMedia(const QJsonObject &mediaObject)
{
    mediaArray.append(mediaObject);
    bool success = saveToFile();

    if (success) {
        emit mediaDataChanged();  // EMETTI IL SEGNALE QUI
    }

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
        bool success = saveToFile();
        if (success) {
            emit mediaDataChanged();  // Emetti il segnale anche per la rimozione
        }
        return success;
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

void JsonManager::setFileName(const QString &newFileName)
{
    fileName = newFileName;
    loadFromFile();
}

QString JsonManager::getFileName() const
{
    return fileName;
}

void JsonManager::replaceMediaArray(const QJsonArray& newArray)
{
    mediaArray = newArray;
    saveToFile();
}

QJsonObject JsonManager::convertMediaToJson(Media* media)
{
    if (!media) return QJsonObject();
    
    QMap<QString, QVariant> data;
    
    // Campi comuni a tutti i media
    data["title"] = media->getTitle();
    data["year"] = media->getYear();
    data["description"] = media->getDescription();
    data["genre"] = media->getGenre();
    data["imagePath"] = media->getImagePath();
    
    // Campi specifici per tipo
    if (Book* book = dynamic_cast<Book*>(media)) {
        data["author"] = book->getAuthor();
        data["pages"] = book->getPages();
        data["isbn"] = book->getISBN();
        data["publisher"] = book->getPublisher();
        return JsonManager::mediaToJson("Book", data);
    }
    else if (Film* film = dynamic_cast<Film*>(media)) {
        data["director"] = film->getDirector();
        data["duration"] = film->getDuration();
        data["rating"] = film->getRating();
        data["studio"] = film->getStudio();
        return JsonManager::mediaToJson("Film", data);
    }
    else if (Music* music = dynamic_cast<Music*>(media)) {
        data["duration"] = music->getDuration();
        data["format"] = music->getFormat();
        data["label"] = music->getLabel();
        return JsonManager::mediaToJson("Music", data);
    }
    else if (Videogame* game = dynamic_cast<Videogame*>(media)) {
        data["developer"] = game->getDeveloper();
        data["platform"] = game->getPlatform();
        data["publisher"] = game->getPublisher();
        data["playtime"] = game->getPlaytime();
        return JsonManager::mediaToJson("Video Game", data);
    }
    
    return QJsonObject();
}

Media* JsonManager::createMediaFromJson(const QJsonObject& mediaObj)
{
    QString type = mediaObj["type"].toString();
    Media* media = nullptr;
    
    if (type == "Book") {
        media = new Book(
            mediaObj["title"].toString(),
            mediaObj["description"].toString(),
            mediaObj["genre"].toString(),
            mediaObj["imagePath"].toString(),
            mediaObj["year"].toInt(),
            mediaObj["pages"].toInt(), // Assicurati che il campo sia "pages" non "pageCount"
            mediaObj["isbn"].toString(),
            mediaObj["publisher"].toString(),
            mediaObj["author"].toString()
        );
    }
    else if (type == "Film") {
        media = new Film(
            mediaObj["title"].toString(),
            mediaObj["description"].toString(),
            mediaObj["genre"].toString(),
            mediaObj["imagePath"].toString(),
            mediaObj["year"].toInt(),
            mediaObj["duration"].toInt(),
            mediaObj["rating"].toInt(),
            mediaObj["studio"].toString(),
            mediaObj["director"].toString()
        );
    }
    else if (type == "Music") {
        media = new Music(
            mediaObj["title"].toString(),
            mediaObj["description"].toString(),
            mediaObj["genre"].toString(),
            mediaObj["imagePath"].toString(),
            mediaObj["year"].toInt(),
            mediaObj["format"].toString(),
            mediaObj["label"].toString(),
            mediaObj["duration"].toInt()
        );
    }
    else if (type == "Video Game") {
        media = new Videogame(
            mediaObj["title"].toString(),
            mediaObj["description"].toString(),
            mediaObj["genre"].toString(),
            mediaObj["imagePath"].toString(),
            mediaObj["year"].toInt(),
            mediaObj["platform"].toString(),
            mediaObj["developer"].toString(),
            mediaObj["publisher"].toString(),
            mediaObj["playtime"].toInt()
        );
    }
    
    if (!media) {
        qWarning() << "Unknown media type:" << type;
    }
    
    return media;
}