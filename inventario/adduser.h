#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = 0);
    ~AddUser();

private slots:
    void on_save_clicked();

    void on_pushButton_clicked();

    void on_guardar_clicked();

private:
    Ui::AddUser *ui;
};

#endif // ADDUSER_H
