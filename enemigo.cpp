#include "enemigo.h"
#include <QPixmap>
#include <QTimer>
#include <iostream>
#include "List.cpp"
using namespace std;

List<QPoint> ruta;
List<QPoint> rutaNueva;
Enemigo::Enemigo(QGraphicsItem *parent)
{
    sheet = QPixmap(":/Imagenes/Macho.png");
    sprite = sheet.copy(0, 138, 33, 69);
    setPixmap(sprite);
    temporizador = new QTimer();
    QTimer *temporizador2 = new QTimer();
    connect(temporizador,SIGNAL(timeout()),this,SLOT(mover()));
    connect(temporizador2,SIGNAL(timeout()),this,SLOT(animar()));
    temporizador2->start(50);
}

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
}

void Enemigo::setRuta(List<QPoint> pRuta){
    i=-1;
    ruta=pRuta;
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

}

void Enemigo::correr(){temporizador->start(60);}
