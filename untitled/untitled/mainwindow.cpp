#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

int MainWindow::initializeData()
{
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery query;
    finance nil(0,0);
    year=nil;
    for(int month = 1; month<14; month++){
        if (!sdb.open()) {  //TODO
            QMessageBox msgBox;
            msgBox.setText("Open error");
            msgBox.exec();
            return 0;
        }
        QMessageBox msgBox;
        switch (month) {
        case 1:
            sdb.setDatabaseName("jan.sqlite");
            break;
        case 2:
            sdb.setDatabaseName("feb.sqlite");
            break;
        case 3:
            sdb.setDatabaseName("mar.sqlite");
            break;
        case 4:
            sdb.setDatabaseName("apr.sqlite");
            break;
        case 5:
            sdb.setDatabaseName("may.sqlite");
            break;
        case 6:
            sdb.setDatabaseName("jun.sqlite");
            break;
        case 7:
            sdb.setDatabaseName("jul.sqlite");
            break;
        case 8:
            sdb.setDatabaseName("aug.sqlite");
            break;
        case 9:
            sdb.setDatabaseName("sep.sqlite");
            break;
        case 10:
            sdb.setDatabaseName("oct.sqlite");
            break;
        case 11:
            sdb.setDatabaseName("nov.sqlite");
            break;
        case 12:
            sdb.setDatabaseName("dec.sqlite");
            break;
        }
        QSqlTableModel base;
        query.exec("CREATE TABLE IF NOT EXISTS month(number INTEGER, income DOUBLE, expence DOUBLE, balance DOUBLE,"
        " firstAccount TEXT, secondAccount TEXT, date TEXT, note TEXT)");
        base.setTable("month");
        base.select();
        base.setData(base.index(0, 0), 1);
        finance current;
        current.initialize(&base);
        year = year + current;
        base.submitAll();
        sdb.close();
    }
    return 1;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    initializeData();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMonth(int number)
{
    monthData = new Month(number);
    connect(monthData, &Month::monthWindow, this, &MainWindow::show);
    monthData->show();
    this->close();
}

void MainWindow::on_calculation_clicked()
{
    initializeData();
    ui->textBrowser_4->setText(QString::number(year.getIncome()));
    ui->textBrowser_5->setText(QString::number(year.getExpence()));
    ui->textBrowser_6->setText(QString::number(year.getIncome()-year.getExpence()));
}

void MainWindow::on_pushButton_clicked()
{
    showMonth(1);
}

void MainWindow::on_pushButton_2_clicked()
{
    showMonth(2);
}

void MainWindow::on_pushButton_3_clicked()
{
    showMonth(3);
}

void MainWindow::on_pushButton_4_clicked()
{
    showMonth(4);
}

void MainWindow::on_pushButton_5_clicked()
{
    showMonth(5);
}

void MainWindow::on_pushButton_6_clicked()
{
    showMonth(6);
}

void MainWindow::on_pushButton_7_clicked()
{
    showMonth(7);
}

void MainWindow::on_pushButton_8_clicked()
{
    showMonth(8);
}

void MainWindow::on_pushButton_9_clicked()
{
    showMonth(9);
}

void MainWindow::on_pushButton_10_clicked()
{
    showMonth(10);
}

void MainWindow::on_pushButton_11_clicked()
{
    showMonth(11);
}

void MainWindow::on_pushButton_12_clicked()
{
    showMonth(12);
}

