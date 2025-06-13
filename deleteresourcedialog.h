#ifndef DELETERESOURCEDIALOG_H
#define DELETERESOURCEDIALOG_H

#include <QDialog>

namespace Ui {
class DeleteResourceDialog;
}

class DeleteResourceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteResourceDialog(QWidget *parent = nullptr);
    ~DeleteResourceDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::DeleteResourceDialog *ui;
};

#endif // DELETERESOURCEDIALOG_H
