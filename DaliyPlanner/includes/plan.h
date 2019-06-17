#ifndef PLAN_H
#define PLAN_H
#include "event.h"

/* Класс план, родитель - event */
class plan:public event
{
protected:
    int prior;  // Значимость плана
public:

    plan()
        {
            prior=0;
        }
    plan(QDateTime tim,QString temp,int temp_int)
        {
            prior=temp_int;
            time = tim;
            description = temp;
        }
    QString print()
        {
            return QString::number(time.date().day())+"."+QString::number(time.date().month())+"."+QString::number(time.date().year())+"|"+time.time().toString()+"|"+QString::number(prior)+"|"+description;
        }
   virtual ~plan()
        {
            prior=0;
        }
   int& get_prior()
       {
            return prior;
       }
};

#endif // PLAN_H
