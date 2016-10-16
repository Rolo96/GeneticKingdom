#include "tower.h"
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QPolygonF>

Tower::Tower(QGraphicsPixmapItem *parent){
    setPixmap(QPixmap(":/Imagenes/tower.png"));

    QVector<QPointF> puntos;
    puntos << QPoint(1,0) << QPoint(2,0) << QPoint(3,1) << QPoint(3,2) << QPoint(2,3) << QPoint(1,3) << QPoint(0,2) << QPoint(0,1);

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
