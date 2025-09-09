#include "../../headers/core/media.h"

Media::Media(const QString& t, const QString& d, const QString& g, const QString& ip, int y): 
    title(!(t.isNull() && t.isEmpty()) ? t : "Default Title"),  
    description(!(d.isNull() && d.isEmpty()) ? d : "Default Description"),
    genre(!(g.isNull() && g.isEmpty()) ? g : "Default Genre"),
    imagepath(!(ip.isNull() && ip.isEmpty()) ? ip : ":/images/default.jpg"),
    year((y != NULL) ? y : 0) {}

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