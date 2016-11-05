#include "bala.h"
#include <QTimer>
#include <qmath.h>
#include "../com.GeneticKingdom.UI/juego.h"

/**
 * Constructor de la clase bala
 * @param pJuego: instancia de juego hecha
 * @param bala: imagen de proyectil que debe adquirir
 * @param tipo: tipo de proyectil
 * @param pBorrable: boolean de borrable o no
 * @return Bala creada
 */
Bala::Bala(Juego &pJuego, QPixmap bala, int tipo, bool pBorrable) : juego(pJuego){
    borrable=pBorrable;
    this->tipo=tipo;
    setPixmap(bala);
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(moverBala()));
    timer->start(50);
}

/**
 * Destructor de la clase
 */
Bala::~Bala(){}

/**
 * Método para mover los proyectiles en una dirección en específico
 */
void Bala::moverBala() {
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

/**
 * Método para detectar colisiones contra enemigos
 */
void Bala::colisiones(){
    QList<QGraphicsItem *> list = collidingItems() ;
    foreach(QGraphicsItem * i , list)
    {
        Enemigo * item= dynamic_cast<Enemigo *>(i);
        if (item){
            //Condiciones para saber qué tanta vida bajarle a un enemigo dependiendo del tipo de proyectil
            if(tipo==1){
                if(item->getResA()>0 && item->getResA()<=10){
                    item->setVida(-4);
                }else if(item->getResA()>10 && item->getResA()<=20){
                    item->setVida(-3);
                }else if(item->getResA()>20 && item->getResA()<=30){
                    item->setVida(-2);
                }else{
                    item->setVida(-1);
                }
            }else if(tipo==2){
                if(item->getResB()>0 && item->getResB()<=10){
                    item->setVida(-4);
                }else if(item->getResB()>10 && item->getResB()<=20){
                    item->setVida(-3);
                }else if(item->getResB()>20 && item->getResB()<=30){
                    item->setVida(-2);
                }else{
                    item->setVida(-1);
                }
            }else{
                if(item->getResC()>0 && item->getResC()<=10){
                    item->setVida(-4);
                }else if(item->getResC()>10 && item->getResC()<=20){
                    item->setVida(-3);
                }else if(item->getResC()>20 && item->getResC()<=30){
                    item->setVida(-2);
                }else{
                    item->setVida(-1);
                }
            }

            //Bala borrable o no
            if(borrable)juego.borrarBala(this);

            //Si el enemigo le queda vida cero o menos después del método se elimina del juego
            if (item->getVida()<=0){
                juego.matar(item,1);
            }
            break;
        }
    }
}
