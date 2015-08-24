#include "dot.h"
#include "ui_dot.h"
#include <QMovie>

dot::dot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dot)
{
    ui->setupUi(this);
}

dot::~dot()
{
    delete ui;
}

void dot::welcome(QString gif) {
    tipo = gif;

    QMovie *movie = new QMovie("../imagenes/system/"+tipo+".gif");
    ui->label->setMovie(movie);
    movie->start();
}
