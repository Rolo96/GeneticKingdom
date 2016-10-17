#ifndef JUEGO_H
#define JUEGO_H
#define ROW 10
#define COL 16
#include <QGraphicsView>
#include "List.h"
#include "List.cpp"
#include "enemigo.h"
#include <QMouseEvent>
#include <QPoint>
#include <QPointF>
#include "Pathfinding.h"

class Juego: public QGraphicsView {
public:
    Juego();
    QGraphicsScene * scene;
    List<Enemigo *> listaEnemigos;
    void mouseReleaseEvent ( QMouseEvent * event );
    QPointF convertirPunto(QPointF punto);
    QPointF convertirCuadricula(QPointF punto);
    int inicioX,anchoX,finX,inicioY,anchoY;
    List<QPoint> findPath(QPointF pos);
    bool permitirTorre(QPointF pos);
    bool noHayCamino(QPointF pos);
};

#endif // JUEGO_H
