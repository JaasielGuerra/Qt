#include "users.h"
#include "ui_users.h"
#include <QMessageBox>

Users::Users(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Users)
{
    ui->setupUi(this);
    /*
     * Carga la imagen para el background
    */
    QPixmap bkgnd("../imagenes/system/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    loadData();
}

Users::~Users()
{
    delete ui;
}

void Users::loadData() {
    /*
     * Inicializa la clase DBConnect en el objeto connection y
     * Valida la conexion a la BD
    */\
    DBConnect connection;
    if (!connection.dbOpen()) {
        QMessageBox::critical(this, tr("Error!"), tr("Ocurrio un error al cargar la Base de Datos"));
    }

    QSqlQueryModel * modal = new QSqlQueryModel;
    QSqlQuery* query = new QSqlQuery(connection.db);

    query->prepare("SELECT usuario, nombre, tipo FROM empleados WHERE tipo != 'developer'");

    if (query->exec()) {
        /*
         * Si la consulta es correcta
         * muestra en la tabla los usuarios
         * y en la lista desplegable
        */
        modal->setQuery(*query);
        ui->userslist->setModel(modal);
        ui->comboBox->setModel(modal);
        connection.dbClose(); //cierra la conexion a la BD
    }
}

void Users::on_pushButton_clicked()
{
    /*
     * si presiona el boton crear usuario
     * abre la clase CreateUser
    */
    CreateUser CU;
    CU.setModal(true);
    CU.exec();
}

void Users::on_pushButton_2_clicked()
{
    /*
     * si presiona el boton actualizar
     * ejecuta la funcion loadData
    */
    loadData();
}

void Users::on_eliminar_usuario_clicked()
{
    /*
     * al presionar el boton eliminar usuario
     * abre una conexion a la BD
     */
    DBConnect connection;
    connection.dbOpen();

    /*
     * crea la variable usuario y guarda en ella
     * el usuario seleccionado para eliminarlo
     */
    QString usuario = ui->comboBox->currentText();
    /*
     * Crear el mensaje de confirmacion para eliminar al usuario
     */
    QMessageBox msgBox;
    msgBox.setWindowTitle("Confirmación");
    msgBox.setText("Deseas eliminar el usuario: " + usuario);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int respuesta = msgBox.exec();
    switch (respuesta) {
      case QMessageBox::Yes: { // si confirma la eliminacion
          QSqlQuery query;
          //elimina el usuario de la BD
          query.prepare("DELETE FROM empleados WHERE usuario = '"+usuario+"'");
          if (query.exec()) {
              QMessageBox::information(this, tr("Notificación"), tr("El usuario se elimino correctamente"));
              connection.dbClose();
          }
          break;
        }
      case QMessageBox::Cancel:
          //Cancela la eliminacion
          break;
      default:
          //por defecto cancela la eliminacion
          break;
    }
}

void Users::on_actualizarUsuario_clicked()
{
    /*
     * al presionar el boton actualizar usuario
     * crea el objeto CU con la clase CreateUser
     *
     * Crea la variable user y guarda el nombre de usuario seleccionado
     *
     * Inicia la funcion updateUser y pasa la variable user
     */
    CreateUser CU;
    QString user = ui->comboBox->currentText();

    CU.updateUser(user);
    CU.setModal(true);
    CU.exec();
}
