#include <QApplication>
#include "../com.GeneticKingdom.UI/juego.h"

/**
 * Clase inicial que instancia el juego
 * @param argc parametro por defecto
 * @param argv parametro por defecto
 * @return la ejecucion de la app
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Juego * juego = new Juego();
    juego->show();
    return a.exec();
}
