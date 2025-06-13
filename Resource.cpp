#include "Resource.h"
#include <QUuid>

#include <QDebug>

Resource::Resource(QString title, QString author, int year, QString description,
                   int quantity, Type type, QObject *parent)
    : QObject(parent), title(title), author(author), year(year),
    description(description), quantity(quantity), type(type)
{
    id = QUuid::createUuid().toString(QUuid::WithoutBraces);
}

QString Resource::toCSV() const
{
    // to not consider ""
    QString escapedTitle = title;
    escapedTitle.replace("\"", "\"\"");
    QString escapedAuthor = author;
    escapedAuthor.replace("\"", "\"\"");
    QString escapedDesc = description;
    escapedDesc.replace("\"", "\"\"");

    QString typeString = resourceTypeToString(type);

    return QString("\"%1\";\"%2\";\"%3\";%4;\"%5\";%6;\"%7\"")
        .arg(id)
        .arg(escapedTitle)
        .arg(escapedAuthor)
        .arg(year)
        .arg(escapedDesc)
        .arg(quantity)
        .arg(typeString);
}

QString resourceTypeToString(int typeId) {
    switch (typeId) {
    case 0: {return "Article"; break;}
    case 1: {return "Book"; break;}
    case 2: {return "DigitalBook"; break;}
    case 3: {return "Thesis"; break;}
    default: return "Unknown";
    }
}
