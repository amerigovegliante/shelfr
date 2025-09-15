#include "../../headers/core/media.h"

Media::Media(const QString& title, const QString& description, const QString& genre, const QString& imagepath, int year): 
    title(!(title.isNull() && title.isEmpty()) ? title : "Default Title"),  
    description(!(description.isNull() && description.isEmpty()) ? description : "Default Description"),
    genre(!(genre.isNull() && genre.isEmpty()) ? genre : "Default Genre"),
    imagepath(!(imagepath.isNull() && imagepath.isEmpty()) ? imagepath : ":/images/default.jpg"),
    year(year) {}

Media::Media(const Media& media):
    title(media.title),
    description(media.description),
    genre(media.genre),
    imagepath(media.imagepath)
{}

Media::~Media(){}

QString Media::getTitle() const { return Media::title; }

QString Media::getDescription() const { return Media::description; }

QString Media::getGenre() const { return Media::genre; }

QString Media::getImagePath() const { return Media::imagepath; }

int Media::getYear() const { return Media::year; }

void Media::setTitle(const QString& new_title) { title = new_title; }

void Media::setDescription(const QString& new_description) { description = new_description; }

void Media::setGenre(const QString& new_author) { genre = new_author; }

void Media::setImagePath(const QString& new_imagepath) { imagepath = new_imagepath; }

void Media::setYear(int new_year) { year = new_year; }