#ifndef RESOURCE_H
#define RESOURCE_H

#include <QObject>
#include <QString>

class Resource : public QObject
{
    Q_OBJECT
public:
    enum Type { BOOK, DIGITAL_BOOK, THESIS, ARTICLE };
    Q_ENUM(Type)

    Resource(QString title, QString author, int year, QString description,
             int quantity, Type type, QObject *parent = nullptr);

    virtual ~Resource() = default;

    //getters
    QString getId() const { return id; }
    QString getTitle() const { return title; }
    QString getAuthor() const { return author; }
    int getYear() const { return year; }
    QString getDescription() const { return description; }
    int getQuantity() const { return quantity; }
    Type getType() const { return type; }

    friend QString resourceTypeToString(int typeId);
    virtual QString toCSV() const;

protected:
    QString id;
    QString title;
    QString author;
    int year;
    QString description;
    int quantity;
    Type type;
};
QString resourceTypeToString(int typeId);
#endif
