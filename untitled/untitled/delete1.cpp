#include "delete1.h"
#include "ui_delete.h"
#include <QMessageBox>

Delete::Delete(int* number, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Delete)
{
    this->number = number;
    ui->setupUi(this);
}

Delete::~Delete()
{
    delete ui;
}

//int Delete::getNumber(){
//    return number-1;
//}

void Delete::on_pushButton_2_clicked()
{
    this->close();
}

void Delete::on_pushButton_clicked()
{
    bool flg;
    QString str= ui->textEdit->toPlainText();
    *number = str.toInt(&flg);
    if(!flg){
        QMessageBox msgBox;
        msgBox.setText("Error number");
        msgBox.exec();
    } else {
        emit deleteNumber(*number);
        this->close();
    }
}
