#ifndef DOT_H
#define DOT_H

#include <QDialog>

namespace Ui {
class dot;
}

class dot : public QDialog
{
    Q_OBJECT

public:
    explicit dot(QWidget *parent = 0);
    ~dot();

    void welcome(QString);

private:
    Ui::dot *ui;
    QString tipo;
};

#endif // DOT_H
