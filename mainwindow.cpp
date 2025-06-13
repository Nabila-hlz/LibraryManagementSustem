#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "libraryemployeeinterface.h"
#include "employeeactionswindow.h"
#include "studentactionswindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), empActWind(nullptr)
{
    ui->setupUi(this);
    QString testPath = QCoreApplication::applicationDirPath() + "/resources.csv";
    //qDebug() << "CSV file will be saved to:" << testPath;

    QFile testFile(testPath);
    if(testFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        //qDebug() << "File opened successfully";
        testFile.close();
    } /*else {
        //qDebug() << "File open failed:" << testFile.errorString();
    }*/
    connect(empActWind, &EmployeeActionsWindow::eventScheduled,
            this, &MainWindow::onEventScheduled);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setWindowTitle(tr("About LMS"));
    msgBox->setText(
        tr("This Library Management System was developed by Nabila Hallouz\n"
           "Using C++ and Qt after getting inspired by 2024 projects, YouTube videos, OOP course and chatbots.")
        );
    msgBox->setStyleSheet(
        "QMessageBox, QMessageBox QLabel, QMessageBox QPushButton {"
        "background-image: url(:/bleu/bleu.jpg);"
        "background-repeat: no-repeat;"
        "background-position: center;"
        "color: black;"
        "}"
        );

    msgBox->exec();
}


void MainWindow::on_pushButton_2_clicked()
{
    LibraryEmployeeInterface lei;
    lei.setModal(true);
    lei.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    StudentActionsWindow saw;
    saw.exec();
}
void MainWindow::onEventScheduled(const QString& description)
{
    ui->labelEventDisplay->setText("📌 " + description);
}

