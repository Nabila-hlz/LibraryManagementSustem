#include "employeeactionswindow.h"
#include "ui_employeeactionswindow.h"
#include "addresourcedialog.h"
#include "editresourcedialog.h"
#include "deleteresourcedialog.h"
#include <QMessageBox>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QStandardPaths>

EmployeeActionsWindow::EmployeeActionsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EmployeeActionsWindow)
{
    ui->setupUi(this);
}

EmployeeActionsWindow::~EmployeeActionsWindow()
{
    delete ui;
}

void EmployeeActionsWindow::on_addResourceButton_clicked()
{
    AddResourceDialog dialog(this);
    dialog.exec();
}


void EmployeeActionsWindow::on_editResourceButton_clicked()
{
    EditResourceDialog *dialog = new EditResourceDialog(this);
    dialog->exec();
}


void EmployeeActionsWindow::on_deleteResourceButton_clicked()
{
    DeleteResourceDialog* dialog = new DeleteResourceDialog();
    dialog->exec();
}


void EmployeeActionsWindow::on_pushButtonSchedule_clicked()
{
    QString description = ui->textEditSchedule->toPlainText().trimmed();

    if (description.isEmpty()) {
        QMessageBox::warning(this, "Empty", "Please enter a description.");
        return;
    }
    QString projectDir = QDir::cleanPath(QDir::currentPath() + "/../../");
    QString filePath = QDir::cleanPath(projectDir + "/events.csv");
    QFile file(filePath);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);

        // to skip ""
        QString escapedDesc = description;
        escapedDesc.replace("\"", "\"\"");

        out << "\"" << escapedDesc << "\"\n";

        file.close();
        QMessageBox::information(this, "Saved", "Event description saved.");
        ui->textEditSchedule->clear();
    } else {
        QMessageBox::critical(this, "Error", "Cannot open events.csv for writing.");
    }
}




