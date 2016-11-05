#include "tower.h"
#include <QTimer>
#include <QDebug>
#include "bala.h"
#include "../com.GeneticKingdom.UI/juego.h"
#include <QSound>

/**
 * Comtructor de la clase
 * @param pJuego: Instancia del juego hecha
 * @param pSheet: Imagen de la torre según tipo
 * @param pTipo: Tipo de torre
 * @return: Instancia de torre
 */
Tower::Tower(Juego &pJuego, QPixmap pSheet, int pTipo) : juego(pJuego){
    sheet=pSheet;
    sprite = sheet.copy(0, 0, 120, 118).scaled(68,75);
    tipo=pTipo;
    nivel=0;
    velocidad=200;
    SCALE_FACTOR=200;
    points << QPoint(1,0) << QPoint(2,0) << QPoint(2,1) << QPoint(1,1);

    crearAreaAtaque();
    setPixmap(sprite);

    QTimer *habilidad = new QTimer();
    connect(habilidad,SIGNAL(timeout()),this,SLOT(realizarHabilidad()));
    habilidad->start(10000);

    attack_dest = QPointF(0,0);
    has_target = false;

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(atacar()));
    timer->start(velocidad);
    tHabilidad = new QTimer();
    connect(tHabilidad,SIGNAL(timeout()),this,SLOT(terceraHabilidad()));
}

/**
 * Destructor de la clase
 */
Tower::~Tower(){}

/**
 * Método que se ejecuta cada cierto tiempo para realizar habilidad especial de las torres
 */
void Tower::realizarHabilidad() {
    if(tipo==1){
        anima(0,0,true);
        anima(0,1,true);
        anima(0,2,true);
        anima(0,3,true);
        anima(1,0,true);
        anima(1,1,true);
        anima(1,2,true);
        anima(1,3,true);
    }else if(tipo==2){
        anima(1,0,false);
        anima(1,2,false);
        anima(0,0,false);
        anima(0,2,false);
        //aquire_target(false);
    }else if(tipo==3){
        tHabilidad->start(200);
    }
}

/**
 * Método necesario para realizar habilidad especial de tercera torre
 */
void Tower::terceraHabilidad(){
    if(contHabilidad<4){
        anima(1,1,true);
        anima(1,3,true);
        anima(0,1,true);
        anima(0,3,true);
        contHabilidad++;
    }else{
        contHabilidad=0;
        tHabilidad->stop();
    }

}

/**
 * Método para realizar la animación de las torres
 * @param pSpriteY: posición X de sprite
 * @param pSpriteX: posición Y de sprite
 * @param pBorrable: parámetro para saber si la bala que dispara es borrable o no
 */
void Tower::anima(int pSpriteY,int pSpriteX,bool pBorrable) {
    Bala * bala;
    if(tipo==1){
        bala = new Bala(juego, QPixmap("/home/raulaq/ClionProjects/GeneticKingdom/Imagenes/llama"), 1, pBorrable);
    }else if(tipo==2){
        bala = new Bala(juego, QPixmap("/home/raulaq/ClionProjects/GeneticKingdom/Imagenes/flecha"), 2, pBorrable);
    }else if(tipo==3){
        bala = new Bala(juego, QPixmap("/home/raulaq/ClionProjects/GeneticKingdom/Imagenes/bullet1"), 3, pBorrable);
    }
    setPixmap(QPixmap(sheet.copy(sprietX*120, spriteY, 120, 118)).scaled(68,75));
    if(pSpriteY==0){
        if(pSpriteX==0){
            bala->setX(pos().x()+34);
            bala->setY(pos().y()+68);
            bala->setRotation(90);
            scene()->addItem(bala);
        }else if(pSpriteX==1){
            bala->setX(pos().x()+68);
            bala->setY(pos().y()+68);
            bala->setRotation(45);
            scene()->addItem(bala);
        }else if(pSpriteX==2){
            bala->setX(pos().x()+68);
            bala->setY(pos().y()+34);
            bala->setRotation(0);
            scene()->addItem(bala);
        }else if(pSpriteX==3){
            bala->setX(pos().x()+68);
            bala->setY(pos().y()+0);
            bala->setRotation(315);
            scene()->addItem(bala);
        }
    }else{
        if(pSpriteX==0){
            bala->setX(pos().x()+34);
            bala->setY(pos().y()+0);
            bala->setRotation(270);
            scene()->addItem(bala);
        }else if(pSpriteX==1){
            bala->setX(pos().x()+0);
            bala->setY(pos().y()+0);
            bala->setRotation(225);
            scene()->addItem(bala);
        }else if(pSpriteX==2){
            bala->setX(pos().x()+0);
            bala->setY(pos().y()+34);
            bala->setRotation(180);
            scene()->addItem(bala);
        }else if(pSpriteX==3){
            bala->setX(pos().x()+0);
            bala->setY(pos().y()+68);
            bala->setRotation(135);
            scene()->addItem(bala);
        }
    }
    QSound::play("/home/raulaq/ClionProjects/GeneticKingdom/Sonidos/disparo.wav");
}

/**
 * Método para atacar a los enemigos
 */
void Tower::atacar() {
    fijarEnemigo(true);
}

/**
 * Método para buscar si hay alguien dentro del área de ataque y disparar
 * @param pBorrable: bala borrable o no
 */
void Tower::fijarEnemigo(bool pBorrable){
    QList<QGraphicsItem *> colliding_items = attack_area->collidingItems();
    has_target = false;
    Enemigo *enemigo = nullptr;
    for (size_t i = 0, n = colliding_items.size(); i < n; ++i){
        Enemigo * enemy = dynamic_cast<Enemigo *>(colliding_items[i]);
        if (enemy){
                enemigo=enemy;
                has_target=true;
        }
    }
    if(has_target){
        attack_dest = enemigo->pos();
        darOrientacion(enemigo->pos());
        anima(spriteY,sprietX,pBorrable);
    }
}

/**
 * Método para crear el área de ataque de las torres
 */
void Tower::crearAreaAtaque(){
    for (size_t i = 0, n = points.size(); i < n; i++){
        points[i] *= SCALE_FACTOR;
    }
    attack_area = new QGraphicsPolygonItem(QPolygonF(points),this);
    attack_area->setPen(QPen(Qt::DotLine));
    QPointF poly_center(1.5,0.5);
    poly_center *= SCALE_FACTOR;
    poly_center = mapToScene(poly_center);
    QPointF tower_center(x()+34,y()+34);
    QLineF ln(poly_center,tower_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());
}

/**
 * Método para dar orientación a las torres según la posición del enemigo
 * @param posEnemigo: posición del enemigo
 */
void Tower:: darOrientacion(QPointF posEnemigo){
    posEnemigo= juego.convertirCuadricula(posEnemigo);
    QPointF posTorre = juego.convertirCuadricula(this->pos());
    if(posEnemigo.x()<posTorre.x() && posEnemigo.y()==posTorre.y()){
        spriteY=120;
        sprietX=2;
    }
    else if(posEnemigo.x()>posTorre.x() && posEnemigo.y()==posTorre.y()){
        spriteY=0;
        sprietX=2;
    }
    else if(posEnemigo.x()==posTorre.x() && posEnemigo.y()<posTorre.y()){
        spriteY=120;
        sprietX=0;
    }
    else if(posEnemigo.x()==posTorre.x() && posEnemigo.y()>posTorre.y()){
        spriteY=0;
        sprietX=0;
    }
    else if(posEnemigo.x()<posTorre.x() && posEnemigo.y()<posTorre.y()){
        spriteY=120;
        sprietX=1;
    }
    else if(posEnemigo.x()>posTorre.x() && posEnemigo.y()>posTorre.y()){
        spriteY=0;
        sprietX=1;
    }
    else if(posEnemigo.x()<posTorre.x() && posEnemigo.y()>posTorre.y()){
        spriteY=120;
        sprietX=3;
    }
    else if(posEnemigo.x()>posTorre.x() && posEnemigo.y()<posTorre.y()){
        spriteY=0;
        sprietX=3;
    }
}


//----------------------------------------Getters and Setters-------------------------------------//
int Tower::getNivel() const{return nivel;}
void Tower::setNivel(int value){nivel += value;}
QGraphicsPolygonItem *Tower::getAttack_area() const {return attack_area;}
int Tower::getVelocidad() const {return velocidad;}
QTimer *Tower::getTimer() const {return timer;}
int Tower::getSCALE_FACTOR() const {return SCALE_FACTOR;}
void Tower::setVelocidad(int value){velocidad += value;}
QPixmap Tower::getSprite() const{return sprite;}
void Tower::setSprite(const QPixmap &value){sprite = value;}
QPixmap Tower::getSheet() const {return sheet;}
int Tower::getTipo() const{return tipo;}
void Tower::setTipo(int value){tipo = value;}
void Tower::setSheet(const QPixmap &value) {
    sheet = value;
    setPixmap(QPixmap(sheet.copy(sprietX*120, spriteY, 120, 118)).scaled(68,75));
}