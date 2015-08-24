#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    /*
     * Carga la imagen para el background
    */
    QPixmap bkgnd("../imagenes/system/background2.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    ui->setupUi(this);
    QPixmap foto1("../imagenes/system/user.png");
    foto1 = foto1.scaled(ui->foto1->size(), Qt::IgnoreAspectRatio);
    ui->foto1->setPixmap(foto1);

    QPixmap foto2("../imagenes/system/user.png");
    foto2 = foto2.scaled(ui->foto1_2->size(), Qt::IgnoreAspectRatio);
    ui->foto1_2->setPixmap(foto2);

    QPixmap foto3("../imagenes/system/user.png");
    foto3 = foto3.scaled(ui->foto1_3->size(), Qt::IgnoreAspectRatio);
    ui->foto1_3->setPixmap(foto3);

    QPixmap foto4("../imagenes/system/user.png");
    foto4 = foto4.scaled(ui->foto1_4->size(), Qt::IgnoreAspectRatio);
    ui->foto1_4->setPixmap(foto4);
}

About::~About()
{
    delete ui;
}
