#include "adduser.h"
#include "ui_adduser.h"

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
    /*
     * Inicializa la clase MainWindow en el objeto connection y
     * Valida la conexion a la BD
    */\

    MainWindow connection;

    if (!connection.dbOpen()) {
        QMessageBox::critical(this, tr("Error!"), tr("Ocurrio un error al cargar la Base de Datos"));
    }
}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::on_guardar_clicked()
{
    QString usuario, pass, pass2, nombre, tipo;
    pass = ui->pass->text();
    pass2 = ui->pass2->text();

    if (pass == pass2) {
        usuario = ui->usuario->text();
        nombre = ui->nombre->text();
        ui->notify->setText("El usuario se creo correctamenta!");
        /*
        if ()
        tipo = ui->administrador->isChecked();
        */
        QMessageBox::warning (this, tr("Error de Sesion"), tr("Usuario o password incorrectos!"));
    } else {
        QMessageBox::warning (this, tr("Error de Sesion"), tr("Usuario o password incorrectos!"));
        ui->notify->setText("Error, las contraseñas no coinciden");
    }
}
