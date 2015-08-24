#include "mainwindow.h"
#include <QApplication>
#include <QTimer>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Crea el objeto inicio con la clase QSplashScreen
    QSplashScreen *inicio = new QSplashScreen;
    /*
     * Antes de iniciar el programa muestra la imagen de la empresa (slash)
     * durante 4 segundos, despues inicia el programa
     * y muestra la pantalla de acceso
     */
    inicio->setPixmap(QPixmap("../imagenes/system/slash.png"));
    inicio->show();

    QTimer::singleShot(4000, inicio, SLOT(close()));

    MainWindow w;
    QTimer::singleShot(4000, &w, SLOT(show()));
    //w.show();

    return a.exec();
}
