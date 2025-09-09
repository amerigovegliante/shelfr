#include "../../headers/core/film.h"

Film::Film(const QString& t, const QString& d, const QString& g, const QString& ip, int y, int dur, int rat, const QString& stud, const QString& dir):
    Media(t,d,g,ip,y),
    duration((dur != NULL && dur > 0) ? dur : 0),
    rating((rat != NULL && rat >= 1 && rat <= 5) ? rat : 0), // default case managed as "rating not found"
    studio(!(stud.isNull() && stud.isEmpty()) ? stud : "Default Studio"),
    director(!(dir.isNull() && dir.isEmpty()) ? dir : "Default Film Director")
    {}

int Film::getDuration() const {return Film::duration; }

int Film::getRating() const { return Film::rating; }

QString Film::getStudio() const { return Film::studio; }

QString Film::getDirector() const { return Film::director; }

void Film::setDuration(int new_duration) { duration = (new_duration > 0) ? new_duration : 0;}

void Film::setRating(int new_rating) { rating = (new_rating >= 1 && new_rating <= 5) ? new_rating : 0;}

void Film::setStudio(const QString& new_studio) { studio = new_studio; }

void Film::setDirector(const QString& new_director) { director = new_director; }
