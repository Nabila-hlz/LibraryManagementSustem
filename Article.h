#ifndef ARTICLE_H
#define ARTICLE_H

#include "Resource.h"

class Article : public Resource
{
public:
    Article(QString title, QString author, int year, QString description, int quantity,
            QString journal, QString doi, QObject *parent = nullptr);
    QString toCSV() const override;
    ~Article() = default;
private:
    QString journal="";
    QString doi="";
};
#endif
