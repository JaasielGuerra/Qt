#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class Inventario;
}

class Inventario : public QDialog
{
    Q_OBJECT

public:
    explicit Inventario(QWidget *parent = 0);
    ~Inventario();
    void loadData();

private slots:
    void on_pushButton_3_clicked();

    void on_inventario_ver_clicked();

    void on_inventario_agregar_clicked();

    void on_pushButton_clicked();

    void on_inventario_activated(const QModelIndex &index);

    void loadImage(QString);

    void on_inventario_eliminar_clicked();

private:
    Ui::Inventario *ui;
};

#endif // INVENTARIO_H
