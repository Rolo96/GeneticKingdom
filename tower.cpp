#include "tower.h"
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include <QTimer>
#include <QDebug>
#include "bala.h"
#include "juego.h"

Tower::Tower(Juego& pJuego,QPixmap sheet,QGraphicsItem *parent): juego(pJuego){
    this->sheet=sheet;
    sprite = sheet.copy(0, 0, 120, 118).scaled(68,75);
    setPixmap(sprite);

    //----------------------------------------------------MODIFICADO-----------------------------------------
    // create points vector
    QVector<QPointF> points;
    points << QPoint(1,0) << QPoint(2,0) << QPoint(2,1) << QPoint(1,1);

    // scale points
    int SCALE_FACTOR = 200;
    for (size_t i = 0, n = points.size(); i < n; i++){
        points[i] *= SCALE_FACTOR;
    }

    // create the QGraphicsPolygonItem
    attack_area = new QGraphicsPolygonItem(QPolygonF(points),this);
    attack_area->setPen(QPen(Qt::DotLine));

    // move the polygon
    QPointF poly_center(1.5,0.5);
    poly_center *= SCALE_FACTOR;
    poly_center = mapToScene(poly_center);;
    QPointF tower_center(x()+34,y()+34);
    QLineF ln(poly_center,tower_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());

    // set attack_dest
        attack_dest = QPointF(0,0);
        has_target = false;
        QTimer * timer = new QTimer();
            connect(timer,SIGNAL(timeout()),this,SLOT(aquire_target()));
            timer->start(200);
    //---------------------------------------------------FIN-----------------------------------------

    //QTimer *temporizador = new QTimer();
    //connect(temporizador,SIGNAL(timeout()),this,SLOT(anima()));
    //temporizador->start(200);
}

void Tower::anima() {
    Bala * bala = new Bala(juego);

    setPixmap(QPixmap(sheet.copy(i*120, mY, 120, 118)).scaled(68,75));
    if(mY==0){
        if(i==0){
            bala->setX(pos().x()+34);
            bala->setY(pos().y()+68);
            bala->setRotation(90);
            scene()->addItem(bala);
        }else if(i==1){
            bala->setX(pos().x()+68);
            bala->setY(pos().y()+68);
            bala->setRotation(45);
            scene()->addItem(bala);
        }else if(i==2){
            bala->setX(pos().x()+68);
            bala->setY(pos().y()+34);
            bala->setRotation(0);
            scene()->addItem(bala);
        }else if(i==3){
            bala->setX(pos().x()+68);
            bala->setY(pos().y()+0);
            bala->setRotation(315);
            scene()->addItem(bala);
        }
    }else{
        if(i==0){
            bala->setX(pos().x()+34);
            bala->setY(pos().y()+0);
            bala->setRotation(270);
            scene()->addItem(bala);
        }else if(i==1){
            bala->setX(pos().x()+0);
            bala->setY(pos().y()+0);
            bala->setRotation(225);
            scene()->addItem(bala);
        }else if(i==2){
            bala->setX(pos().x()+0);
            bala->setY(pos().y()+34);
            bala->setRotation(180);
            scene()->addItem(bala);
        }else if(i==3){
            bala->setX(pos().x()+0);
            bala->setY(pos().y()+68);
            bala->setRotation(135);
            scene()->addItem(bala);
        }
    }
}

//----------------------------------------------------MODIFICADO-----------------------------------------
void Tower::aquire_target(){
    // get a list of all enemies that collide with attack_area, find the closest one
    // and set it's position as the attack_dest

    // get a list of all enemies within attack_area
    QList<QGraphicsItem *> colliding_items = attack_area->collidingItems();

    // assume tower does not have a target, unless we find one
    has_target = false;

    for (size_t i = 0, n = colliding_items.size(); i < n; ++i){

        // make sure it is an enemy
        Enemigo * enemy = dynamic_cast<Enemigo *>(colliding_items[i]);

        // see if distance is closer
        if (enemy){
                attack_dest = enemy->pos();
                has_target = true;
                darOrientacion(enemy->pos());
                anima();
                break;
        }
    }
}

void Tower:: darOrientacion(QPointF posEnemigo){
    posEnemigo= juego.convertirCuadricula(posEnemigo);
    QPointF posTorre = juego.convertirCuadricula(this->pos());
    if(posEnemigo.x()<posTorre.x() && posEnemigo.y()==posTorre.y()){
        mY=120;
        i=2;
    }
    else if(posEnemigo.x()>posTorre.x() && posEnemigo.y()==posTorre.y()){
        mY=0;
        i=2;
    }
    else if(posEnemigo.x()==posTorre.x() && posEnemigo.y()<posTorre.y()){
        mY=120;
        i=0;
    }
    else if(posEnemigo.x()==posTorre.x() && posEnemigo.y()>posTorre.y()){
        mY=0;
        i=0;
    }
    else if(posEnemigo.x()<posTorre.x() && posEnemigo.y()<posTorre.y()){
        mY=120;
        i=1;
    }
    else if(posEnemigo.x()>posTorre.x() && posEnemigo.y()>posTorre.y()){
        mY=0;
        i=1;
    }
    else if(posEnemigo.x()<posTorre.x() && posEnemigo.y()>posTorre.y()){
        mY=120;
        i=3;
    }
    else if(posEnemigo.x()>posTorre.x() && posEnemigo.y()<posTorre.y()){
        mY=0;
        i=3;
    }
}
//---------------------------------------------------FIN-----------------------------------------
