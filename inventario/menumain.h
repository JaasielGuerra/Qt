#ifndef MENUMAIN_H
#define MENUMAIN_H

#include <QMainWindow>
#include "dbconnect.h"
#include "inventario.h"
#include "about.h"
#include <QPrinter>
#include <QPainter>

namespace Ui {
class MenuMain;
}

class MenuMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuMain(QWidget *parent = 0);
    ~MenuMain();

    void WelcomeMsg(QString);

private slots:
    void on_button_inventario_clicked();
    void on_button_usuarios_clicked();

    void on_actionCerrar_Sesi_n_triggered();

    void on_actionSalir_triggered();

    bool checkLevelUser();

    void on_actionTodos_los_productos_triggered();

    void on_actionCrear_Producto_triggered();

    void on_actionCrear_Usuario_triggered();

    void on_actionUsuarios_triggered();

    void on_cargar_clicked();

    void getfecha();

    void on_pushButton_clicked();

    void on_entrada_guardar_clicked();

    void on_salida_guardar_clicked();

    void on_pushButton_2_clicked();

    void on_actionAcerca_de_triggered();

    void on_button_ventas_clicked();

    void on_ventas_2_activated(const QModelIndex &index);

    void on_pushButton_3_clicked();

    int generaReporte();

private:
    Ui::MenuMain *ui;
    //Datos del vendedor
    QString id, usuario, fecha, nombre;

    /*
     * Datos de productos en seccion de Ventas
     */
    QString venta_codigobarras, venta_producto, venta_fecha, venta_vendedor;
    int venta_cantidad=0, rows = 0, venta_stock=0, venta_check=0, venta_id=0;
    float venta_costo=0, venta_importe=0, total_bruto=0, total_iva=0, total_=0;

protected:
    void  closeEvent(QCloseEvent*);
};

#endif // MENUMAIN_H
