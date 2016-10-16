#include "juego.h"
#include <QGraphicsScene>
#include "tower.h"
#include "enemigo.h"
#include <QPixmap>
#include "List.h"
#include <iostream>
#include <QMouseEvent>
#include <QPoint>
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
    QPixmap pix(":/Imagenes/mapa1.jpg");
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
      QPoint punto = convertirCuadricula(event->pos());
      if (punto.x()!=-1){
        punto = convertirPunto(punto);
        Tower * tower = new Tower();
        scene->addItem(tower);
        tower->setPos(punto);
        findPath();
      }
  }
}

QPoint Juego::convertirPunto(QPoint punto){
    QPoint puntoCreacion;
    puntoCreacion.setX(punto.x()*anchoX+inicioX);
    puntoCreacion.setY(punto.y()*anchoY+inicioY);
    return puntoCreacion;
}

QPoint Juego::convertirCuadricula(QPoint punto){
    if(punto.x()>=inicioX && punto.x()<=finX-anchoX){
        int posx, posy;
        posx= (-inicioX+punto.x())/anchoX;
        posy=(inicioY+punto.y())/anchoY;
        QPoint puntoCreacion;
        puntoCreacion.setX(posx);
        puntoCreacion.setY(posy);
        return puntoCreacion;
    }
    else{
        QPoint puntoCreacion;
        puntoCreacion.setX(-1);
        puntoCreacion.setY(-1);
        return puntoCreacion;
    }
}

void Juego:: findPath(){
    path->trazar();
}
