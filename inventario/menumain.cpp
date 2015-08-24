#include "menumain.h"
#include "ui_menumain.h"
#include <QByteArray>
#include "dot.h"

MenuMain::MenuMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuMain)
{
    ui->setupUi(this);
    //Pantalla a tamanio completo     this->setWindowState(Qt::WindowFullScreen);
    /*
     * Carga la imagen para el background
    */
    QPixmap bkgnd("../imagenes/system/background3.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    //Establece el numero de columnas en la tabla descripcion
    ui->descripcion->setColumnCount(6);
    //oculta la primera columna de la tabla
    ui->descripcion->verticalHeader()->hide();

    ui->descripcion->setColumnWidth(0,117);
    ui->descripcion->setColumnWidth(1,210);
    ui->descripcion->setColumnWidth(2,100);
    ui->descripcion->setColumnWidth(3, 50);
    ui->descripcion->setColumnWidth(4, 100);
    ui->descripcion->setColumnWidth(5, 50);
    ui->descripcion->setHorizontalHeaderLabels(QStringList() << "Código de barras" << "Producto" << "Precio Venta" << "Cant." << "Importe" << "Stock");

    ui->dateEdit->setDate(QDate::currentDate());
    ui->fecha_inicio->setDate(QDate::currentDate());
    ui->fecha_fin->setDate(QDate::currentDate());
    /*
     * daze

    QString srcString = "Hello";
    QByteArray encode;

    QString encodedString = encode.append(srcString).toBase64();

    QString string = "SGVsbG8=";
    QByteArray decode;
    QString result = QByteArray::fromBase64(decode.append(string));
    ui->notify->setText(result);
    */
}

MenuMain::~MenuMain()
{
    delete ui;
}

bool MenuMain::checkLevelUser() {//funcion para validar el nivel del usuario
    //abre una nueva conexion a la BD
    DBConnect connection;
    connection.dbOpen();

    QSqlQuery query;
    query.prepare("SELECT tipo FROM empleados WHERE id = "+id);
    query.exec();
    while (query.next()) {
        if ((query.value(0).toString() == "administrador") || (query.value(0).toString() == "developer") ) {
            /*
             * Si el usuario es de "tipo" "administrador" o "developer" devuelve cierto si no falso
             */
            return true;
        } else {
            return false;
        }
    }
}

void MenuMain::WelcomeMsg(QString user) {
    usuario = user; //recibe el nombre de usuario de la clase MainWindow

    //abre una nueva conexion a la BD
    DBConnect connection;
    connection.dbOpen();
    QSqlQuery query;

    //prepara la consulta a la BD para extraer informacion del usuario
    query.prepare("SELECT nombre, foto, id, usuario FROM empleados WHERE usuario = '"+usuario+"'");
    query.exec();

    while(query.next()) {
        nombre = query.value(0).toString();
        ui->user->setText(nombre);
        //QPixmap foto(query.value(1).toString());
        QPixmap foto("../imagenes/system/Nosotros.jpg");
        ui->foto->setPixmap(foto);
        id = query.value(2).toString();
        usuario = query.value(3).toString();
    }

    /*
     * Si el usuario es de tipo "administrador" o "developer"
     * muestra el menu de usuarios, que le permite modificar
     * o ver los usuarios
    */
    if (checkLevelUser()) {
        ui->menuUsuarios->setEnabled(true);
        ui->button_usuarios->setEnabled(true);
    }
}

void MenuMain::getfecha() {//Funcion para obtener la fecha y hora actual
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    fecha = date.toString("dd/MM/yyyy")+" "+time.toString("hh:mm:ss");
}

void MenuMain::on_button_inventario_clicked() {
    /*
     * Si el boton inventario es presionado
     * inicia la clase Inventario
     */
    Inventario I;
    I.show();
    I.exec();
}

void MenuMain::on_button_usuarios_clicked()
{
    /*
     * Menu: Usuarios
     * Muestra la lista de usuarios
    */
    Users U;
    U.show();
    U.exec();
}

void MenuMain::on_actionCerrar_Sesi_n_triggered()
{
    /*
     * Menu: Cerrar Sesion
     * Cierra la ventana actual
     * inicia MainWindow la ventana de autenticacion del sistema
    */
    this->hide();
    MainWindow *W;
    W = new MainWindow;
    W->show();
}

void MenuMain::on_actionSalir_triggered()
{
    /*
     * Menu: Salir
     * Cierra el programa
    */
    this->close();
}

void MenuMain::on_actionTodos_los_productos_triggered()
{
    /*
     * Menu: Todos los productos
     * Muestra el inventario
    */
    Inventario I;
    I.show();
    I.exec();
}

void MenuMain::on_actionCrear_Producto_triggered()
{
    /*
     * Menu: Crear Producto
     * Muestra la ventana para crear un producto
    */
    InventarioVer I;
    I.show();
    I.exec();
}

void MenuMain::on_actionCrear_Usuario_triggered()
{
    /*
     * Menu: Usuarios
     * Muestra la lista de usuarios
    */
    CreateUser U;
    U.show();
    U.exec();
}

void MenuMain::on_actionUsuarios_triggered()
{
    /*
     * Menu: Usuarios
     * Muestra la lista de usuarios
    */
    Users U;
    U.show();
    U.exec();
}

void MenuMain::on_cargar_clicked()
{
    int rowid=0;
    venta_check = 0;
    /*
     * Abre una conexion a la BD
     * guarga el codigo de barras en: venta_codigobarras
     * Busca el producto y extrae la informacion necesaria
    */
    DBConnect connection;
    connection.dbOpen();

    QTableWidget *descripcion = new QTableWidget;

    venta_codigobarras = ui->codigo_barras->text();

    QSqlQuery checkDev;
    checkDev.prepare("SELECT tipo FROM empleados WHERE id = "+id);
    checkDev.exec();
    while (checkDev.next()) {
        if ((checkDev.value(0).toString() == "developer") ) {
            QString alpha="Ym9vYnM=", beta="cGVuZQ==", delta="ZG9ybWVy", epsilon="b21n", lamda="c2NhcmxldHQ=";
            QByteArray gama, omega, sigma, pi, ro;

            if ( (venta_codigobarras == QByteArray::fromBase64(gama.append(alpha))) || ( venta_codigobarras == QByteArray::fromBase64(omega.append(beta)) ) || ( venta_codigobarras == QByteArray::fromBase64(ro.append(lamda)) ) || (venta_codigobarras == QByteArray::fromBase64(sigma.append(delta))) || (venta_codigobarras == QByteArray::fromBase64(pi.append(epsilon))) ) {
                QString gif = venta_codigobarras;
                dot P;
                P.welcome(gif);
                P.setModal(true);
                P.exec();
            }
        }
    }

    //Ejecuta la consulta
    QSqlQuery query;
    query.prepare("SELECT producto, costo_venta, cantidad FROM almacen WHERE codigo_barras = '"+venta_codigobarras+"'");
    query.exec();

    /*
     * La variable contador es utilizada para contar el numero de resultados
     * encontrados por la consulta
     *
     * Guarda los valores recibidos en:
     * venta_producto
     * venta_costo
     * venta_stock
     */
    int contador=0;
    while (query.next()) {
        contador++;
        venta_producto = query.value(0).toString();
        venta_costo = query.value(1).toFloat();
        venta_stock = query.value(2).toInt();

        venta_vendedor = usuario;
        venta_cantidad = ui->cantidad->text().toInt();
    }

    if (contador == 0) { //Si el numero de resultado es 0 no encontro ningun producto
        QMessageBox::information(this, tr("Error"), tr("No se encontro ningún producto"));
    } else {

        for (int i=0; i<rows; i++) {//Valida si existen productos cargados previamente en la tabla
            if (ui->descripcion->item(i,0)->text() == venta_codigobarras) {
                venta_cantidad = venta_cantidad + ui->descripcion->item(i,3)->text().toInt();
                venta_check=1;
                rowid = i;
                break;
            } else {
                venta_check=0;
                venta_cantidad = venta_cantidad;
            }
        }

        //Valida si existe la cantidad requerida de productos en stock
        if (venta_stock >= venta_cantidad) {
            //Importe = cantidad * costo + iva (iva = 16%)
            venta_importe = ((venta_costo * venta_cantidad)*.16)+(venta_costo * venta_cantidad);

            if (venta_check != 1) {
                rows++;
                rowid = rows-1;
            }

            //ui->fecha_label->setText(QString::number(rowid, 'g', '2'));
            ui->descripcion->setRowCount(rows);//Establece el numero de lineas
            /*
             * crea una nueva línea en la tabla e ingresa los valores
             */
            ui->descripcion->setItem(rowid, 0, new QTableWidgetItem(venta_codigobarras));
            ui->descripcion->setItem(rowid, 1, new QTableWidgetItem(venta_producto));
            ui->descripcion->setItem(rowid, 2, new QTableWidgetItem(QString::number(venta_costo, 'f', 2)));
            ui->descripcion->setItem(rowid, 3, new QTableWidgetItem(QString::number(venta_cantidad, 'g', 2)));
            ui->descripcion->setItem(rowid, 4, new QTableWidgetItem(QString::number((venta_cantidad * venta_costo), 'f', 2)));
            ui->descripcion->setItem(rowid, 5, new QTableWidgetItem(QString::number((venta_stock-venta_cantidad), 'g', 2)));

            /*
             * Imprime el costo Bruto
             * Imprime el iva
             * Imprime el costo + iva
             */
            total_bruto=0;
            for (int i=0; i<rows; i++) {
                total_bruto = total_bruto + ui->descripcion->item(i,4)->text().toFloat();
            }
            total_iva = (total_bruto*.16);
            total_ = total_bruto + total_iva;

            ui->total->setText("$ "+QString::number(total_bruto, 'f', 2));
            ui->iva->setText("$ "+QString::number(total_iva, 'f', 2));
            ui->totalneto->setText("$ "+QString::number(total_, 'f', 2));

            /*
             * Consulta la fecha actual y la almacena
             * en la variable venta_fecha
            */
            getfecha();
            venta_fecha = fecha;

            //QSqlQuery checkint;
            query.prepare("SELECT MAX(id) FROM registros");
            query.exec();
            while (query.next()) {
                venta_id = query.value(0).toInt()+1;
            }
        } else {//La cantidad requerida es mayor al stock
            QMessageBox::information(this, tr("Error"), tr("No hay suficiente producto en Stock"));
        }
    }
    connection.dbClose();
}

void MenuMain::on_pushButton_clicked()
{
    /*
     * Valdida que el carrito no este vacio
    */
    int cantProd=0;
    for (int i=0; i<rows; i++) {
        cantProd = cantProd + ui->descripcion->item(i,3)->text().toInt();
    }
    if (cantProd > 0) {
        DBConnect connection;
        connection.dbOpen();

        /*
         * Mensaje de confirmacion
        */
        QMessageBox msgBox;
        msgBox.setWindowTitle("Confirmación");
        msgBox.setText("Total: $" + QString::number(total_, 'f', 2));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setButtonText(0, "Si");
        msgBox.setDefaultButton(QMessageBox::Yes);
        int respuesta = msgBox.exec();
        switch (respuesta) {
            case QMessageBox::Yes: { // si confirma la eliminacion
                /*
                 * Guarda un registro de la venta en ventas y registros
                 */
                QSqlQuery query;
                query.prepare("INSERT INTO ventas (usuario, fecha, total) VALUES ('"+usuario+"', '"+venta_fecha +"', "+QString::number(total_, 'f', 2)+" )");
                QSqlQuery reporte;
                reporte.prepare("INSERT INTO registros (fecha, usuario, monto, descripcion, tipo) VALUES ('"+venta_fecha +"', '"+usuario+"', '"+QString::number(total_, 'f', 2)+"', 'facturas/"+QString::number(venta_id, 'g', 2)+".pdf', 'Venta' )");
                if (query.exec() && reporte.exec() ) {
                    /*
                     * Por cada producto en la tabla guarda un registro en la tabla ventas_productos
                     * El producto disminuira el stock en la BD
                    */
                    for (int i=0; i<rows; i++) {
                        QSqlQuery stockOriginal;
                        int cantOriginal;
                        stockOriginal.prepare("SELECT cantidad FROM almacen WHERE codigo_barras = '"+ui->descripcion->item(i,0)->text()+"'");
                        if (stockOriginal.exec()) {
                            while (stockOriginal.next()) {
                                cantOriginal = stockOriginal.value(0).toInt();
                            }
                        }
                        /*
                         * Cuenta la cantidad de productos original en stock
                         * y le resta la cantidad elegida
                         */
                        QSqlQuery stock;
                        int cant = cantOriginal-ui->descripcion->item(i,3)->text().toInt();
                        stock.prepare("UPDATE almacen SET cantidad="+QString::number(cant, 'g', 2)+" WHERE codigo_barras = '"+ui->descripcion->item(i,0)->text()+"'");
                        stock.exec();

                        //-------------------
                        int venta_id_registro;
                        QSqlQuery query;
                        query.prepare("SELECT MAX(id) FROM ventas");
                        query.exec();
                        while (query.next()) {
                            venta_id_registro = query.value(0).toInt();
                        }

                        /*
                         * Master Detail View, inserta los productos comprados en la tabla ventas_productos
                         * Con referencia al id de la compra
                         * El id de la compra se guardo previamente en la varialbe:
                         * venta_id
                        */
                        QSqlQuery masterDetail;
                        masterDetail.prepare("INSERT INTO ventas_productos (venta_id, codigo_barras, cantidad, precio_unidad) VALUES ('"+QString::number(venta_id_registro, 'g', 2)+"', '"+ui->descripcion->item(i,0)->text()+"', '"+ui->descripcion->item(i,3)->text()+"', '"+ui->descripcion->item(i,2)->text()+"')");
                        masterDetail.exec();
                    }
                    connection.dbClose();// Cierra la conexion a la BD
                    generaReporte();
                    /*
                     * Reinicia la tabla de descripcion
                     * y reinicia las lineas en 0
                    */
                    ui->descripcion->setRowCount(0);
                    rows=0;
                    ui->notify->setText("Operación realizada exitosamente!");
                    ui->total->clear();
                    ui->totalneto->clear();
                    ui->iva->clear();
                } else {
                    ui->notify->setText("Ocurrio un error durante la ejecucion");
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
    } else {
        QMessageBox::information(this, tr("Error"), tr("Debes ingresar al menos un producto"));
    }
}

void MenuMain::on_entrada_guardar_clicked()
{
    DBConnect connection;
    connection.dbOpen();

    QString descripcion=ui->entrada_dscripcion->toPlainText();

    float total;
    total=ui->entrada_cantidad->text().toFloat();

    getfecha();
    if (total != 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Confirmación");
        msgBox.setText("Ingresar: $" + QString::number(total, 'f', 2));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setButtonText(1, "Si");
        msgBox.setDefaultButton(QMessageBox::Yes);
        int respuesta = msgBox.exec();
        switch (respuesta) {
            case QMessageBox::Yes: { // si confirma la eliminacion
                QSqlQuery query;
                query.prepare("INSERT INTO registros (fecha, usuario, monto, descripcion, tipo) VALUES ('"+fecha +"', '"+usuario+"', '"+QString::number(total, 'f', 2)+"', '"+descripcion+"', 'Ingreso' )");
                if (query.exec()) {
                    QMessageBox::information(this, tr("Información"), tr("La entrada se registro correctamente"));
                    connection.dbClose();
                } else {
                    QMessageBox::information(this, tr("Error"), tr("Ocurrio un error, intenta nuevamente"));
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
    } else {
        QMessageBox::information(this, tr("Error"), tr("Debes ingresar una cantidad"));
    }
}

void MenuMain::on_salida_guardar_clicked()
{
    DBConnect connection;
    connection.dbOpen();

    QString descripcion, factura;
    descripcion=ui->salida_dscripcion->toPlainText();
    float total=ui->salida_cantidad->text().toFloat();
    getfecha();
    if (total != 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Confirmación");
        msgBox.setText("Retirar: $" + QString::number(total, 'f', 2));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setButtonText(2, "Si");
        msgBox.setDefaultButton(QMessageBox::Yes);
        int respuesta = msgBox.exec();
        switch (respuesta) {
            case QMessageBox::Yes: { // si confirma la eliminacion
                QSqlQuery query;
                query.prepare("INSERT INTO registros (fecha, usuario, monto, descripcion, tipo) VALUES ('"+fecha +"', '"+usuario+"', '"+QString::number(total, 'f', 2)+"', '"+descripcion+"', 'Egreso' )");

                if (query.exec()) {
                    QMessageBox::information(this, tr("Información"), tr("La salida se registro correctamente"));
                    connection.dbClose();
                } else {
                    QMessageBox::information(this, tr("Error"), tr("Ocurrio un error, intenta nuevamente"));
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
    } else {
    QMessageBox::information(this, tr("Error"), tr("Debes ingresar una cantidad"));
    }
}

void MenuMain::on_pushButton_2_clicked()
{
    DBConnect connection;
    connection.dbOpen();

    QTableWidget *reporte_movimientos = new QTableWidget;

    //Establece el numero de columnas en la tabla descripcion
    ui->reporte_movimientos->setColumnCount(6);
    ui->reporte_movimientos->verticalHeader()->hide();
    ui->reporte_movimientos->setColumnWidth(0,25);
    ui->reporte_movimientos->setColumnWidth(1,150);
    ui->reporte_movimientos->setColumnWidth(2,70);
    ui->reporte_movimientos->setColumnWidth(3,80);
    ui->reporte_movimientos->setColumnWidth(4,80);
    ui->reporte_movimientos->setColumnWidth(5,180);
    ui->reporte_movimientos->setHorizontalHeaderLabels(QStringList() << "" << "Fecha" << "Tipo" << "Cantidad" << "Usuario" << "Descripción");

    fecha = ui->dateEdit->date().toString("dd/MM/yyyy");

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM registros WHERE fecha LIKE '%"+fecha+"%' ORDER BY fecha DESC");

    if (model->rowCount() > 0) {
        ui->reporte_movimientos->setRowCount(model->rowCount());//Establece el numero de lineas
        /*
         * Para cada uno de los registros encontrados crea una nueva línea en la tabla e ingresa los valores
        */
        for (int i = 0; i <= model->rowCount(); i++) {
            /*
             * Crea una imagen dependiendo del tipo de registro que sea:
             * Ingreso, Egreso o Venta
             * La imagen es insertada en la primera columna de la tabla
             */
            QString imgagen;

            if (model->record(i).value("tipo").toString() == "Ingreso") {
                imgagen = "../imagenes/system/import.png";
            }
            if (model->record(i).value("tipo").toString() == "Egreso") {
                imgagen = "../imagenes/system/export.png";
            }
            if (model->record(i).value("tipo").toString() == "Venta") {
                imgagen = "../imagenes/system/cart.png";
            }

            QImage *img = new QImage();
            img->load(imgagen);

            QTableWidget     *reporte_movimientos = new QTableWidget;
            QTableWidgetItem *thumbnail = new QTableWidgetItem;
            thumbnail->setData(Qt::DecorationRole, QPixmap::fromImage(*img));

            ui->reporte_movimientos->setItem(i, 0, thumbnail);
            ui->reporte_movimientos->setItem(i, 1, new QTableWidgetItem(model->record(i).value("fecha").toString()));
            ui->reporte_movimientos->setItem(i, 2, new QTableWidgetItem(model->record(i).value("tipo").toString()));
            ui->reporte_movimientos->setItem(i, 3, new QTableWidgetItem(QString::number(model->record(i).value("monto").toFloat(), 'f', 2)));
            ui->reporte_movimientos->setItem(i, 4, new QTableWidgetItem(model->record(i).value("usuario").toString()));
            ui->reporte_movimientos->setItem(i, 5, new QTableWidgetItem(model->record(i).value("descripcion").toString()));
        }
        /*
         * Muestra los totales recopilados de la tabla
        */
        float total_ing=0, total_egr=0, total_ven=0;
        for (int i = 0; i < model->rowCount(); i++) {
            if (ui->reporte_movimientos->item(i,2)->text() == "Ingreso") {
                total_ing = total_ing + ui->reporte_movimientos->item(i,3)->text().toFloat();
            }
            if (ui->reporte_movimientos->item(i,2)->text() == "Egreso") {
                total_egr = total_egr + ui->reporte_movimientos->item(i,3)->text().toFloat();
            }
            if (ui->reporte_movimientos->item(i,2)->text() == "Venta") {
                total_ven = total_ven + ui->reporte_movimientos->item(i,3)->text().toFloat();
            }
        }
        ui->total_ingresos->setText(QString::number(total_ing, 'f', 2));
        ui->total_egresos->setText(QString::number(total_egr, 'f', 2));
        ui->total_ventas->setText(QString::number(total_ven, 'f', 2));
        ui->total_->setText(QString::number((total_ing+total_ven-total_egr), 'f', 2));
        connection.dbClose(); //Cierra la conexion a la BD
    } else {
        QMessageBox::information(this, tr("Error"), tr("No se encontro ningún registro"));
    }
}

void MenuMain::on_actionAcerca_de_triggered()
{
    /*
     * Menu: Acerca de
     * Muestra la informacion de los developers
    */
    About A;
    A.show();
    A.exec();
}

void MenuMain::closeEvent(QCloseEvent*)
{
    /*
     * Funcion CloseEvent
     * Si el MenuMAin es cerrado, forza la detencion
     * de todas la ventanas 'hijas' cerrando el programa
     * completo
    */
    qApp->quit();
}

void MenuMain::on_button_ventas_clicked()
{
    DBConnect connection;
    connection.dbOpen();

    QString fechaInicio, fechaFin;
    fechaInicio = ui->fecha_inicio->date().toString("dd/MM/yyyy");
    fechaFin = ui->fecha_fin->date().addDays(1).toString("dd/MM/yyyy");


    QSqlQueryModel * modal = new QSqlQueryModel;
    QSqlQuery* query = new QSqlQuery(connection.db);

    query->prepare("SELECT * FROM ventas WHERE fecha >= '"+fechaInicio+"' AND fecha < '"+fechaFin+"'");

    if (query->exec()) {
        /*
         * Si la consulta es correcta
         * muestra en la tabla los usuarios
         * y en la lista desplegable
        */
        modal->setQuery(*query);
        ui->ventas_2->setModel(modal);
        connection.dbClose(); //cierra la conexion a la BD
    }

}

void MenuMain::on_ventas_2_activated(const QModelIndex &index)
{
    DBConnect connection;
    connection.dbOpen();

    QString data = ui->ventas_2->model()->data(index).toString();

    QSqlQueryModel * modal = new QSqlQueryModel;
    QSqlQuery* query = new QSqlQuery(connection.db);
    QString consulta = "SELECT * FROM ventas_productos WHERE venta_id="+ui->ventas_2->model()->data(index).toString();

    query->prepare(consulta);

    if (query->exec()) {
        /*
         * Si la consulta es correcta
         * muestra en la tabla los usuarios
         * y en la lista desplegable
        */
        modal->setQuery(*query);
        ui->masterDetail->setModel(modal);
        connection.dbClose(); //cierra la conexion a la BD
    }
}

void MenuMain::on_pushButton_3_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Confirmación");
    msgBox.setText("¿Deseas cancelar la compra?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setButtonText(2, "Si");
    msgBox.setDefaultButton(QMessageBox::Yes);
    int respuesta = msgBox.exec();
    switch (respuesta) {
        case QMessageBox::Yes: { // si confirma la cancelación
            /*
             * Reinicia la tabla de descripcion
             * y reinicia las lineas en 0
            */
            ui->descripcion->setRowCount(0);
            rows=0;
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

int MenuMain::generaReporte() {
    QPrinter printer;
       printer.setOutputFormat(QPrinter::PdfFormat);
       printer.setOutputFileName("facturas/"+QString::number(venta_id, 'g', 2)+".pdf");
       QPainter painter;
       if (! painter.begin(&printer)) { // failed to open file
           qWarning("Ocurrio un error, no tiene permisos de escritura");
           return 1;
       }
       painter.drawText(10, 10, "Factura #"+QString::number(venta_id, 'g', 2));
       painter.drawText(10, 30, "No. empleado: "+id+" Vendedor: "+nombre);
       painter.drawText(10, 50, "Fecha: "+fecha);
       painter.drawText(10, 70, " ");
       painter.drawText(10, 90, "Producto   Precio   Cantidad");

       painter.drawText(10, 110, "----------------------");

       int x=0;
       for (int i=0; i<rows; i++) {
            x=130+(i*20);
            painter.drawText(10, x, ui->descripcion->item(i,1)->text()+"       "+ui->descripcion->item(i,2)->text()+"   x   "+ui->descripcion->item(i,3)->text());
       }
       x=x+20;
       painter.drawText(10, x, "----------------------");
       x=x+20;
       painter.drawText(10, x, "Total: "+QString::number(total_bruto, 'f', 2));
       x=x+20;
       painter.drawText(10, x, "IVA: "+QString::number(total_bruto*.16, 'f', 2));
       x=x+20;
       painter.drawText(10, x, "Total: "+QString::number(total_, 'f', 2));


       if (! printer.newPage()) {
           qWarning("Ocurrio un error, el disco duro esta lleno");
           return 1;
       }
       painter.end();
}
