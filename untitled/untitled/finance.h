#ifndef FINANCE_H
#define FINANCE_H

#include <QSqlTableModel>
#include <QSqlRecord>

class finance
{
public:
    finance();
    finance(double income, double expence);
    ~finance();
    finance operator+(finance sec);
    finance* operator=(finance sec);
    double getIncome();
    double getExpence();
    double getBalance();
    finance initialize(QSqlTableModel* base);
private:
    double income;
    double expence;
    double balance;
};

#endif // FINANCE_H
