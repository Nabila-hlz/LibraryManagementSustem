#ifndef BOOK_H
#define BOOK_H

#include "Resource.h"

class Book : public Resource
{
public:
    Book(QString title, QString author, int year, QString description, int quantity,
         QString isbn, QString publisher, QObject *parent = nullptr);
    QString toCSV() const override;
    ~Book () = default ;
private:
    QString isbn="";
    QString publisher="";
};
#endif

