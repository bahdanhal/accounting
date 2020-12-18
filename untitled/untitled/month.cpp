#include "month.h"
#include "ui_month.h"
#include <QDebug>
#include <iostream>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

int Month::balanceRead()
{
    double sum;
    for (int i = 0; i < base->rowCount() - 1; ++i) {
        //суммируем значения во всех ячейках 0-ого столбца
        sum = 0;
        sum += base->data(base->index(i, 1)).toDouble();
        sum += base->data(base->index(i, 2)).toDouble();
    }
    return 1;
}

Month::Month(int number, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Month)
{
    ui->setupUi(this);

    if(!this->createConnection(number)){
        this->close();
    }
    base = new QSqlTableModel;
    initializeModel(base);
    ui->tableView->setModel(base);
    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    int lastRow = base->rowCount();
    if(lastRow==0){
        if(!base->insertRow(0)){
            QMessageBox::critical(this, tr("БД"),
                                tr("Вставка строки вызвала следующую ошибку:\r\n %1").arg(base->lastError().databaseText()));
        } else {
            base->setData(base->index(lastRow,1),"");
        }
    }
    base->submitAll();
    ui->tableView->show();
}

bool Month::createConnection(int monthNumber)
{
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    switch (monthNumber) {
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

    if (!sdb.open()) {  //TODO
        return 0;
    }
    return 1;
}

void initializeModel(QSqlTableModel *model)
{
    model->setTable("month");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    qDebug() << model->rowCount();
    initializeHeader(model);
}

void initializeHeader(QSqlTableModel *model)
{
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Номер"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Получено"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Отдано"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Баланс"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Счет №1"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Счет №2"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Дата"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Заметка"));
}

Month::~Month()
{
    delete ui;
}

void closeDb()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
    QSqlDatabase::removeDatabase(db.connectionName());
}

void Month::on_pushButton_clicked()
{
    closeDb();
    this->close();      // Закрываем окно
    emit monthWindow();
}


void Month::on_pushButton_2_clicked()//расчет
{
    month = finance(0,0);
    base->setData(base->index(0, 3), base->record(0).value("income").toDouble()-base->record(0).value("expence").toDouble());
    for(int count = 1; count<base->rowCount(); count++){
        base->setData(base->index(count, 3), base->record(count).value("income").toDouble()-
                      base->record(count).value("expence").toDouble()+base->record(count-1).value("balance").toDouble());
    }
    month.initialize(base);
    ui->textBrowser_3->setText(QString::number(month.getIncome()));
    ui->textBrowser_4->setText(QString::number(month.getExpence()));
    ui->textBrowser_6->setText(QString::number(month.getBalance()));
}

//void Month::on_pushButton_3_clicked()//сохр
//{
//
//}

void Month::on_pushButton_4_clicked()//добав
{
    //base->database().transaction();
    int lastRow = base->rowCount();
    if(!base->insertRow(lastRow)){
        QMessageBox::critical(this, tr("БД"),
                            tr("Вставка строки вызвала следующую ошибку:\r\n %1").arg(base->lastError().databaseText()));
    }
    base->setData(base->index(lastRow,0), lastRow+1);
    base->submitAll();
    ui->tableView->selectRow(lastRow);
    ui->tableView->setFocus();
    /*QSqlRecord rec = base->record();
    int lastRow = base->rowCount();
    base->insertRecord(lastRow,rec);
    base->submitAll();*/
}

void Month::on_pushButton_5_clicked()//удал
{
   // int number;
    //number = base->rowCount();
   // deleteWindow = new Delete(&number);
   // connect(this, clicked(), deleteWindow,  setText()))
    //deleteWindow->show();
   // if(!base->removeRow(number)){
   //     QMessageBox msgBox;
   //     msgBox.setText("Delete error");
   //     msgBox.exec();
   // } else {
   //     ui->tableView->setRowHidden(number, true);
   // }
    bool flg;
    QString str= ui->textEdit->toPlainText();
    int number = str.toInt(&flg) - 1;
    if(!flg){
        QMessageBox msgBox;
        msgBox.setText("Error number");
        msgBox.exec();
    } else {
        if(!base->removeRow(number)){
            QMessageBox msgBox;
            msgBox.setText("Delete error");
            msgBox.exec();
        } else {
            ui->tableView->setRowHidden(number, true);
        }
    }
    base->submitAll();
}
