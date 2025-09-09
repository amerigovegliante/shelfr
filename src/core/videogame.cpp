#include "../../headers/core/videogame.h"

Videogame::Videogame(const QString& t, const QString& d, const QString& g, const QString& ip, int y, const QString& pf, const QString& dev, const QString& publ, int pt):
    Media(t,d,g,ip,y),
    platform(!(pf.isNull() && pf.isEmpty()) ? pf : "Default Videogame Platform"),
    developer(!(dev.isNull() && dev.isEmpty()) ? dev : "Default Developer"),
    publisher(!(publ.isNull() && publ.isEmpty()) ? publ : "Default Videogame Publisher"),
    playtime((pt > 0) ? pt : 0)
{}

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