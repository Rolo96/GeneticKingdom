#ifndef JUEGO_H
#define JUEGO_H

#include <QGraphicsView>
#include "List.h"
#include "List.cpp"
#include "enemigo.h"
#include <QMouseEvent>
#include <QPoint>

class Juego: public QGraphicsView {
public:
    Juego();
    QGraphicsScene * scene;
    List<Enemigo *> listaEnemigos;
    void mouseReleaseEvent ( QMouseEvent * event );
    QPoint convertirPunto(QPoint punto);
    QPoint convertirCuadricula(QPoint punto);
    int inicioX,anchoX,finX,inicioY,anchoY;
};

#endif // JUEGO_H
