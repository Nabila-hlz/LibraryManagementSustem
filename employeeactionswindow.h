#ifndef EMPLOYEEACTIONSWINDOW_H
#define EMPLOYEEACTIONSWINDOW_H


#include <QWidget>

namespace Ui {
class EmployeeActionsWindow;
}

class EmployeeActionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeActionsWindow(QWidget *parent = nullptr);
    ~EmployeeActionsWindow();

private slots:
    void on_addResourceButton_clicked();
    void on_editResourceButton_clicked();
    void on_deleteResourceButton_clicked();
    void on_pushButtonSchedule_clicked();

private:
    Ui::EmployeeActionsWindow *ui;

signals:
    void eventScheduled(const QString& description);
};

#endif // EMPLOYEEACTIONSWINDOW_H
