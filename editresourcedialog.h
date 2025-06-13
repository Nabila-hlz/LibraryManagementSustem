#ifndef EDITRESOURCEDIALOG_H
#define EDITRESOURCEDIALOG_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class EditResourceDialog;
}

class EditResourceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditResourceDialog(QWidget *parent);
    ~EditResourceDialog();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();


private:
    Ui::EditResourceDialog *ui;
};

#endif // EDITRESOURCEDIALOG_H
