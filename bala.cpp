#include "bala.h"
#include <QGraphicsItem>
#include <QTimer>
#include <qmath.h>
#include "juego.h"

Bala::Bala(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/Imagenes/bullet1"));

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(moverBala()));
    timer->start(50);
}

void Bala::moverBala()
{
    int Step=30;
    double angulo=rotation();

    double dy = Step*qSin(qDegreesToRadians(angulo));
    double dx = Step*qCos(qDegreesToRadians(angulo));

    setPos(x()+dx,y()+dy);
    colisiones();
}
void Bala::colisiones(){
    QList<QGraphicsItem *> list = collidingItems() ;
    foreach(QGraphicsItem * i , list)
    {
        Enemigo * item= dynamic_cast<Enemigo *>(i);
        if (item){
            item->vida-=1;
            scene()->removeItem(this);
        }
    }
}
