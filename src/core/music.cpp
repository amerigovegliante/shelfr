#include "../../headers/core/music.h"

Music::Music(const QString& title, const QString& description, const QString& genre, const QString& imagepath, int year, const QString& format, const QString& label, int duration):
    Media(title,description,genre,imagepath,year),
    format(!(format.isNull() && format.isEmpty()) ? format : "Default Music Format"),
    label(!(label.isNull() && label.isEmpty()) ? label : "Default Music Label") 
{}

Music::Music(const Music& music):
    Media(music),
    format(music.format),
    label(music.label),
    duration(music.duration)
{}

void Music::accept(MediaVisitorInterface& visitor)
{
    visitor.visit(*this);
}

Music* Music::clone() const { return new Music(*this);}

QString Music::getFormat() const 
{
    return Music::format;
}

QString Music::getLabel() const 
{
    return Music::label;
}

int Music::getDuration() const 
{
    return Music::duration;
}

void Music::setFormat(const QString& new_format)
{
    format = new_format;
}

void Music::setLabel(const QString& new_label)
{
    label = new_label;
}

void Music::setDuration(int new_duration)
{
    duration = new_duration;
}