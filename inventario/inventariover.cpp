#include "inventariover.h"
#include "ui_inventariover.h"
#include <QFileDialog>

InventarioVer::InventarioVer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InventarioVer)
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


    QPixmap img(imagen);
    ui->foto->setPixmap(img);
    ui->foto->setScaledContents(true);
}

InventarioVer::~InventarioVer()
{
    delete ui;
}

void InventarioVer::VerProducto(QString id) {
    /*
     * crea la variable prod_id y le asigna el valor de id
     * abre una conexion a la BD
     */
    QString prod_id = id;
    DBConnect connection;
    connection.dbOpen();
    QSqlQuery query;
    query.prepare("SELECT * FROM almacen WHERE id = '"+prod_id+"'");
    query.exec();

    while(query.next()) {
        ui->label_id->setText(query.value(0).toString());
        ui->producto->setText(query.value(1).toString());
        ui->codigoBarras->setText(query.value(2).toString());
        ui->cantidad->setText(query.value(3).toString());
        ui->descripcion->setText(query.value(4).toString());
        ui->categoria->setText(query.value(5).toString());
        ui->precioFabrica->setText(query.value(6).toString());
        ui->precioPublico->setText(query.value(7).toString());
        //ui->status->setText(query.value(8).toString());

        imagen = query.value(9).toString();
        QPixmap img(imagen);
        ui->foto->setPixmap(img);
        ui->foto->setScaledContents(true);
        ui->cantidad_minima->setText(query.value(10).toString());
    }

}

void InventarioVer::on_cancel_prod_clicked()
{
    /*
     * Cierra la ventana actual
    */
    this->close();
}

void InventarioVer::on_update_prod_clicked()
{
    DBConnect connection;
    connection.dbOpen();

    QString producto=ui->producto->text(), codigo_barras=ui->codigoBarras->text(), descripcion=ui->descripcion->toPlainText().toUtf8() , categoria=ui->categoria->text();
    int cantidad=ui->cantidad->text().toInt(), /*status=ui->status->text().toInt(),*/ cantidad_minima=ui->cantidad_minima->text().toInt();
    float costo_compra=ui->precioFabrica->text().toFloat(), costo_venta=ui->precioPublico->text().toFloat();

    if (producto != "") {
        QSqlQuery query;
        QString consulta;
        if (ui->label_id->text() != "") {
            //Si el id existe la accion es actualizar el articulo
            consulta = "UPDATE almacen SET producto = '"+producto+"', codigo_barras='"+codigo_barras+"', cantidad='"+QString::number(cantidad, 'g', 2)+"', descripcion='"+descripcion+"', categoria='"+categoria+"', costo_compra='"+QString::number(costo_compra, 'f', 2)+"', costo_venta='"+QString::number(costo_venta, 'f', 2)+"', imagen='"+imagen+"', cantidad_minima='"+QString::number(cantidad_minima, 'g', 2)+"'  WHERE id = '"+ui->label_id->text()+"'";
        } else {
            //Si el id no existe la accion es crear el articulo
            consulta = "INSERT INTO almacen (producto, codigo_barras, cantidad, descripcion, categoria, costo_compra, costo_venta, cantidad_minima) VALUES ( '"+producto+"', '"+codigo_barras+"', "+QString::number(cantidad, 'g', 2)+", '"+descripcion+"', '"+categoria+"', "+QString::number(costo_compra, 'f', 2)+", '"+QString::number(costo_venta, 'f', 2)+"', "+QString::number(cantidad_minima, 'g', 2)+")";
        }

        query.prepare(consulta);

        if (query.exec()) {
            QMessageBox::information(this, tr("Notificación"), tr("El articulo se agrego correctamente!"));
            connection.dbClose();
            this->close();
        } else {
            QMessageBox::information(this, tr("Error"), tr("Ocurrio un error al ejecutar la consulta No. 2"));
        }
    } else {
        QMessageBox::information(this, tr("Error"), tr("Ingresa un articulo"));
    }
}

void InventarioVer::on_pushButton_clicked()
{
    /*
     * El usuario solo puede seleccionar archivos de tipo imagen
    */
    QString foto;
    foto = QFileDialog::getOpenFileName(
                this, tr("Abrir Archivo"),
                "../imagenes/productos/",
                "Imagen (*.png *.jpg *.jpeg)"
                );
    /*
     * Obtiene la imagen seleccionada por el usuario
     * Copia la imagen a la carpeta: ../imagenes/productos/
    */
    QStringList queryfoto = foto.split("/");
    imagen = "../imagenes/productos/"+queryfoto.at(queryfoto.count()-1);
    QFile::copy(foto, imagen);

    /*
     * Muestra la imagen seleccionada
    */
    QPixmap fotoUpdate(imagen);
    ui->foto->setPixmap(fotoUpdate);
    ui->foto->setScaledContents(true);
}
