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

    path = new Pathfinding();
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1280,680);
    setScene(scene);
    QPixmap pix(":/Imagenes/Map.jpg");
    scene->addPixmap(pix);

    setFixedSize(1280,680);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



    for(int i=0;i<1;i++){
        Enemigo * enemigo = new Enemigo();
        scene->addItem(enemigo);
        enemigo->setPos(110,0);
        listaEnemigos.add_end(enemigo);
        listaEnemigos.get_Node(0)->get_data()->setRuta(findPath(convertirCuadricula(listaEnemigos.get_Node(0)->get_data()->pos())));
        listaEnemigos.get_Node(0)->get_data()->setPos(110,0);
        listaEnemigos.get_Node(0)->get_data()->correr();
    }
}

void Juego:: mouseReleaseEvent ( QMouseEvent * event ){
  if(event->button() == Qt::LeftButton)
  {
      QPointF punto = convertirCuadricula(event->pos());
      if (punto.x()!=-1 && permitirTorre(punto)){

              QPointF puntoCreacion;
              puntoCreacion.setX(listaEnemigos.get_Node(0)->get_data()->posX);
              puntoCreacion.setY(listaEnemigos.get_Node(0)->get_data()->posY);
              //qDebug()<<puntoCreacion;
              //findPath(puntoCreacion);
              punto = convertirPunto(punto);
              Tower * tower = new Tower();
              scene->addItem(tower);
              tower->setPos(punto);
              listaEnemigos.get_Node(0)->get_data()->setRuta(findPath(convertirCuadricula(puntoCreacion)));

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
    for(int i=0;i<listaEnemigos.get_size();i++){
        QPointF puntoCreacion;
        puntoCreacion.setX(listaEnemigos.get_Node(i)->get_data()->x());
        puntoCreacion.setY(listaEnemigos.get_Node(i)->get_data()->y());
        int mY=listaEnemigos.get_Node(i)->get_data()->mY;
        puntoCreacion=convertirCuadricula(puntoCreacion);
        if(path->grid[static_cast<int>(pos.y())][static_cast<int>(pos.x())]==0){
            return false;
        }
        else if(noHayCamino(pos)){
            path->grid[static_cast<int>(pos.y())][static_cast<int>(pos.x())]=1;
           return false;
        }
        else if(puntoCreacion==pos){
            return false;
        }
        else if(mY==0){
            pos.setY(pos.y()-1);
            if(puntoCreacion==pos){
                return false;
            }
        }
        else if(mY==207){
            pos.setY(pos.y()+1);
            if(puntoCreacion==pos){
                return false;
            }
        }
        else if(mY==69){
            pos.setX(pos.x()+1);
            if(puntoCreacion==pos){
                return false;
            }
        }
        else if(mY==138){
            pos.setX(pos.x()-1);
            if(puntoCreacion==pos){
                return false;
            }
        }
    }
    return true;
}
