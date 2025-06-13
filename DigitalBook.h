#ifndef DIGITALBOOK_H
#define DIGITALBOOK_H

#include "Resource.h"

class DigitalBook : public Resource
{
public:
    DigitalBook(QString title, QString author, int year, QString description, int quantity,
                QString format, QString url, QObject *parent = nullptr);
    QString toCSV() const override;
    ~DigitalBook() = default;

private:
    QString format="";
    QString url="";
};
#endif
