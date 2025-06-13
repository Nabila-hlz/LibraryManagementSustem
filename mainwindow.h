#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "employeeactionswindow.h"
#include <QMainWindow>
#include <QtCore>
//#include "employeeactionswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

public slots :
    void onEventScheduled(const QString &description);

private:
    Ui::MainWindow *ui;
    EmployeeActionsWindow* empActWind;
};
#endif // MAINWINDOW_H
