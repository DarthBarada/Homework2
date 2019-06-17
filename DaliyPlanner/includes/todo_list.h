#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <QList>

#include "case.h"

/* Класс to-do list состоит из queue <дело> */
class do_list
    {
protected:
        QList <business> list;
public:
        do_list()
            {   }
        ~do_list()
            {
                list.~QList();
            }
    };
#endif // TODO_LIST_H
