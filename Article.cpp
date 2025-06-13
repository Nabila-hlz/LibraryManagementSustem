#include "Article.h"

Article::Article(QString title, QString author, int year, QString description, int quantity,
                 QString journal, QString doi, QObject *parent)
    : Resource(title, author, year, description, quantity, Resource::ARTICLE, parent),
    journal(journal), doi(doi)
{
}

QString Article::toCSV() const
{
    return Resource::toCSV() + QString(";\"%1\";\"%2\"").arg(journal).arg(doi);
}
