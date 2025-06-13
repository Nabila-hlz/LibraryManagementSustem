#include "libraryemployeeinterface.h"
#include "ui_libraryemployeeinterface.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "employeeactionswindow.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QDir>
#include <QStandardPaths>*

LibraryEmployeeInterface::LibraryEmployeeInterface(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LibraryEmployeeInterface)
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &LibraryEmployeeInterface::on_loginButton_clicked);
}

LibraryEmployeeInterface::~LibraryEmployeeInterface()
{
    delete ui;
}

void LibraryEmployeeInterface::on_loginButton_clicked()
{

    QString name = ui->nameLineEdit->text().trimmed();
    QString id = ui->idLineEdit->text().trimmed();

    if (isValidEmployee(name, id)) {
        ui->statusLabel->setText("✅ Access granted");
        EmployeeActionsWindow *actionsWindow = new EmployeeActionsWindow();
        actionsWindow->show();
        this->close();
    } else {
        ui->statusLabel->setText("❌ Invalid name or ID");
    }
}

bool LibraryEmployeeInterface::isValidEmployee(const QString &name, const QString &id)
{
    QString projectDir = QDir::cleanPath(QDir::currentPath() + "/../../");
    QString filePath = QDir::cleanPath(projectDir + "/libraryemployees.csv");
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "File failed to open.";
        return false;
    }

    QTextStream in(&file);
    in.readLine();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(";");
        if (fields.size() >= 2) {
            QString fileName = fields[0].trimmed();
            QString fileId = fields[1].trimmed();
            qDebug() << "Checking against:" << fileName << fileId;

            if (fileName == name && fileId == id) {
                qDebug() << "Match found!";
                return true;
            }
        }
    }
    qDebug() << "No match found ";
    return false;
}

