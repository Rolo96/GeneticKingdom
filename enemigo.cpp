#include "enemigo.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include <iostream>
using namespace std;
Enemigo::Enemigo(QGraphicsItem *parent)
{
    setPos(200,200);
    sheet = QPixmap(":/Imagenes/Men.png");
    sprite = sheet.copy(0, 138, 33, 69);
    setPixmap(sprite);

    QTimer *temporizador = new QTimer();
    QTimer *temporizador2 = new QTimer();
    connect(temporizador,SIGNAL(timeout()),this,SLOT(mover()));
    connect(temporizador2,SIGNAL(timeout()),this,SLOT(animar()));
    temporizador->start(20);
    temporizador2->start(50);
}


void Enemigo::animar() {
    setPixmap(QPixmap(sheet.copy(i*53, mY, 33, 69)));
    if(flag){
        if(i==2){flag=false;i=i-2;}i++;
    }else{
        if(i==0){flag=true;i=i+2;}i--;
    }
}

void Enemigo::mover(){
    if(x()<600){
        setPos(x()+3, y());
        mY=138;
    }
    else if(x() > 600 && y()>68 && mY!=0 && y()<400){
        setPos(x(), y()-3);
        mY=207;
    }
    else if(y()<=68 && x()<1000){
        setPos(x()+3, y());
        mY=138;
    }
    else if(x()>1000 && y()<500){
        setPos(x(), y()+3);
        mY=0;
    }
    else if(y()>=500){
        setPos(x()-3, y());
        mY=69;
    }
}
