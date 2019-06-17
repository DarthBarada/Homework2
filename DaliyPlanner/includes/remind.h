#ifndef REMIND_H
#define REMIND_H

#include "event.h"
#include <QDateTime>
#include <QString>
/* Класс напоминание, родитель - event */
class remind:public event
{
public:
    remind()
        {}

    remind(QDateTime temp_time,QString temp)
        {
            time=temp_time;
            description=temp;
        }
    virtual ~remind()
        {
        }

    QString print()
        {
            return QString::number(time.date().day())+"."+QString::number(time.date().month())+"."+QString::number(time.date().year())+"|"+time.time().toString()+"|"+description;
        }

};

#endif // REMIND_H
