#ifndef USERS_H
#define USERS_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class Users;
}

class Users : public QDialog
{
    Q_OBJECT

public:
    explicit Users(QWidget *parent = 0);
    ~Users();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void loadData();

    void on_eliminar_usuario_clicked();

    void on_actualizarUsuario_clicked();

private:
    Ui::Users *ui;
};

#endif // USERS_H
