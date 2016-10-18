#ifndef TOWER_H
#define TOWER_H
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QObject>

class Juego;
class Tower:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Tower(Juego& pJuego, QGraphicsItem * parent=0);
    void darOrientacion(QPointF posEnemigo);
public slots:
    void anima();
    //----------------------------------------------------MODIFICADO-----------------------------------------
     void aquire_target();
    //----------------------------------------------------FIN-----------------------------------------
private:
    //QGraphicsPolygonItem *areaAtaque;
    int i=0;
    int mY=0;
    QPixmap sprite;
    QPixmap sheet;
    Juego &juego;
    //----------------------------------------------------MODIFICADO-----------------------------------------
    QGraphicsPolygonItem * attack_area;
    QPointF attack_dest;
    bool has_target;
    //----------------------------------------------------FIN-----------------------------------------
};
#endif // TOWER_H

//----------------------------------------------------MODIFICADO-----------------------------------------
//----------------------------------------------------FIN-----------------------------------------
