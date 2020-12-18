#ifndef DELETE_H
#define DELETE_H

#include <QDialog>

namespace Ui {
class Delete;
}

class Delete : public QDialog
{
    Q_OBJECT

public:
    explicit Delete(int* number, QWidget *parent = nullptr);
    ~Delete();
    int getNumber();

signals:
    void deleteNumber(int);


private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Delete *ui;
    int* number;
};

#endif // DELETE_H
