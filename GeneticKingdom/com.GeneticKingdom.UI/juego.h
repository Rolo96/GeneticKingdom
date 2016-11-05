#ifndef JUEGO_H
#define JUEGO_H
#define ROW 10
#define COL 16
#include <QGraphicsView>
#include "../com.GeneticKingdom.EstructurasDatos/List.h"
#include "../com.GeneticKingdom.EstructurasDatos/List.cpp"
#include "../com.GeneticKingdom.Logica/enemigo.h"
#include "../com.GeneticKingdom.Logica/bala.h"
#include "../com.GeneticKingdom.Logica/tower.h"
#include <QMouseEvent>
#include <QPoint>
#include <QPointF>
#include "../com.GeneticKingdom.Logica/Pathfinding.h"
#include <QObject>
#include <QPushButton>
#include <QTextEdit>

class Juego: public QGraphicsView {
    Q_OBJECT

public:
    Juego();
    List<QPoint> findPath(QPointF pos);
    QPointF convertirPunto(QPointF punto);
    QPointF convertirCuadricula(QPointF punto);
    QPushButton *postButton;
    QTextEdit *txt;
    bool permitirTorre(QPointF pos);
    bool noHayCamino(QPointF pos);
    void mousePressEvent( QMouseEvent * event );
    void mouseMoveEvent(QMouseEvent *event);
    void matar(Enemigo* enemigo, int estado);
    void setCursor(QString filename,QPointF pos);
    void borrarBala(Bala* bala);
    void borrarTorre(Tower* torre);
    void upgradeTorre(Tower* torre);
    void actualizarOro(int valor);
    void mConstruir(QMouseEvent *event,QPointF punto);
    void clickDerecho(QMouseEvent *event,QPointF punto);
    void asinarIcono(QMouseEvent *event);
    void setMachoFit(int fit);
    void setMutaciones(int pMutaciones);
public slots:
    void crearEnemigos();
    void solicitarEnemigos();
    void cambiarTamano();
private:
    int tipo;
    int Oro;
    int mutaciones=0;
    int numeroEnemigo;
    int generaciones=0;
    int machoFit=0;
    int muertos=0;
    int inicioX,anchoX,finX,inicioY,anchoY;
    bool construir;
    QPixmap sprite;
    QPixmap sheet;
    QTimer *temporizador;
    QTimer *temporizador2;
    QGraphicsScene * scene;
    QGraphicsPixmapItem * cursor;
    QGraphicsPixmapItem * torres;
    QGraphicsTextItem* itemOro;
    QGraphicsTextItem* itemGeneraciones;
    QGraphicsTextItem* itemMuertes;
    QGraphicsTextItem* itemMutaciones;
    QGraphicsTextItem* itemMachoFit;
    Pathfinding *path = new Pathfinding();
};

#endif // JUEGO_H


