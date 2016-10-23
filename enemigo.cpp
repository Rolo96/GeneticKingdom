#include "enemigo.h"
#include <QPixmap>
#include <QTimer>
#include <iostream>
#include "juego.h"
using namespace std;


List<QPoint> rutaNueva;
Enemigo::Enemigo(Juego& pJuego,QGraphicsItem *parent): juego(pJuego){
    ruta = *new List<QPoint>();
    sheet = QPixmap(":/Imagenes/Macho.png");
    sprite = sheet.copy(0, 138, 33, 69);
    setPixmap(sprite);
    temporizador = new QTimer();
    QTimer *temporizador2 = new QTimer();
    connect(temporizador,SIGNAL(timeout()),this,SLOT(mover()));
    connect(temporizador2,SIGNAL(timeout()),this,SLOT(animar()));
    temporizador2->start(50);
}

Enemigo::~Enemigo(){}

void Enemigo::animar() {
    setPixmap(QPixmap(sheet.copy(index*53, mY, 33, 69)));
    if(flag){
        if(index==2){flag=false;index=index-2;}index++;
    }else{
        if(index==0){flag=true;index=index+2;}index--;
    }
}

void Enemigo::mover(){
    if(mY==0){
        setPos(x(), y()+2);
        if(this->y()>=posY){
            i++;
            setOrientacion();
        }
    }
    else if(mY==69){
        setPos(x()-2, y());
        if(this->x()<=posX){
            i++;
            setOrientacion();
        }
    }
    else if(mY==138){
        setPos(x()+2, y());
        if(this->x()>=posX){
            i++;
            setOrientacion();
        }
    }
    else if(mY==207){
        setPos(x(), y()-2);
        if(this->y()<=posY){
            i++;
            setOrientacion();
        }
    }
    if(this->x()>1280){
        juego.matar(this);
    }
}

void Enemigo::setRuta(List<QPoint> pRuta){
    i=-1;
    ruta=pRuta;
    //qDebug()<<"Inicio";
    //qDebug()<<id;
    //qDebug()<<ruta.get_head()->get_data();
    //qDebug()<<ruta.get_Node(1)->get_data();
    //pRuta.print();
}

void Enemigo::setOrientacion(){
    if(i<ruta.get_size()-1){
        //qDebug()<<ruta.get_Node(i+1)->get_data();
        if(ruta.get_Node(i)->get_data().x()!=ruta.get_Node(i+1)->get_data().x()){
            //Abajo
            if(ruta.get_Node(i)->get_data().x()<ruta.get_Node(i+1)->get_data().x()){
                mY=0;
                posY=ruta.get_Node(i+1)->get_data().x()*68;
                posX=(ruta.get_Node(i+1)->get_data().y())*68+128;
            }//qDebug()<<posY;}
            //Arriba
            else{
                mY=207;
                posY=ruta.get_Node(i+1)->get_data().x()*68;
                posX=(ruta.get_Node(i+1)->get_data().y())*68+128;
            }//qDebug()<<posY;}
        }
        else{
            //derecha
            if(ruta.get_Node(i)->get_data().y()<ruta.get_Node(i+1)->get_data().y()){
                mY=138;
                posY=ruta.get_Node(i+1)->get_data().x()*68;
                posX=(ruta.get_Node(i+1)->get_data().y())*68+128;
                //qDebug()<<posX;
            }//qDebug()<<posX;}
            //izquierda
            else{
                mY=69;
                posY=ruta.get_Node(i+1)->get_data().x()*68;
                posX=(ruta.get_Node(i+1)->get_data().y())*68+128;
            }//qDebug()<<posX;}
        }
    }
    else{mY=138;}
    //qDebug()<<"Punto";
    //qDebug()<<id;
    //qDebug()<<*ruta;
    //qDebug()<<ruta.get_Node(i)->get_data();
}

void Enemigo::correr(){temporizador->start(20);}

void Enemigo::colisiones(){

    QList<QGraphicsItem *> list = collidingItems() ;
    foreach(QGraphicsItem * i , list)
    {
        if(this->vida<=0){
            scene()->removeItem(this);
        }
    }
}
