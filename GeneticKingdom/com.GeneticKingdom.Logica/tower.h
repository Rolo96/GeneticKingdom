#ifndef TOWER_H
#define TOWER_H
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QObject>


class Juego;
class Tower:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Tower(Juego &pJuego, QPixmap sheet, int tipo);
    ~Tower();

    void darOrientacion(QPointF posEnemigo);
    void setSheet(const QPixmap &value);
    void setVelocidad(int value);
    void fijarEnemigo(bool pBorrable);
    void setSCALE_FACTOR(int value);
    void setNivel(int value);
    void setTipo(int value);
    void setSprite(const QPixmap &value);
    int getSCALE_FACTOR() const;
    int getVelocidad() const;
    int getNivel() const;
    int getTipo() const;
    QGraphicsPolygonItem *getAttack_area() const;
    QTimer *getTimer() const;
    QPixmap getSheet() const;
    QPixmap getSprite() const;
public slots:
    void anima(int pSpriteY,int pSpriteX,bool pBorrable);
    void atacar();
    void crearAreaAtaque();
    void realizarHabilidad();
    void terceraHabilidad();
private:
    int sprietX=0;
    int spriteY=0;
    int velocidad;
    int SCALE_FACTOR;
    int nivel;
    int tipo;
    int contHabilidad=0;
    bool has_target;
    QVector<QPointF> points;
    QTimer * timer;
    QTimer * tHabilidad;
    QPixmap sprite;
    QPixmap sheet;
    Juego &juego;
    QGraphicsPolygonItem * attack_area;
    QPointF attack_dest;
};
#endif // TOWER_H
