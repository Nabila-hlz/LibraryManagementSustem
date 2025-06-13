#include "DigitalBook.h"

DigitalBook::DigitalBook(QString title, QString author, int year, QString description, int quantity,
                         QString format, QString url, QObject *parent)
    : Resource(title, author, year, description, quantity, Resource::DIGITAL_BOOK, parent),
    format(format), url(url)
{
}

QString DigitalBook::toCSV() const
{
    return Resource::toCSV() + QString(";\"%1\";\"%2\"").arg(format).arg(url);
}
