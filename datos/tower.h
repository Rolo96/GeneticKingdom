#ifndef TOWER_H
#define TOWER_H
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>

class Tower: public QGraphicsPixmapItem{
public:
    Tower(QGraphicsPixmapItem *parent=0);
private:
    //QGraphicsPolygonItem *areaAtaque;
};
#endif // TOWER_H
