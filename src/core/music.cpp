#include "../../headers/core/music.h"

Music::Music(const QString& t, const QString& d, const QString& g, const QString& ip, int y, const QString& frm, const QString& lbl, int dur):
    Media(t,d,g,ip,y),
    format(!(frm.isNull() && frm.isEmpty()) ? frm : "Default Music Format"),
    label(!(lbl.isNull() && lbl.isEmpty()) ? lbl : "Default Music Label") 
{}

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