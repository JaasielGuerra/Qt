#ifndef CREATEUSER_H
#define CREATEUSER_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class CreateUser;
}

class CreateUser : public QDialog
{
    Q_OBJECT

public:
    explicit CreateUser(QWidget *parent = 0);
    ~CreateUser();
    void updateUser(QString);

private slots:
    void on_guardar_clicked();

    void on_pushButton_clicked();

    void on_subirFoto_clicked();

private:
    Ui::CreateUser *ui;
    int funcion=0;
    QString foto, imagen;
};

#endif // CREATEUSER_H
