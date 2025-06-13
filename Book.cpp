/*#include "Book.h"

Book::Book(QString title, QString author, int year, QString description, int quantity,
           QString isbn, QString publisher, QObject *parent)
    : Resource(title, author, year, description, quantity, Resource::BOOK, parent),
    isbn(isbn), publisher(publisher)
{
}

QString Book::toCSV() const
{
    return Resource::toCSV() + QString(",\"%1\",\"%2\"").arg(isbn).arg(publisher);
}
*/
// book.cpp
#include "Book.h"

Book::Book(QString title, QString author, int year, QString description, int quantity, QString isbn, QString publisher, QObject *parent)
    : Resource(title, author, year, description, quantity, Resource::BOOK, parent),
    isbn("ISBN-" + QString::number(rand() % 10000)),
    publisher("Unknown Publisher")
{
}

QString Book::toCSV() const
{
    return Resource::toCSV() +
           QString(";\"%1\";\"%2\"")
               .arg(isbn)
               .arg(publisher);
}
