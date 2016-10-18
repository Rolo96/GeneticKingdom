#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList>
#include <QPointF>
#include <QPoint>
#include "List.h"
#include <QTimer>

class Enemigo: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemigo(QGraphicsItem * parent=0);
    void rotar(QPointF punto);
    QTimer *temporizador;
    void correr();
    int posX=0;
    int posY=0;
    int mY=138;
    int vida=6;
    void colisiones();
public slots:
    void animar();
    void mover();
    void setRuta(List<QPoint> pRuta);
private:
    QList<QPointF> puntos;
    QPointF destino;
    int index=0;
    int i=0;
    bool flag=true;
    QPixmap sprite;
    QPixmap sheet;
    void setOrientacion();
};

#endif // ENEMIGO_H
