#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
/* Класс продукт*/
class product
    {
protected:
        int kol = 1;               // Клоичество покупаемого
        QString description;
public:
        product()
            {   }
        product(int temp_kol,QString temp)
            {
                kol=temp_kol;
                description = temp;
            }
        virtual ~product()
            {
                kol=0;
                description.~QString();
            }
    };
#endif // PRODUCT_H
