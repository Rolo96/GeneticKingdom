#include "juego.h"
#include <QMessageBox>
#include "../com.GeneticKingdom.Red/httpconection.cpp"
#include <QSound>
using namespace std;

/**
 * Constructor de la clase juego
 * @return instancia de juego
 */
Juego::Juego(){
    //Definimos características del View juego
    inicioX=110;
    finX=1208;
    anchoX=68;
    inicioY=0;
    anchoY=68;
    construir=false;
    cursor=nullptr;
    path = new Pathfinding();
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1280,680);
    setScene(scene);
    QPixmap pix("/home/raulaq/ClionProjects/GeneticKingdom/Imagenes/Mapa.png");
    scene->addPixmap(pix);
    setFixedSize(1280,680);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    postButton = new QPushButton("POST", this);
    postButton->setGeometry(QRect(QPoint(100, 100),
                                QSize(60, 30)));
    postButton->move(10,260);
    postButton->setStyleSheet("background-color: green");
    connect(postButton, SIGNAL (released()), this, SLOT (cambiarTamano()));

    txt=new QTextEdit(this);
    txt->setGeometry(10,220,60,30);

    datosParseados = * new Array<Array<int>>();
    setMouseTracking(true);

    //Tareas necesarios que el juego debe realizar como solicitar y crear enemigos
    temporizador = new QTimer();
    temporizador2 = new QTimer();
    connect(temporizador,SIGNAL(timeout()),this,SLOT(crearEnemigos()));
    connect(temporizador2,SIGNAL(timeout()),this,SLOT(solicitarEnemigos()));
    temporizador2->start(4000);

    //Datos estadísticos
    Oro = 500;
    itemOro = new QGraphicsTextItem(QString::number(Oro));
    itemOro->setDefaultTextColor(Qt::white);
    itemOro->setPos(50,635);
    itemOro->setFont(QFont("Algerian", 15, QFont::Bold));
    scene->addItem(itemOro);

    itemGeneraciones = new QGraphicsTextItem("Generaciones: "+QString::number(generaciones));
    itemGeneraciones->setDefaultTextColor(Qt::black);
    itemGeneraciones->setPos(150,635);
    itemGeneraciones->setFont(QFont("Algerian", 10, QFont::Bold));
    scene->addItem(itemGeneraciones);

    itemMuertes = new QGraphicsTextItem("Enemigos eliminados: "+QString::number(muertos));
    itemMuertes->setDefaultTextColor(Qt::black);
    itemMuertes->setPos(300,635);
    itemMuertes->setFont(QFont("Algerian", 10, QFont::Bold));
    scene->addItem(itemMuertes);

    itemMutaciones = new QGraphicsTextItem("Mutaciones transcurridas: "+QString::number(mutaciones));
    itemMutaciones->setDefaultTextColor(Qt::black);
    itemMutaciones->setPos(500,635);
    itemMutaciones->setFont(QFont("Algerian", 10, QFont::Bold));
    scene->addItem(itemMutaciones);

    itemMachoFit = new QGraphicsTextItem("Fitness Macho: "+QString::number(machoFit));
    itemMachoFit ->setDefaultTextColor(Qt::black);
    itemMachoFit ->setPos(730,635);
    itemMachoFit ->setFont(QFont("Algerian", 10, QFont::Bold));
    scene->addItem(itemMachoFit);

    //Coloca iconos de las torres en la esquima superior izquierda de la pantalla
    for(int i=1;i<4;i++){
        torres = new QGraphicsPixmapItem();
        sheet = QPixmap("/home/raulaq/ClionProjects/GeneticKingdom/Imagenes/torre"+QString::number(i)+"0.png");
        sprite = sheet.copy(0, 0, 120, 118).scaled(68,75);
        torres->setPixmap(sprite);
        scene->addItem(torres);
        torres->setPos(0,(i-1)*75);
    }
}

/**
 * Método para que al presionar un icono de una torre la imagen de esta siga al cursor a la posición donde
 * se va a crear
 * @param filename: Imagen de torre que debe aparecer junto al cursor
 * @param pos: Posición del cursor, donde debe aparecer el icono
 */
void Juego::setCursor(QString filename,QPointF pos){
    construir=true;
    cursor = new QGraphicsPixmapItem();
    sheet = QPixmap(filename);
    sprite = sheet.copy(0, 0, 120, 118).scaled(68,75);
    cursor->setPixmap(sprite);
    scene->addItem(cursor);
    cursor->setPos(pos.x(),pos.y());
}

/**
 * Método para que el icono siga al cursor cuando se mueve
 * @param event: evento de movimiento
 */
void Juego::mouseMoveEvent(QMouseEvent *event){
    if(construir){
        cursor->setPos(event->pos());
    }
}

/**
 * Método para realizar diferentes acciones cuando se presiona click, ya se izquierdo o derecho
 * @param event: evento de presionar
 */
void Juego:: mousePressEvent ( QMouseEvent * event ){
    QPointF punto = convertirCuadricula(event->pos());
    if(construir){
        mConstruir(event,punto);
    }else{
        asinarIcono(event);
        if(event->button() == Qt::RightButton){
            clickDerecho(event,punto);
        }
    }
}

/**
 * Método para asignar icono al cursor cuando se da click en algún icono
 * @param event: evento del click
 */
void Juego::asinarIcono(QMouseEvent *event){
    if(event->pos().x()<68 && event->pos().y()<75){
        setCursor("/home/raulaq/ClionProjects/GeneticKingdom/Imagenes/torre10.png",event->pos());
        tipo=1;
    }else if(event->pos().x()<68 && (event->pos().y()<150 && event->pos().y()>75)){
        setCursor("/home/raulaq/ClionProjects/GeneticKingdom/Imagenes/torre20.png",event->pos());
        tipo=2;
    }else if(event->pos().x()<68 && (event->pos().y()<225 && event->pos().y()>150)){
        setCursor("/home/raulaq/ClionProjects/GeneticKingdom/Imagenes/torre30.png",event->pos());
        tipo=3;
    }
}

/**
 * Método para realizar upgrades o vender torres al dar click derecho
 * @param event: evento del click
 * @param punto: punto de matriz respectivo al click
 */
void Juego::clickDerecho(QMouseEvent *event,QPointF punto){
    if(path->grid[static_cast<int>(punto.y())][static_cast<int>(punto.x())]==0){
        QMessageBox msgBox;
        msgBox.addButton(tr("Upgrade"), QMessageBox::ActionRole);
        msgBox.addButton(tr("Sale"), QMessageBox::ActionRole);
        int button=msgBox.exec();

        if(button==0){
            QPointF puntoTorre;
            QPointF puntoEvento = convertirCuadricula(event->pos());
            for(int i=0;i<scene->items().size();i++){
                Tower * tower = dynamic_cast<Tower *>(scene->items()[i]);
                if(tower){
                    puntoTorre = convertirCuadricula(tower->pos());
                    if (puntoTorre.x()==puntoEvento.x() && puntoTorre.y()==puntoEvento.y()){
                        if(tower->getNivel()<3){
                            if(Oro>=50){
                                upgradeTorre(tower);
                                tower->setNivel(1);
                                actualizarOro(-50);
                            }else{
                                QMessageBox msgBox2;
                                msgBox2.setText("Oro insuficiente");
                                msgBox2.exec();
                            }
                        }else{
                            QMessageBox msgBox1;
                            msgBox1.setText("No se pueden hacer más upgrades");
                            msgBox1.exec();
                        }
                    }
                }
            }
        }else{
            QPointF puntoTorre;
            QPointF puntoEvento = convertirCuadricula(event->pos());
            for(int i=0;i<scene->items().size();i++){
                Tower * tower = dynamic_cast<Tower *>(scene->items()[i]);
                if(tower){
                    puntoTorre = convertirCuadricula(tower->pos());
                    if (puntoTorre.x()==puntoEvento.x() && puntoTorre.y()==puntoEvento.y()){
                        borrarTorre(tower);
                        path->grid[static_cast<int>(puntoEvento.y())][static_cast<int>(puntoEvento.x())]=1;
                    }
                }
            }
            actualizarOro(100);
        }
    }
}

/**
 * Método para construir una torre al hacer click
 * @param event: evento del click
 * @param punto: punto clickeado
 */
void Juego::mConstruir(QMouseEvent *event,QPointF punto){
    if(event->button() == Qt::LeftButton)
    {
        if (punto.x()!=-1 && permitirTorre(punto)){
            punto = convertirPunto(punto);
            Tower * tower = new Tower(*this, sheet, tipo);
            scene->addItem(tower);
            if(tipo==1){
                actualizarOro(-150);
            }else if(tipo==2){
                actualizarOro(-100);
            }else{
                actualizarOro(-200);
            }
            tower->setPos(punto);
            //qDebug()<<punto;
            for(int i=0;i<scene->items().size();i++){
                Enemigo * enemy = dynamic_cast<Enemigo *>(scene->items()[i]);
                if (enemy){
                    QPointF puntoCreacion;
                    puntoCreacion.setX(enemy->getPosX());
                    puntoCreacion.setY(enemy->getPosY());
                    enemy->setRuta(findPath(convertirCuadricula(puntoCreacion)));
                }
            }
            construir=false;
            delete cursor;
            cursor=nullptr;
            tipo=0;
        }else if(event->pos().x()<68 && event->pos().y()<75){
            construir=false;
            delete cursor;
            cursor=nullptr;
            tipo=0;
        }else if(event->pos().x()<68 && (event->pos().y()<150 && event->pos().y()>75)){
            construir=false;
            delete cursor;
            cursor=nullptr;
            tipo=0;
        }else if(event->pos().x()<68 && (event->pos().y()<225 && event->pos().y()>150)){
            construir=false;
            delete cursor;
            cursor=nullptr;
            tipo=0;
        }
    }
}

/**
 * Convierte de punto de matriz a punto en pixeles
 * @param punto: punto de matriz a convertir
 * @return: punto en pixeles equivalente a punto de matriz
 */
QPointF Juego::convertirPunto(QPointF punto){
    QPoint puntoCreacion;
    puntoCreacion.setX((int) (punto.x() * anchoX + inicioX));
    puntoCreacion.setY((int) (punto.y() * anchoY + inicioY));
    return puntoCreacion;
}

/**
 * Convierte de punto en pixeles a punto de matriz
 * @param punto: punto en pixeles a convertir
 * @return: punto de matriz equivalente a punto en pixeles
 */
QPointF Juego::convertirCuadricula(QPointF punto){
    if(punto.x()>=inicioX && punto.x()<=finX-anchoX){
        int posx;
        int posy;
        posx= (int) ((-inicioX + punto.x()) / anchoX);
        posy= (int) ((inicioY + punto.y()) / anchoY);
        QPointF puntoCreacion;
        puntoCreacion.setX(posx);
        puntoCreacion.setY(posy);
        return puntoCreacion;
    }
    else{
        QPointF puntoCreacion;
        puntoCreacion.setX(-1);
        puntoCreacion.setY(-1);
        return puntoCreacion;
    }
}

/**
 * Método para encontrar el camino hacia la salida
 * @param pos: posición en la que está el enemigo que desea encontrar su ruta a la salida
 * @return: camino a la salida
 */
List<QPoint> Juego:: findPath(QPointF pos){
    return path->trazar(pos);
}

/**
 * Método para averiguar si al crear una torre nueva no se obstruye totalmente el camino
 * @param pos: posición en la que se va a crear la torre
 * @return: true: no hay camino, false: hay camino
 */
bool Juego::noHayCamino(QPointF pos){
    path->grid[static_cast<int>(pos.y())][static_cast<int>(pos.x())]=0;
    List<QPoint> puntos;
    QPointF punto;
    punto.setX(0);
    punto.setY(6);
    puntos=path->trazar(punto);
    path->grid[static_cast<int>(pos.y())][static_cast<int>(pos.x())]=1;
    return puntos.get_Node(0)->get_data().x()==-1;
}

/**
 * Método para verificar si se puede crear una torre cuando se está en modo "construcción" y el jugador
 * da click en la alguna posición del mapa, o si se tiene suficiente oro para hacerla
 * @param pos: posición en la que clickeo
 * @return: true: permite hacer la torre, false: no permite la creación de la torre
 */
bool Juego::permitirTorre(QPointF pos){
    QPointF puntoTorre;
    puntoTorre.setX(pos.x());
    puntoTorre.setY(pos.y());
    if(path->grid[static_cast<int>(pos.y())][static_cast<int>(pos.x())]==0){
        return false;
    }
    else if(Oro>=0){
        if(tipo==1 && Oro<150){
           QMessageBox msgBox;
           msgBox.setText("Oro insuficiente");
           msgBox.exec();
           return false;
        }else if(tipo==2 && Oro<100){
            QMessageBox msgBox;
            msgBox.setText("Oro insuficiente");
            msgBox.exec();
            return false;
        }else if(tipo==3 && Oro<200){
            QMessageBox msgBox;
            msgBox.setText("Oro insuficiente");
            msgBox.exec();
            return false;
        }
    }
    else if(noHayCamino(pos)){
       return false;
    }
    for(int i=0;i<scene->items().size();i++){
        Enemigo * enemy = dynamic_cast<Enemigo *>(scene->items()[i]);
        if (enemy){
            QPointF puntoCreacion;
            puntoCreacion.setX(enemy->x());
            puntoCreacion.setY(enemy->y());
            int mY=enemy->getMy();
            puntoCreacion=convertirCuadricula(puntoCreacion);
            if(puntoCreacion==pos){
                return false;
            }
            else if(mY==0){
                pos.setY(pos.y()-1);
                if(puntoCreacion==pos){
                    return false;
                }
                pos.setY(pos.y()+1);
            }
            else if(mY==207){
                pos.setY(pos.y()+1);
                if(puntoCreacion==pos){
                    return false;
                }
                pos.setY(pos.y()-1);
            }
            else if(mY==69){
                pos.setX(pos.x()+1);
                if(puntoCreacion==pos){
                    return false;
                }
                pos.setX(pos.x()-1);
            }
            else if(mY==138){
                pos.setX(pos.x()-1);
                if(puntoCreacion==pos){
                    return false;
                }
                pos.setX(pos.x()+1);
            }
        }
    }
    //qDebug()<<pos;
    path->grid[static_cast<int>(pos.y())][static_cast<int>(pos.x())]=0;
    return true;
}

/**
 * Método para matar a un enemigo cuando se le acaba la vida o se sale de la pantalla
 * @param enemigo: enemigo a eliminar
 * @param estado: determina si el enemigo fue matado por una torre o se salió de la pantalla
 */
void Juego::matar(Enemigo* enemigo, int estado){
    scene->removeItem(enemigo);
    if (estado==1){
        QSound::play("/home/raulaq/ClionProjects/GeneticKingdom/Sonidos/gritohombre.wav");
        if(enemigo->getFitness()>=0 && enemigo->getFitness()<=10){
            actualizarOro(10);
        }else if(enemigo->getFitness()>10 && enemigo->getFitness()<=20){
            actualizarOro(20);
        }else if(enemigo->getFitness()>20 && enemigo->getFitness()<=30){
            actualizarOro(30);
        }else{
            actualizarOro(40);
        }
        muertos++;
        itemMuertes->setPlainText("Enemigos eliminados: "+QString::number(muertos));
    }
    delete enemigo;
}

/**
 * Método de borrar bala al colisionar con enemigo o salir de pantalla
 * @param bala: bala a eliminar
 */
void Juego::borrarBala(Bala* bala){
    scene->removeItem(bala);
    delete bala;
}

/**
 * Método pata eliminar torre al venderla
 * @param torre: torre a eliminar
 */
void Juego::borrarTorre(Tower* torre){
    scene->removeItem(torre);
    delete torre;
}

/**
 * Método que realiza el upgrade de las torres
 * @param torre: torre a la que se va a realizar upgrade
 */
void Juego::upgradeTorre(Tower* torre){
    torre->setSheet(QPixmap("/home/raulaq/ClionProjects/GeneticKingdom/Imagenes/torre"
                            +QString::number(torre->getTipo())+QString::number(torre->getNivel()+1)+".png"));
    torre->setVelocidad(-30);
    torre->getTimer()->setInterval(torre->getVelocidad());
}

/**
 * Método para modificar oro
 * @param valor: valor que se desea sumar al oro
 */
void Juego::actualizarOro(int valor) {
    Oro +=valor;
    itemOro->setPlainText(QString::number(Oro));
}

/**
 * Método para crear enemigos
 */
void Juego::crearEnemigos(){
    if (numeroEnemigo<datosParseados.get_size()){
        Enemigo * enemigo = new Enemigo(datosParseados.get_data(numeroEnemigo).get_data(0),
                                        datosParseados.get_data(numeroEnemigo).get_data(1),
                                        datosParseados.get_data(numeroEnemigo).get_data(2),
                                        datosParseados.get_data(numeroEnemigo).get_data(3),
                                        datosParseados.get_data(numeroEnemigo).get_data(4),
                                        datosParseados.get_data(numeroEnemigo).get_data(5), *this,
                                        datosParseados.get_data(numeroEnemigo).get_data(6));
        scene->addItem(enemigo);
        enemigo->setPos(110,408);
        enemigo->setRuta(findPath(convertirCuadricula(enemigo->pos())));
        enemigo->setPos(110,408);
        enemigo->correr();
        numeroEnemigo++;
    }
    else{
        temporizador->stop();
        temporizador2->start(3000);
    }

}

/**
 * Método para solicitar enemigos al servidor
 */
void Juego::solicitarEnemigos(){
    solicitarPoblacion();
    numeroEnemigo=0;
    temporizador->start(3000);
    temporizador2->stop();
    generaciones++;
    itemGeneraciones->setPlainText("Generaciones: "+QString::number(generaciones));
}

/**
 * Solicita al rest que cambie el tamaño de la poblacion
 */
void Juego::cambiarTamano(){
    QString texto = txt->toPlainText();
    bool numerico=true;
    int number=0;
    for (int var = 0; var < texto.length(); ++var) {
        if (texto.at(var).isDigit()){
            number += texto.at(var).digitValue()*pow(10,texto.length()-var-1);

        }
        else{
            numerico=false;
        }
    }
    qDebug()<<number;
    cambiarTamanoP(number);
}

void Juego::setMutaciones(int pMutaciones) {
    mutaciones += pMutaciones;
    itemMutaciones->setPlainText("Mutaciones transcurridas: "+QString::number(mutaciones));
}

void Juego::setMachoFit(int fit) {
    if(machoFit<fit){
        machoFit=fit;
        itemMachoFit->setPlainText("Fitness Macho: "+QString::number(machoFit));
    }
}