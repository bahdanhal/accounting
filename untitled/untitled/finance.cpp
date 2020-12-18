#include "finance.h"
#include <QDebug>
finance::finance()
{
    income = 0;
    expence = 0;
    balance = 0;
}

finance::finance(double income, double expence)
{
    this->income = income;
    this->expence = expence;
    this->balance = income - expence;
    qDebug() << balance;
}

finance::~finance()
{

}

finance finance::operator+(finance sec)
{
    finance result(this->income + sec.income, this->expence + sec.expence);
    return result;
}

finance* finance::operator=(finance sec)
{
    this->income = sec.income;
    this->expence = sec.expence;
    this->expence = sec.expence;
    return this;
}

double finance::getIncome()
{
    return income;
}

double finance::getExpence()
{
    return expence;
}

double finance::getBalance()
{
    return balance;
}

finance finance::initialize(QSqlTableModel* base)
{
    qDebug() << base->rowCount();
    for(int count = 0; count < base->rowCount(); count++){

        finance current(base->record(count).value("income").toDouble(), base->record(count).value("expence").toDouble());
        qDebug()<<current.balance<<"asdsad";
        *this = *this + current;
    }
    this->balance = this->income - this->expence;
    return *this;
}
