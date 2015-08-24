#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "adduser.h"
#include "createuser.h"
#include "users.h"
#include "inventariover.h"
#include "menumain.h"
#include "cifrado.h"

#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_submit_clicked();

private:
    Ui::MainWindow *ui;
    int intentos=1;
};

#endif // MAINWINDOW_H
