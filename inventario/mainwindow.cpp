#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
    this->setFixedSize(this->maximumSize());
    /*
     * Valida la conexion a la BD
    */\
    DBConnect Conn;

    if (!Conn.dbOpen()) {
        QMessageBox::critical(this, tr("Error!"), tr("Ocurrio un error al cargar la Base de Datos"));
    }

    /*
     * Muestra la imagen de login
    */
    QPixmap loginImagen("../imagenes/system/key.png");
    ui->imagen_login->setPixmap(loginImagen);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_submit_clicked()
{
    /*
     * Al ser presionado el boton "Iniciar Sesion" inicia esta funcion
    */
    if (intentos == 3) {
        QMessageBox::warning (this, tr("Error de Sesion"), tr("Has excedido el numero de intentos"));
        this->close();
    } else {
        /*
         * Declara las variables "user" y "password" donde y les asigna los valores ingresados por el usuario
        */
        QString password, user;
        user = ui->user->text();
        password = ui->password->text();

        /*
         * Cifra la contrasenia
        */
        Cifrado C;
        QString data=password;
        password = C.cifrar(data);

        DBConnect Conn;
        Conn.dbOpen();
        QSqlQuery query;
        query.prepare("SELECT * FROM empleados WHERE usuario='"+user+"' AND password = '"+password+"' ");

        /*
         * Busca dentro de la base de datos los datos ingresados y valida si son correctos
        */
        if (query.exec()) {
            int contador=0;
            while (query.next()) {
                contador++;
            }
            if (contador == 1) {
                Conn.dbClose(); //Cierra la conexion a la BD
                /*
                * Si el usuario y la contrasenia son correctos inicializa la clase
                * 'MenuMain' en el objeto 'I' y muestra la ventana de la aplicacion
                */
                this->hide();//oculta la ventana actual
                MenuMain *M;
                M = new MenuMain;
                M->WelcomeMsg(user);
                M->show();
                intentos = 0;
            } else {
                /*
                 * Si la contrasenia no es correcta muestra un mensaje de error
                */
                QMessageBox::warning (this, tr("Error de Sesion"), tr("Usuario o password incorrectos!"));
                intentos++;
            }
        }
    }
}
