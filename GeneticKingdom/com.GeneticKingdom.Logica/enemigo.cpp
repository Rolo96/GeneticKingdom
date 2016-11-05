#include "enemigo.h"
#include "../com.GeneticKingdom.UI/juego.h"

using namespace std;

/**
 * Constructor de la clase enemigo
 * @param pVelocidad: Velocidad del enemigo
 * @param pResA: Resistencia a los proyectiles de fuego
 * @param pResB: Resistencia a los proyectiles tipo flecha
 * @param pResC: Resistencia a los proyectiles tipo bala
 * @param pVida: Vida del enemigo
 * @param pTipo: Tipo de enemigo
 * @param pJuego: Instancia de juego hecha
 * @return Enemigo creado
 */
Enemigo::Enemigo(int pVelocidad, int pResA, int pResB, int pResC, int pVida, int pTipo, Juego &pJuego,int pMutado)
        : juego(pJuego), tipo(pTipo), vida(pVida), velocidad(pVelocidad),
          resA(pResA), resB(pResB), resC(pResC) {

    ruta = *new List<QPoint>();

    //Fitness del enemigo
    fitness=(pVelocidad+pResA+pResB+pResC+pVida)/5;


    //Asignación de imagen dependiendo del tipo de enemigo
    if(tipo==0){
        juego.setMachoFit(fitness);
        if(pMutado==1){
            juego.setMutaciones(1);
            sheet = QPixmap("/home/raulaq/ClionProjects/GeneticKingdom/Imagenes/MachoMutado.png");
        }else{
            sheet = QPixmap("/home/raulaq/ClionProjects/GeneticKingdom/Imagenes/Macho.png");
        }
    }
    else if(tipo==1){
        if(pMutado==1){
            juego.setMutaciones(1);
            sheet = QPixmap("/home/raulaq/ClionProjects/GeneticKingdom/Imagenes/MercenarioMutado.png");
        }else{
            sheet = QPixmap("/home/raulaq/ClionProjects/GeneticKingdom/Imagenes/Mercenario.png");
        }
    }
    else if(tipo==2){
        if(pMutado==1){
            juego.setMutaciones(1);
            sheet = QPixmap("/home/raulaq/ClionProjects/GeneticKingdom/Imagenes/PelirrojaMutado.png");
        }else{
            sheet = QPixmap("/home/raulaq/ClionProjects/GeneticKingdom/Imagenes/Pelirroja.png");
        }
    }
    else {
        if(pMutado==1){
            juego.setMutaciones(1);
            sheet = QPixmap("/home/raulaq/ClionProjects/GeneticKingdom/Imagenes/RobotMutado.png");
        }else{
            sheet = QPixmap("/home/raulaq/ClionProjects/GeneticKingdom/Imagenes/Robot.png");
        }
    }
    sprite = sheet.copy(0, 138, 33, 69);
    setPixmap(sprite);

    //Tareas necesarios para que el enemigo realice sus movimientos
    temporizador = new QTimer();
    connect(temporizador,SIGNAL(timeout()),this,SLOT(mover()));
    QTimer *temporizador2 = new QTimer();
    connect(temporizador2,SIGNAL(timeout()),this,SLOT(animar()));
    temporizador2->start(50+velocidad*3);

}

/**
 * Destructor de la clase
 */
Enemigo::~Enemigo(){}

/**
 * Método para realizar animación del enemigo
 */
void Enemigo::animar() {
    setPixmap(QPixmap(sheet.copy(index*53, mY, 33, 69)));
    if(flag){
        if(index==2){flag=false;index=index-2;}index++;
    }else{
        if(index==0){flag=true;index=index+2;}index--;
    }
}

/**
 * Método para mover al enemigo
 */
void Enemigo::mover(){
    if(mY==0){
        setPos(x(), y()+2);
        if(this->y()>=posY){
            i++;
            setOrientacion();
        }
    }
    else if(mY==69){
        setPos(x()-2, y());
        if(this->x()<=posX){
            i++;
            setOrientacion();
        }
    }
    else if(mY==138){
        setPos(x()+2, y());
        if(this->x()>=posX){
            i++;
            setOrientacion();
        }
    }
    else if(mY==207){
        setPos(x(), y()-2);
        if(this->y()<=posY){
            i++;
            setOrientacion();
        }
    }
    if(this->x()>1280){
        juego.matar(this,0);
    }
}

/**
 * Método para modificar la ruta del enemigo al poder una torre
 * @param pRuta: nueva ruta
 */
void Enemigo::setRuta(List<QPoint> pRuta){
    i=-1;
    ruta=pRuta;
}

/**
 * Método para cambiar la orientación del enemigo cuando cambia de dirección
 */
void Enemigo::setOrientacion(){
    if(i<ruta.get_size()-1){
        if(ruta.get_Node(i)->get_data().x()!=ruta.get_Node(i+1)->get_data().x()){
            //Dirección abajo
            if(ruta.get_Node(i)->get_data().x()<ruta.get_Node(i+1)->get_data().x()){
                mY=0;
                posY=ruta.get_Node(i+1)->get_data().x()*68;
                posX=(ruta.get_Node(i+1)->get_data().y())*68+128;
            }
            //Dirección arriba
            else{
                mY=207;
                posY=ruta.get_Node(i+1)->get_data().x()*68;
                posX=(ruta.get_Node(i+1)->get_data().y())*68+128;
            }
        }
        else{
            //Dirección derecha
            if(ruta.get_Node(i)->get_data().y()<ruta.get_Node(i+1)->get_data().y()){
                mY=138;
                posY=ruta.get_Node(i+1)->get_data().x()*68;
                posX=(ruta.get_Node(i+1)->get_data().y())*68+128;
            }
            //Dirección izquierda
            else{
                mY=69;
                posY=ruta.get_Node(i+1)->get_data().x()*68;
                posX=(ruta.get_Node(i+1)->get_data().y())*68+128;
            }
        }
    }
    else{mY=138;}
}

/**
 * Método que inicia la tarea para que el enemigo camine
 */
void Enemigo::correr(){temporizador->start((int) (40 - ((velocidad - 1) * 0.75)));}


//---------------------------------Getters and Setters------------------------------//
int Enemigo::getPosX(){return posX;}
int Enemigo::getPosY(){return posY;}
int Enemigo::getMy(){return mY;}
int Enemigo::getVida(){return vida;}
int Enemigo::getFitness() const{return fitness;}
int Enemigo::getResC() const{return resC;}
int Enemigo::getResB() const{return resB;}
int Enemigo::getResA() const{return resA;}
void Enemigo::setVida(int pVida){vida+=pVida;}
