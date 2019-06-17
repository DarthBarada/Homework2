#ifndef CASE_H
#define CASE_H

#include <QString>
/* Класс business(дело)*/
class business
    {
protected:
        QString description;    // Описание дела
        int status;            //  статус дела (0-не приступил;1-приступил;2-выполнил)
public:
        business()
            {   }
        business(QString temp,int temp_status=0)
            {
               description=temp;
               status=temp_status;
            }
        ~business()
            {
                status=0;
                description.~QString();
            }
        QString& get_description()
            {
                return description;
            }
        int& get_status()
            {
                return status;
            }
    };

#endif // CASE_H
