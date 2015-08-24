#ifndef INVENTARIOVER_H
#define INVENTARIOVER_H

#include <QDialog>
#include <mainwindow.h>
#include <QPixmap>

namespace Ui {
class InventarioVer;
}

class InventarioVer : public QDialog
{
    Q_OBJECT

public:
    explicit InventarioVer(QWidget *parent = 0);
    ~InventarioVer();
    void VerProducto(QString);

private slots:
    void on_cancel_prod_clicked();

    void on_update_prod_clicked();

    void on_pushButton_clicked();

private:
    Ui::InventarioVer *ui;
    QString imagen="../imagenes/productos/default.png";
};

#endif // INVENTARIOVER_H
