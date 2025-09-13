#include "../../headers/core/videogame.h"

Videogame::Videogame(const QString& title, const QString& description, const QString& genre, const QString& imagepath, int year, const QString& platform, const QString& developer, const QString& publisher, int playTime):
    Media(title,description,genre,imagepath,year),
    platform(!(platform.isNull() && platform.isEmpty()) ? platform : "Default Videogame Platform"),
    developer(!(developer.isNull() && developer.isEmpty()) ? developer : "Default Developer"),
    publisher(!(publisher.isNull() && publisher.isEmpty()) ? publisher : "Default Videogame Publisher"),
    playtime((playtime > 0) ? playtime : 0)
{}

Videogame::Videogame(const Videogame& videogame):
    Media(videogame),
    platform(videogame.platform),
    developer(videogame.developer),
    publisher(videogame.publisher),
    playtime(videogame.playtime)
{}

void Videogame::accept(MediaVisitorInterface& visitor)
{
    visitor.visit(*this);
}

Videogame* Videogame::clone() const { return new Videogame(*this);}

QString Videogame::getPlatform() const
{
    return Videogame::platform;
}

QString Videogame::getDeveloper() const
{
    return Videogame::developer;
}
QString Videogame::getPublisher() const 
{
    return Videogame::publisher;
}

int Videogame::getPlaytime() const
{
    return Videogame::playtime;
}

void Videogame::setPlatform(const QString& new_platform)
{
    platform = new_platform;
}

void Videogame::setDeveloper(const QString& new_developer)
{
    developer = new_developer;
}

void Videogame::setPublisher(const QString& new_publisher)
{
    publisher = new_publisher;
}

void Videogame::setPlaytime(int new_playtime)
{
    playtime = new_playtime;
}