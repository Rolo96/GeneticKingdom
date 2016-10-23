#ifndef JUEGO_H
#define JUEGO_H
#define ROW 10
#define COL 16
#include <QGraphicsView>
#include "List.h"
#include "List.cpp"
#include "enemigo.h"
#include "bala.h"
#include <QMouseEvent>
#include <QPoint>
#include <QPointF>
#include "Pathfinding.h"
#include <QObject>

class Juego: public QGraphicsView {
    Q_OBJECT
public:
    Juego();
    bool construir;
    QPixmap sprite;
    QPixmap sheet;
    QGraphicsScene * scene;
    QGraphicsPixmapItem * cursor;
    QGraphicsPixmapItem * torres;
    QGraphicsPixmapItem * torres1;
    QGraphicsPixmapItem * torres2;
    void mousePressEvent( QMouseEvent * event );
    void mouseMoveEvent(QMouseEvent *event);
    QPointF convertirPunto(QPointF punto);
    QPointF convertirCuadricula(QPointF punto);
    int inicioX,anchoX,finX,inicioY,anchoY;
    List<QPoint> findPath(QPointF pos);
    bool permitirTorre(QPointF pos);
    bool noHayCamino(QPointF pos);
    void matar(Enemigo* enemigo);
    void setCursor(QString filename,QPointF pos);
    void borrarBala(Bala* bala);
public slots:
    void crearEnemigos();
};

#endif // JUEGO_H


