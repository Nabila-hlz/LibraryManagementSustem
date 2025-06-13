#ifndef STUDENTACTIONSWINDOW_H
#define STUDENTACTIONSWINDOW_H

#include <QDialog>

namespace Ui {
class StudentActionsWindow;
}

class StudentActionsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StudentActionsWindow(QWidget *parent = nullptr);
    ~StudentActionsWindow();

private slots:
    void on_pushButtonBorrow_clicked();
    void on_pushButton_3_clicked();

    void on_pushButtonReturn_clicked();

private:
    Ui::StudentActionsWindow *ui;
};

#endif // STUDENTACTIONSWINDOW_H
