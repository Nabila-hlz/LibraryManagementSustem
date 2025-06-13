#include "Thesis.h"

Thesis::Thesis(QString title, QString author, int year, QString description, int quantity,
               QString university, QString degree, QObject *parent)
    : Resource(title, author, year, description, quantity, Resource::THESIS, parent),
    university(university), degree(degree)
{
}

QString Thesis::toCSV() const
{
    return Resource::toCSV() + QString(";\"%1\";\"%2\"").arg(university).arg(degree);
}
