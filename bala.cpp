#include "bala.h"
#include <QGraphicsItem>
#include <QTimer>
#include <qmath.h>
#include "juego.h"
#include <stdlib.h>

Bala::Bala(Juego& pJuego,QGraphicsItem *parent): juego(pJuego)
{
    setPixmap(QPixmap(":/Imagenes/bullet1"));

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(moverBala()));
    timer->start(50);
}

Bala::~Bala(){}

void Bala::moverBala()
{
    if(this->x()>1280||this->x()<0||this->y()>680||this->y()<0){
        juego.borrarBala(this);
    }
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
            juego.borrarBala(this);
            if (item->vida<=0){juego.matar(item);
            }
            break;
        }
    }
}
