#ifndef BALA_H
#define BALA_H

#include <QGraphicsPixmapItem>
#include <QObject>
class Juego;
class Bala: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bala(Juego &pJuego, QPixmap bala, int tipo, bool pBorrable);
    ~Bala();

    void colisiones();
public slots:
    void moverBala();
private:
    int tipo;
    bool borrable;
    Juego &juego;
};

#endif // BALA_H
