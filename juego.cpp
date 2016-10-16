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

    for(int i=0;i<4;i++){
        Enemigo * enemigo = new Enemigo();
        scene->addItem(enemigo);
        enemigo->setPos(0,i*200);
        listaEnemigos.add_end(enemigo);
    }
}

void Juego:: mouseReleaseEvent ( QMouseEvent * event ){
  if(event->button() == Qt::LeftButton)
  {
      QPointF punto = convertirCuadricula(event->pos());
      if (punto.x()!=-1){
          if(path->grid[static_cast<int>(punto.y())][static_cast<int>(punto.x())]==1){
              path->grid[static_cast<int>(punto.y())][static_cast<int>(punto.x())]=0;
              //QPointF puntoCreacion;
              //puntoCreacion.setX(0);
              //puntoCreacion.setY(6);
              //findPath(puntoCreacion);
              findPath(convertirCuadricula(listaEnemigos.get_Node(0)->get_data()->pos()));
              punto = convertirPunto(punto);
              Tower * tower = new Tower();
              scene->addItem(tower);
              tower->setPos(punto);
          }
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
    qDebug()<< pos;
    return path->trazar(pos);
}
