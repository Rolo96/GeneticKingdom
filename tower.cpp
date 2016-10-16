#include "tower.h"
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include <QTimer>
#include <QDebug>

Tower::Tower(QGraphicsItem *parent){
    //setPixmap(QPixmap(":/Imagenes/Torre.png"));
    sheet = QPixmap(":/Imagenes/Torre.png");
    sprite = sheet.copy(0, 0, 120, 118).scaled(68,75);
    setPixmap(sprite);
    QVector<QPointF> puntos;
    puntos << QPoint(1,0) << QPoint(2,0) << QPoint(3,1) << QPoint(3,2) << QPoint(2,3) << QPoint(1,3) << QPoint(0,2) << QPoint(0,1);

    QTimer *temporizador = new QTimer();
    connect(temporizador,SIGNAL(timeout()),this,SLOT(anima()));
    temporizador->start(200);

    int escala=100;
    int n=puntos.size();
    for(size_t i=0;i<n;i++){
        puntos[i]*=escala;
    }

    //areaAtaque = new QGraphicsPolygonItem(QPolygonF(puntos),this);

    QPointF centroPoligono(1.5,1.5);
    centroPoligono*=escala;
    centroPoligono=mapToScene(centroPoligono);
    QPointF centroTorre(x()+30,y()+100);
    QLineF ln(centroPoligono,centroTorre);
    //areaAtaque->setPos(x()+ln.dx(),y()+ln.dy());

}

void Tower::anima() {
    setPixmap(QPixmap(sheet.copy(i*120, mY, 120, 118)).scaled(68,75));
    if(flag){
        if(i==3){flag=false;i=-1;mY=120;}i++;
    }else{
        if(i==3){flag=true;i=-1;mY=0;}i++;
    }
}
