#ifndef EVENT_H
#define EVENT_H

#pragma once
#include <QDateTime>
#include <QString>
/* Класс event (событие)*/
class event
{
protected:
    QDateTime time;          // Когда произойдет событие
    QString description;    // Описание события
public:
    virtual QString print()=0;

    event()
        {
            time=QDateTime::currentDateTime();
            description = "";
        }

    virtual ~event()
        {
            time.~QDateTime();
            description.~QString();
        }

    QDateTime& get_time()
        {
            return time;
        }
    QString& get_description()
        {
            return description;
        }
};

#endif // EVENT_H
