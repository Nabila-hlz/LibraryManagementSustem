#ifndef LIBRARYEMPLOYEEINTERFACE_H
#define LIBRARYEMPLOYEEINTERFACE_H
#include "employeeactionswindow.h"
#include <QDialog>

namespace Ui {
class LibraryEmployeeInterface;
}

class LibraryEmployeeInterface : public QDialog
{
    Q_OBJECT

public:
    explicit LibraryEmployeeInterface(QWidget *parent = nullptr);
    ~LibraryEmployeeInterface();

private slots:
    void on_loginButton_clicked();

private:
    Ui::LibraryEmployeeInterface *ui;
    bool isValidEmployee(const QString &name, const QString &id);
};

#endif // LIBRARYEMPLOYEEINTERFACE_H
