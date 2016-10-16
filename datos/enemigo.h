#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList>
#include <QPointF>

class Enemigo: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemigo(QGraphicsItem * parent=0);
    void rotar(QPointF punto);
public slots:
    void animar();
    void mover();
private:
    QList<QPointF> puntos;
    QPointF destino;
    int indice;
    int i=0;
    int mY=138;
    bool flag=true;
    QPixmap sprite;
    QPixmap sheet;

};

#endif // ENEMIGO_H
