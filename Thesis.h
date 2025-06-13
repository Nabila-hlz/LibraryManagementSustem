#ifndef THESIS_H
#define THESIS_H

#include "Resource.h"

class Thesis : public Resource
{
public:
    Thesis(QString title, QString author, int year, QString description, int quantity,
           QString university, QString degree, QObject *parent = nullptr);
    QString toCSV() const override;
    ~Thesis() = default;

private:
    QString university=" ";
    QString degree="";
};
#endif
