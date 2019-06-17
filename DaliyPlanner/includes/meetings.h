#ifndef MEETINGS_H
#define MEETINGS_H

#include "event.h"
#include <QDateTime>
#include <QString>
/* Класс встреча, родитель - event*/
class meeting:public event
{
public:
    meeting()
        {}

    meeting(QDateTime temp_time,QString temp)
        {
            time=temp_time;
            description=temp;
        }

    virtual ~meeting()
        {

        }

    QString print()
        {
            return QString::number(time.date().day())+"."+QString::number(time.date().month())+"."+QString::number(time.date().year())+"|"+time.time().toString()+"|"+description;
        }
};

#endif // MEETINGS_H
