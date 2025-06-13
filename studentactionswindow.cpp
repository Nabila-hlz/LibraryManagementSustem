#include "studentactionswindow.h"
#include "ui_studentactionswindow.h"
#include <QFile>
#include <QMessageBox>
#include <QStringList>
#include <QTextStream>
#include <QString>
#include <QDir>
#include <QStandardPaths>

StudentActionsWindow::StudentActionsWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StudentActionsWindow)
{
    ui->setupUi(this);
    connect(ui->comboBoxType, &QComboBox::currentTextChanged,ui->lineEdit, &QLineEdit::setText);

}

StudentActionsWindow::~StudentActionsWindow()
{
    delete ui;
}

void StudentActionsWindow::on_pushButtonBorrow_clicked()
{
    {
        QString title = ui->lineEditTitle->text().trimmed();
        QString type = ui->lineEdit->text().trimmed();

        if (title.isEmpty() || type.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Enter both title and type.");
            return;
        }
        QString projectDir = QDir::cleanPath(QDir::currentPath() + "/../../");
        QString filePath = QDir::cleanPath(projectDir + "/resources.csv");
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "File Error", "Could not open resources.csv for reading.");
            return;
        }


        QStringList lines;
        bool found = false;

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(';');
            if (fields.size() >= 7) {
                QString rTitle = fields[1].remove('\"');
                //QString rType = type;

                if (rTitle.compare(title, Qt::CaseInsensitive) == 0
                    /*rType.compare(type, Qt::CaseInsensitive) == 0*/)
                {
                    found = true;
                    int quantity = fields[5].toInt();
                    if (quantity > 0) {
                        fields[5] = QString::number(quantity - 1);
                        QMessageBox::information(this, "Success", "Borrowed successfully.");
                    } else {
                        QString projectDire = QDir::cleanPath(QDir::currentPath() + "/../../");
                        QString filePathe = QDir::cleanPath(projectDire + "/reservations.csv");
                        QFile resFile(filePathe);

                        if (resFile.open(QIODevice::Append | QIODevice::Text)) {
                            QTextStream resOut(&resFile);
                            resOut << "\"" << title << "\";\"" << type << "\"\n";
                            resFile.close();
                        }
                        QMessageBox::warning(this, "Unavailable", "Resource unavailable for the moment. You reserve it.");
                        return;
                    }
                }
            }
            lines << fields.join(';');
        }
        file.close();

        if (!found) {
            QMessageBox::warning(this, "Not Found", "Resource not found.");
            return;
        }
        QString projectDirec = QDir::cleanPath(QDir::currentPath() + "/../../");
        QString outtPathee = QDir::cleanPath(projectDirec + "/resources.csv");
        QFile outFile(outtPathee); //if borrowed successfully update resources
        if (outFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            QTextStream out(&outFile);
            for (const QString& l : lines)
                out << l << "\n";
            outFile.close();
        }
    }
}

void StudentActionsWindow::on_pushButton_3_clicked()
{
    QString projectDirc = QDir::cleanPath(QDir::currentPath() + "/../../");
    QString evPathe = QDir::cleanPath(projectDirc + "/events.csv");
    QFile file(evPathe);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "File Error", "Could not open resources.csv for reading.");
        return;
    }

    QTextStream in(&file);
    QString content;
    while (!in.atEnd()) {
        content += in.readLine() + "\n";
    }
    file.close();

    ui->plainTextEvent->setPlainText(content);
}


void StudentActionsWindow::on_pushButtonReturn_clicked()
{
    QString title = ui->lineEditTitle->text().trimmed();
    QString type = ui->lineEdit->text().trimmed();
    if (title.isEmpty() || type.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Enter both title and type.");
        return;
    }
    QString projectDir = QDir::cleanPath(QDir::currentPath() + "/../../");
    QString filePath = QDir::cleanPath(projectDir + "/resources.csv");
    QFile file(filePath);

    bool found = false;
    QStringList lines;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "File Error", "Could not open resources.csv for reading.");
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(';');
    if (fields.size() >= 7) {
        QString rTitle = fields[1].remove('\"');
        QString rType = fields[6].remove('\"');

        if (rTitle.compare(title, Qt::CaseInsensitive) == 0 &&
            rType.compare(type, Qt::CaseInsensitive) == 0)
        {
            found=true;
            int quantity = fields[5].toInt();
            if (quantity >= 0) {
                fields[5] = QString::number(quantity + 1);
                QMessageBox::information(this, "Success", "Returned successfully.");
            }
        }
    }
    lines << fields.join(';');
    }
    file.close();

    if (!found) {
        QMessageBox::warning(this, "Not Found", "Resource not found.");
        return;
    }
    QFile outFile(filePath);
    if (outFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream out(&outFile);
        for (const QString &line : lines)
            out << line << "\n";
        outFile.close();
    } else {
        QMessageBox::critical(this, "File Error", "Could not open resources.csv to save changes.");
    }
}
