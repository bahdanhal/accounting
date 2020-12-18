#ifndef MONTH_H
#define MONTH_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QTableView>
#include "delete1.h"
#include "finance.h"

namespace Ui {
class Month;
}

class Month : public QMainWindow
{
    Q_OBJECT

public:
    explicit Month(int number, QWidget *parent = nullptr);
    ~Month();
    bool createConnection(int monthNumber);
    int balanceRead();

signals:
    void monthWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Month *ui;
    QSqlTableModel *base;
    QSqlDatabase sdb;
    finance month;
    Delete* deleteWindow;
};

void initializeModel(QSqlTableModel *model);
void initializeHeader(QSqlTableModel *model);
void closeDb();
#endif // MONTH_H
