#include "deleteresourcedialog.h"
#include "ui_deleteresourcedialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QStandardPaths>

DeleteResourceDialog::DeleteResourceDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DeleteResourceDialog)
{
    ui->setupUi(this);

    connect(ui->comboBoxType, &QComboBox::currentTextChanged,ui->lineEdit, &QLineEdit::setText);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DeleteResourceDialog::on_buttonBox_accepted);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &DeleteResourceDialog::reject);
}

DeleteResourceDialog::~DeleteResourceDialog()
{
    delete ui;
}

void DeleteResourceDialog::on_buttonBox_accepted()
{
    QString title = ui->lineEditTitle->text().trimmed();
    QString type = ui->lineEdit->text().trimmed();

    if (title.isEmpty() || type.isEmpty()) {
        QMessageBox::warning(this, "Missing Data", "Please enter both title and type.");
        return;
    }

    QString projectDir = QDir::cleanPath(QDir::currentPath() + "/../../");
    QString filePath = QDir::cleanPath(projectDir + "/resources.csv");
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open resources.csv");
        return;
    }

    QStringList lines;
    QTextStream in(&file);
    bool found = false;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(';');

        if (fields.size() < 8) {
            lines << line;
            continue;
        }

        // if found
        if (fields[1].trimmed() == title && fields[6].trimmed() == type) {
            found = true;
            continue;       // to skip adding this line to .csv
        }

        lines << line;
    }
    file.close();
    if (!found) {
        QMessageBox::warning(this, "Not Found", "No matching resource found to delete.");
        return;
    }

    // Rewrite without deleted
    QFile outFile(filePath);  // ← Use a new QFile object
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::critical(this, "Error", "Unable to write to resources.csv");
        return;
    }

    QTextStream out(&outFile);
    for (const QString &line : lines)
        out << line << "\n";

    outFile.close();


    QMessageBox::information(this, "Deleted", "Resource successfully deleted.");
    accept();
}

void DeleteResourceDialog::on_buttonBox_rejected()
{
    reject();
}

