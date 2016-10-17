#ifndef BALA_H
#define BALA_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Bala: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bala(QGraphicsItem * parent=0);
    void colisiones();
public slots:
    void moverBala();
private:
};

#endif // BALA_H
