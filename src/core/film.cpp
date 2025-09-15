#include "../../headers/core/film.h"

Film::Film(const QString& title, const QString& description, const QString& genre, const QString& imagepath, int year, int duration, int rating, const QString& studio, const QString& director):
    Media(title,description,genre,imagepath,year),
    duration((duration >= 0) ? duration : 0),
    rating((rating >= 1 && rating <= 5) ? rating : 0), // default case managed as "rating not found"
    studio(!(studio.isNull() && studio.isEmpty()) ? studio : "Default Studio"),
    director(!(director.isNull() && director.isEmpty()) ? director : "Default Film Director")
{}

Film::Film(const Film& film):
    Media(film),
    duration(film.duration),
    rating(film.rating),
    studio(film.studio),
    director(film.director)
{}

void Film::accept(MediaVisitorInterface& visitor)
{
    visitor.visit(*this);
}

QString Film::getType() const { return "Film";}

Film* Film::clone() const { return new Film(*this); }

int Film::getDuration() const {return Film::duration; }

int Film::getRating() const { return Film::rating; }

QString Film::getStudio() const { return Film::studio; }

QString Film::getDirector() const { return Film::director; }

void Film::setDuration(int new_duration) { duration = (new_duration > 0) ? new_duration : 0;}

void Film::setRating(int new_rating) { rating = (new_rating >= 1 && new_rating <= 5) ? new_rating : 0;}

void Film::setStudio(const QString& new_studio) { studio = new_studio; }

void Film::setDirector(const QString& new_director) { director = new_director; }
