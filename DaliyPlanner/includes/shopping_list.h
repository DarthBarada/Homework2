#ifndef SHOPPING_LIST_H
#define SHOPPING_LIST_H

#include <QMap>
#include <QString>

#include "product.h"
/* Класс shopping list состоит из map <имя продукта, продукт> */
class shopping_list:public product
    {
protected:
        QMap <QString,product> products;
public:
        shopping_list()
            {   }
        virtual ~shopping_list()
            {
               products.~QMap();
            }
    };

#endif // SHOPPING_LIST_H
