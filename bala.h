#ifndef BALA_H
#define BALA_H

#include <QGraphicsPixmapItem>
#include <QObject>
class Juego;
class Bala: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bala(Juego& pJuego, QGraphicsItem * parent=0);
    void colisiones();
    Juego &juego;
public slots:
    void moverBala();
private:
};

#endif // BALA_H
