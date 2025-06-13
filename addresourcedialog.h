#ifndef ADDRESOURCEDIALOG_H
#define ADDRESOURCEDIALOG_H
#include "Resource.h"
#include "Article.h"
#include "Book.h"
#include "DigitalBook.h"
#include "Thesis.h"

#include <QDialog>

namespace Ui {
class AddResourceDialog;
}

class AddResourceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddResourceDialog(QWidget *parent = nullptr);
    ~AddResourceDialog();
    bool saveToCSV(Resource* resource);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();


private:
    Ui::AddResourceDialog *ui;
};

#endif // ADDRESOURCEDIALOG_H
