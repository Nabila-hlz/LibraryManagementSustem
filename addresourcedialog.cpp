#include "addresourcedialog.h"
#include "ui_addresourcedialog.h"
#include <QFile>
#include <QMessageBox>
#include "Resource.h"
#include "addresourcedialog.h"
#include "Book.h"
#include "Thesis.h"
#include "DigitalBook.h"
#include "Article.h"
#include <QTextStream>
#include <QDir>
#include <QStandardPaths>

AddResourceDialog::AddResourceDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddResourceDialog)
{
    ui->setupUi(this);
    connect(ui->comboBox, &QComboBox::currentTextChanged,ui->lineEdit, &QLineEdit::setText);
}

AddResourceDialog::~AddResourceDialog()
{
    delete ui;
}

void AddResourceDialog::on_buttonBox_accepted()
{
    QString title = ui->Title->text().trimmed();
    QString author = ui->Author->text().trimmed();
    int year = ui->Year->value();
    QString description = ui->Description->toPlainText().trimmed();
    int quantity = ui->Quantity->value();

    QString typeText = ui->lineEdit->text();
    Resource::Type type;

    if (typeText == "Book") type = Resource::BOOK;
    else if (typeText == "DigitalBook") type = Resource::DIGITAL_BOOK;
    else if (typeText == "Thesis") type = Resource::THESIS;
    else if (typeText == "Article") type = Resource::ARTICLE;
    // no empty inputs
    if(title.isEmpty() || author.isEmpty()) {
        QMessageBox::warning(this, "Error", "Title and author cannot be empty!");
        return;
    }

    Resource* resource = nullptr;

    switch(type) {
    case Resource::BOOK:
        resource = new Book(title, author, year, description, quantity,"unknown", "0", this);
        break;
    case Resource::DIGITAL_BOOK:
        resource = new DigitalBook(title, author, year, description, quantity, " ", " ", this);
        break;
    case Resource::THESIS:
        resource = new Thesis(title, author, year, description, quantity," "," ", this);
        break;
    case Resource::ARTICLE:
        resource = new Article(title, author, year, description, quantity, " ", " ", this);
        break;
    }

    if(resource) {
        if(saveToCSV(resource)) {
            QMessageBox::information(this, "Success", "Resource added successfully!");
        } else {
            QMessageBox::critical(this, "Error", "Failed to save resource!");
        }
        resource->deleteLater();
    }
}

bool AddResourceDialog::saveToCSV(Resource* resource)
{
    QString projectDir = QDir::cleanPath(QDir::currentPath() + "/../../");
    QString filePath = QDir::cleanPath(projectDir + "/resources.csv");
    QFile file(filePath);

    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << resource->toCSV() << "\n";
        file.close();
        //qDebug() << "Resource saved to:" << filePath;
        return true;
    } else {
        //qDebug() << "Error saving to CSV:" << file.errorString();
        return false;
    }
}

void AddResourceDialog::on_buttonBox_rejected()
{
    reject();
}

