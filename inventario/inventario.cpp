#include "inventario.h"
#include "ui_inventario.h"

Inventario::Inventario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Inventario)
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

    /*
     * Inicializa la clase MainWindow en el objeto connection y
     * Valida la conexion a la BD
    */\

    DBConnect connection;

    if (!connection.dbOpen()) {
        QMessageBox::critical(this, tr("Error!"), tr("Ocurrio un error al cargar la Base de Datos"));
    }

    loadData();
    ui->inventario->setColumnWidth(0,25);
    ui->inventario->setColumnWidth(1,180);
    ui->inventario->setColumnWidth(2,120);
    ui->inventario->setColumnWidth(3,70);
    ui->inventario->setColumnWidth(4,70);
    ui->inventario->setColumnWidth(5,70);
    ui->inventario->setColumnWidth(6,110);
    ui->inventario->verticalHeader()->hide();
}

Inventario::~Inventario()
{
    delete ui;
}

void Inventario::loadData() {
    /*
     * Inicializa la clase MainWindow en el objeto connection y
     * Valida la conexion a la BD
    */\
    DBConnect connection;
    if (!connection.dbOpen()) {
        QMessageBox::critical(this, tr("Error!"), tr("Ocurrio un error al cargar la Base de Datos"));
    }

    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery* query = new QSqlQuery(connection.db);

    query->prepare("SELECT id, producto, codigo_barras, cantidad, cantidad_minima, costo_compra, costo_venta FROM almacen WHERE status = 1 ORDER BY cantidad ASC");

    if (query->exec()) {
        modal->setQuery(*query);
        modal->setHeaderData(0, Qt::Horizontal, tr("ID"));
        modal->setHeaderData(1, Qt::Horizontal, tr("Producto"));
        modal->setHeaderData(2, Qt::Horizontal, tr("Código de Barras"));
        modal->setHeaderData(3, Qt::Horizontal, tr("Stock"));
        modal->setHeaderData(4, Qt::Horizontal, tr("Inv. Min."));
        modal->setHeaderData(5, Qt::Horizontal, tr("Costo"));
        modal->setHeaderData(6, Qt::Horizontal, tr("Precio de Venta"));
        ui->inventario->setModel(modal);
        ui->inventarioLista->setModel(modal);
        connection.dbClose();
    }
    for (int i = 0; i <= modal->rowCount(); i++) {
        if (modal->record(i).value("cantidad").toInt() == modal->record(i).value("cantidad_minima").toInt()+2) {
            QMessageBox::information(this, tr("Advertencia!"), tr("Producto ")+modal->record(i).value("producto").toString()+tr(" bajo de Stock"));
        }
    }
}

void Inventario::on_pushButton_3_clicked()
{
    loadData();
}

void Inventario::on_inventario_ver_clicked()
{
    QString id = ui->inventarioLista->currentText();
    InventarioVer IV;
    IV.VerProducto(id);
    IV.setModal(true);
    IV.exec();
}

void Inventario::on_inventario_agregar_clicked()
{
    InventarioVer I;
    I.setModal(true);
    I.exec();
}

void Inventario::on_pushButton_clicked()
{
    QString search = ui->search->text();
    DBConnect connection;
    connection.dbOpen();

    /*
     * Formato para la tabla de resultados
    */

    ui->tableView->verticalHeader()->hide();
    ui->tableView->setColumnWidth(0,25);
    ui->tableView->setColumnWidth(1,100);
    ui->tableView->setColumnWidth(2,150);
    ui->tableView->setColumnWidth(3,70);
    ui->tableView->setColumnWidth(4,50);
    ui->tableView->setColumnWidth(5,100);

    QSqlQueryModel * modal = new QSqlQueryModel;

    QSqlQuery* query = new QSqlQuery(connection.db);
    query->prepare("SELECT id, producto, descripcion, codigo_barras, cantidad, costo_venta FROM almacen WHERE producto LIKE '%"+search+"%' OR descripcion LIKE '%"+search+"%' OR categoria LIKE '%"+search+"%' ORDER BY cantidad DESC");
    if (query->exec()) {

        modal->setQuery(*query);
        modal->setHeaderData(0, Qt::Horizontal, tr("ID"));
        modal->setHeaderData(1, Qt::Horizontal, tr("Producto"));
        modal->setHeaderData(2, Qt::Horizontal, tr("Descripcion"));
        modal->setHeaderData(3, Qt::Horizontal, tr("Código de Barras"));
        modal->setHeaderData(4, Qt::Horizontal, tr("Stock"));
        modal->setHeaderData(5, Qt::Horizontal, tr("Precio de Venta"));
        ui->tableView->setModel(modal);
        connection.dbClose();
    }
}

/*
 * Ambas funciones envia un valor seleccionado de la tabla
 * busca la imagen del producto correspondiente
 * y la muestra en la etiqueta imagen
*/

void Inventario::on_inventario_activated(const QModelIndex &index)
{
    QString data = ui->inventario->model()->data(index).toString();
    loadImage(data);
}

void Inventario::loadImage(QString data) {
    DBConnect connection;
    connection.dbOpen();

    QSqlQuery query;
    query.prepare("SELECT imagen FROM almacen WHERE codigo_barras = '"+data+"' OR producto = '"+data+"' OR id = '"+data+"'");

    if (query.exec()) {
        while (query.next()) {
            QString foto = query.value(0).toString();
            QPixmap img(foto);
            ui->imagen->setPixmap(img);
            ui->imagen->setScaledContents(true);
        }
    } else {
        QMessageBox::information(this, tr("Error"), tr("Ocurrio un error al ejecutar la consulta"));
    }

}

void Inventario::on_inventario_eliminar_clicked()
{
    /*
     * al presionar el boton eliminar el producto
     * abre una conexion a la BD
     */
    DBConnect connection;
    connection.dbOpen();

    /*
     * Crear el mensaje de confirmacion para eliminar el producto
    */
    QMessageBox msgBox;
    msgBox.setWindowTitle("Confirmación");
    msgBox.setText("¿Deseas eliminar el articulo?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int respuesta = msgBox.exec();
    switch (respuesta) {
      case QMessageBox::Yes: { // si confirma la eliminacion
          QSqlQuery query;
          //elimina el producto de la BD
          query.prepare("DELETE FROM almacen WHERE id = '"+ui->inventarioLista->currentText()+"'");
          if (query.exec()) {
              QMessageBox::information(this, tr("Notificación"), tr("El producto se elimino correctamente"));
              connection.dbClose();
          } else {
              QMessageBox::information(this, tr("Error"), tr("Ocurrio un error al eliminar el producto"));
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
