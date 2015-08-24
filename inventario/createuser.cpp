#include "createuser.h"
#include "ui_createuser.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

CreateUser::CreateUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateUser)
{
    ui->setupUi(this);

    /*
     * Carga la imagen para el background
    */
    QPixmap bkgnd("../imagenes/system/background2.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    /*
     * Valida la conexion a la BD
    */\

    DBConnect connection;
    if (!connection.dbOpen()) {
        QMessageBox::critical(this, tr("Error!"), tr("Ocurrio un error al cargar la Base de Datos"));
    }

    QPixmap foto1("../imagenes/system/user.png");
    ui->foto->setPixmap(foto1);
    ui->foto->setScaledContents(true);
}

CreateUser::~CreateUser()
{
    delete ui;
}

void CreateUser::updateUser(QString user) {
    QString userUpdate = user;

    DBConnect connect;
    connect.dbOpen();

    QSqlQuery query;
    query.exec("SELECT usuario, nombre, tipo, foto FROM empleados WHERE usuario = '"+userUpdate+"'");

    while (query.next()) {
        QPixmap fotoUp(query.value(3).toString());
        ui->foto->setPixmap(fotoUp);
        ui->foto->setScaledContents(true);

        ui->usuario->setText(query.value(0).toString());
        ui->nombre->setText(query.value(1).toString());
        if (query.value(2) == "administrador") {
            ui->administrador->setChecked(true);
        }
        else if (query.value(2) == "vendedor") {
            ui->vendedor->setChecked(true);
        }
        else if (query.value(2) == "proveedor") {
            ui->proveedor->setChecked(true);
        }
    }
}

void CreateUser::on_guardar_clicked()
{
    /*
     * Inicializa las clases en los objetos
    */
    DBConnect connection;
    connection.dbOpen();

    QString usuario, pass, pass2, nombre, tipo;
    pass = ui->pass->text();
    pass2 = ui->pass2->text();

    if ( (pass == pass2) && ( pass != "" || pass2 != "" ) ) {
        usuario = ui->usuario->text();
        if (usuario != "") {

            QSqlQuery verifica;
            verifica.prepare("SELECT * FROM empleados WHERE usuario = '"+usuario+"'");
            verifica.exec();
            if (verifica.next()) {
                funcion = 1;
            } else {
                funcion = 0;
            }

            nombre = ui->nombre->text();

            if (ui->administrador->isChecked()) {
                tipo = "administrador";
            }
            if (ui->vendedor->isChecked()) {
                tipo = "vendedor";
            }
            if (ui->proveedor->isChecked()) {
                tipo = "proveedor";
            }

            /*
             * Cifra la contrasenia
             */
            Cifrado C;
            QString data=pass;
            pass = C.cifrar(data);

            QSqlQuery query;
            if (funcion == 1) {
                //Si funcion es = a 1 la accion es actualizar el usuario
                query.prepare("UPDATE empleados SET usuario='"+usuario+"', password='"+pass+"', nombre='"+nombre+"', tipo='"+tipo+"', foto='"+imagen+"' where usuario='"+usuario+"'");
            } else {
                //Si funcion es = a 0 la accion es crear el usuario
                query.prepare("INSERT INTO empleados (usuario, password, nombre, tipo, foto) VALUES ('"+usuario+"', '"+pass+"', '"+nombre+"', '"+tipo+"', '"+imagen+"' )");
            }

            if (query.exec()) {
                QMessageBox::information(this, tr("Notificación"), tr("El usuario se agrego correctamente!"));
                connection.dbClose();
                this->close();
            } else {
                ui->notify->setText("Ocurrio un error al guardar el usuario");
            }

        } else {
            ui->notify->setText("Debes ingresar un usuario");
        }
    }
    else if ( pass != "" || pass2 != "" ) {
        ui->notify->setText("Debes ingresar una contraseña");
    } else {
        ui->notify->setText("Error, las contraseñas no coinciden");
    }
}

void CreateUser::on_pushButton_clicked()
{
    /*
     * Cierra la ventana actual
    */
    this->close();
}

void CreateUser::on_subirFoto_clicked()
{
    /*
     * El usuario solo puede seleccionar archivos de tipo imagen
    */
    foto = QFileDialog::getOpenFileName(
                this, tr("Abrir Archivo"),
                "../imagenes/usuarios/",
                "Imagen (*.png *.jpg *.jpeg)"
                );
    /*
     * Obtiene la imagen seleccionada por el usuario
     * Copia la imagen a la carpeta: ../imagenes/usuarios/
    */
    QStringList queryfoto = foto.split("/");
    imagen = "../imagenes/usuarios/"+queryfoto.at(queryfoto.count()-1);
    QFile::copy(foto, imagen);

    /*
     * Muestra la imagen seleccionada
    */
    QPixmap fotoUpdate(imagen);
    ui->foto->setPixmap(fotoUpdate);
    ui->foto->setScaledContents(true);
}
