#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList>
#include <QPointF>
#include <QPoint>
#include "../com.GeneticKingdom.EstructurasDatos/List.h"
#include <QTimer>
class Juego;
class Enemigo: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemigo(int pVelocidad, int pResA, int pResB, int pResC, int pVida, int pTipo, Juego &pJuego,int pMutado);
    ~Enemigo();

    void correr();
    void setOrientacion();
    void setVida(int pVida);
    int getPosY();
    int getPosX();
    int getMy();
    int getVida();
    int getResA() const;
    int getResB() const;
    int getResC() const;
    int getFitness() const;
public slots:
    void animar();
    void mover();
    void setRuta(List<QPoint> pRuta);
private:
    Juego &juego;
    int index=0;
    int i=0;
    int posX=0;
    int posY=0;
    int mY=138;
    int vida=1;
    int velocidad;
    int resA;
    int resB;
    int resC;
    int tipo;
    int fitness;
    bool flag=true;
    QPixmap sprite;
    QPixmap sheet;
    QTimer *temporizador;
    List<QPoint> ruta;
};

#endif // ENEMIGO_H
