#ifndef TOWER_H
#define TOWER_H
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QObject>

class Tower:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Tower(QGraphicsItem * parent=0);
public slots:
    void anima();
private:
    //QGraphicsPolygonItem *areaAtaque;
    int i=0;
    int mY=0;
    bool flag=true;
    QPixmap sprite;
    QPixmap sheet;
};
#endif // TOWER_H
