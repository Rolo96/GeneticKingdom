#include "juego.h"
#include <QGraphicsScene>
#include "tower.h"
#include "enemigo.h"
#include <QPixmap>
#include <QDebug>
#include "List.h"
#include <iostream>
#include <QMouseEvent>
#include <QPointF>
#include <QGraphicsLineItem>
#include <QPen>
using namespace std;


Pathfinding *path = new Pathfinding();
Juego::Juego(){
    inicioX=110;
    finX=1208;
    anchoX=68;
    inicioY=0;
    anchoY=68;
    construir=false;
    cursor=nullptr;
    setMouseTracking(true);

    path = new Pathfinding();
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1280,680);
    setScene(scene);
    QPixmap pix(":/Imagenes/Map.jpg");
    scene->addPixmap(pix);


    setFixedSize(1280,680);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QTimer *temporizador = new QTimer();
    connect(temporizador,SIGNAL(timeout()),this,SLOT(crearEnemigos()));
    temporizador->start(3000);

        torres = new QGraphicsPixmapItem();
        sheet = QPixmap(":/Imagenes/torre1.png");
        sprite = sheet.copy(0, 0, 120, 118).scaled(68,75);
        torres->setPixmap(sprite);
        scene->addItem(torres);
        torres->setPos(0,0);
        torres1 = new QGraphicsPixmapItem();
        sheet = QPixmap(":/Imagenes/torre2.png");
        sprite = sheet.copy(0, 0, 120, 118).scaled(68,75);
        torres1->setPixmap(sprite);
        scene->addItem(torres1);
        torres1->setPos(0,75);
        torres2 = new QGraphicsPixmapItem();
        sheet = QPixmap(":/Imagenes/torre3.png");
        sprite = sheet.copy(0, 0, 120, 118).scaled(68,75);
        torres2->setPixmap(sprite);
        scene->addItem(torres2);
        torres2->setPos(0,150);
}
void Juego::setCursor(QString filename,QPointF pos){
    construir=true;
    cursor = new QGraphicsPixmapItem();
    sheet = QPixmap(filename);
    sprite = sheet.copy(0, 0, 120, 118).scaled(68,75);
    cursor->setPixmap(sprite);
    scene->addItem(cursor);
    cursor->setPos(pos.x(),pos.y());
}
void Juego::mouseMoveEvent(QMouseEvent *event){
    if(construir){
        qDebug()<<"mueve";
        cursor->setPos(event->pos());
    }
}
void Juego:: mousePressEvent ( QMouseEvent * event ){
    if(construir){
        if(event->button() == Qt::LeftButton)
        {
            QPointF punto = convertirCuadricula(event->pos());
            if (punto.x()!=-1 && permitirTorre(punto)){
              //qDebug()<<puntoCreacion;
              //findPath(puntoCreacion);
              punto = convertirPunto(punto);
              Tower * tower = new Tower(*this,sheet);
              scene->addItem(tower);
              tower->setPos(punto);
              for(int i=0;i<scene->items().size();i++){
                  Enemigo * enemy = dynamic_cast<Enemigo *>(scene->items()[i]);
                  if (enemy){
                      QPointF puntoCreacion;
                      puntoCreacion.setX(enemy->posX);
                      puntoCreacion.setY(enemy->posY);
                      enemy->setRuta(findPath(convertirCuadricula(puntoCreacion)));
                  }
              }
              construir=false;
              delete cursor;
              cursor=nullptr;
            }else if(event->pos().x()<68 && event->pos().y()<75){
                construir=false;
                delete cursor;
                cursor=nullptr;
             }else if(event->pos().x()<68 && (event->pos().y()<150 && event->pos().y()>75)){
                construir=false;
                delete cursor;
                cursor=nullptr;
             }else if(event->pos().x()<68 && (event->pos().y()<225 && event->pos().y()>150)){
                construir=false;
                delete cursor;
                cursor=nullptr;
             }
        }
    }else{
        if(event->pos().x()<68 && event->pos().y()<75){
           setCursor(":/Imagenes/torre1.png",event->pos());
        }else if(event->pos().x()<68 && (event->pos().y()<150 && event->pos().y()>75)){
           setCursor(":/Imagenes/torre2.png",event->pos());
        }else if(event->pos().x()<68 && (event->pos().y()<225 && event->pos().y()>150)){
            setCursor(":/Imagenes/torre3.png",event->pos());
        }
    }
}

QPointF Juego::convertirPunto(QPointF punto){
    QPoint puntoCreacion;
    puntoCreacion.setX(punto.x()*anchoX+inicioX);
    puntoCreacion.setY(punto.y()*anchoY+inicioY);
    return puntoCreacion;
}

QPointF Juego::convertirCuadricula(QPointF punto){
    if(punto.x()>=inicioX && punto.x()<=finX-anchoX){
        int posx, posy;
        posx= (-inicioX+punto.x())/anchoX;
        posy=(inicioY+punto.y())/anchoY;
        QPointF puntoCreacion;
        puntoCreacion.setX(posx);
        puntoCreacion.setY(posy);
        return puntoCreacion;
    }
    else{
        QPointF puntoCreacion;
        puntoCreacion.setX(-1);
        puntoCreacion.setY(-1);
        return puntoCreacion;
    }
}

List<QPoint> Juego:: findPath(QPointF pos){
    return path->trazar(pos);
}

bool Juego::noHayCamino(QPointF pos){
    path->grid[static_cast<int>(pos.y())][static_cast<int>(pos.x())]=0;
    List<QPoint> puntos;
    QPointF punto;
    punto.setX(0);
    punto.setY(0);
    puntos=path->trazar(punto);
    return puntos.get_Node(0)->get_data().x()==-1;
}

bool Juego::permitirTorre(QPointF pos){
    for(int i=0;i<scene->items().size();i++){
        Enemigo * enemy = dynamic_cast<Enemigo *>(scene->items()[i]);
        if (enemy){
            QPointF puntoCreacion;
            puntoCreacion.setX(enemy->x());
            puntoCreacion.setY(enemy->y());
            int mY=enemy->mY;
            puntoCreacion=convertirCuadricula(puntoCreacion);
            if(path->grid[static_cast<int>(pos.y())][static_cast<int>(pos.x())]==0){
                return false;
            }
            else if(noHayCamino(pos)){
                path->grid[static_cast<int>(pos.y())][static_cast<int>(pos.x())]=1;
               return false;
            }
            else if(puntoCreacion==pos){
                path->grid[static_cast<int>(pos.y())][static_cast<int>(pos.x())]=1;
                return false;
            }
            else if(mY==0){
                pos.setY(pos.y()-1);
                if(puntoCreacion==pos){
                    path->grid[static_cast<int>(pos.y())][static_cast<int>(pos.x())]=1;
                    return false;
                }
            }
            else if(mY==207){
                pos.setY(pos.y()+1);
                if(puntoCreacion==pos){
                    path->grid[static_cast<int>(pos.y())][static_cast<int>(pos.x())]=1;
                    return false;
                }
            }
            else if(mY==69){
                pos.setX(pos.x()+1);
                if(puntoCreacion==pos){
                    path->grid[static_cast<int>(pos.y())][static_cast<int>(pos.x())]=1;
                    return false;
                }
            }
            else if(mY==138){
                pos.setX(pos.x()-1);
                if(puntoCreacion==pos){
                    path->grid[static_cast<int>(pos.y())][static_cast<int>(pos.x())]=1;
                    return false;
                }
            }
        }
    }
    return true;
}

void Juego::matar(Enemigo* enemigo){
    scene->removeItem(enemigo);
}

void Juego::crearEnemigos(){

    for(int i=0;i<1;i++){
        Enemigo * enemigo = new Enemigo();
        scene->addItem(enemigo);
        enemigo->setPos(110,0);
        //listaEnemigos.add_end(enemigo);
        enemigo->setRuta(findPath(convertirCuadricula(enemigo->pos())));
        enemigo->setPos(110,0);
        enemigo->correr();
    }
}
