#include "editresourcedialog.h"
#include "ui_editresourcedialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDir>

EditResourceDialog::EditResourceDialog( QWidget *parent)
    : QDialog(parent), ui(new Ui::EditResourceDialog)
{
    ui->setupUi(this);
    connect(ui->comboBoxType, &QComboBox::currentTextChanged,ui->lineEdit, &QLineEdit::setText);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EditResourceDialog::on_buttonBox_accepted);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &EditResourceDialog::reject);
}

EditResourceDialog::~EditResourceDialog()
{
    delete ui;
}

void EditResourceDialog::on_buttonBox_accepted()
{
    QString title = ui->lineEditTitle->text().trimmed();
    QString type = ui->lineEdit->text().trimmed();
    int quantity = ui->spinBoxQuantity->value();
    QString extra = ui->lineEditAdditional->text().replace(';', " ");  // avoid delimiter issues

    if (title.isEmpty() || type.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Title and type must be filled.");
        return;
    }
    QString projectDir = QDir::cleanPath(QDir::currentPath() + "/../../");
    QString filePath = QDir::cleanPath(projectDir + "/resources.csv");
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open resources.csv");
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

        if (fields[1].trimmed() == title && fields[6].trimmed() == type) {
            // Found -then-> modify
            fields[5] = QString::number(quantity);
            fields[7] = extra;
            line = fields.join(';');
            found = true;
        }

        lines << line;
    }

    file.close();

    if (!found) {
        QMessageBox::warning(this, "Not Found", "No matching resource found.");
        return;
    }

    // Rewrite file
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::critical(this, "Error", "Cannot write to resources.csv file.");
        return;
    }

    QTextStream out(&file);
    for (const QString &line : lines)
        out << line << "\n";

    file.close();

    QMessageBox::information(this, "Updated", "Resource updated successfully.");
    accept();
}

void EditResourceDialog::on_buttonBox_rejected()
{
    reject();
}

