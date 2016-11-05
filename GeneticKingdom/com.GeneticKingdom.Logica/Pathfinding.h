#ifndef PATHFINDING_H
#define PATHFINDING_H
#include<bits/stdc++.h>
#include <QPointF>
#include <QPoint>
#include "../com.GeneticKingdom.EstructurasDatos/List.h"

using namespace std;
#define ROW 10//Numero de filas
#define COL 16//Numero de columnas

/**
 * Clase que ejecuta el algoritmo de Pathfinding
 */
class Pathfinding{
public:
    Pathfinding();
    struct cell;
    int grid[ROW][COL] = //matriz que representa el mapa, 1 representa vacio, 0 ocupado
            {
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
            };
    typedef pair<int, int> Pair;
    typedef pair<double, pair<int, int>> pPair;
    bool estaDesbloqueado(int grid[][COL], int row, int col);
    bool posValida(int row, int col);
    bool esDestino(int row, int col, Pair dest);
    double valorMovimiento(int row, int col, Pair dest);
    void guardarCamino(cell cellDetails[][COL], Pair dest, List<QPoint> *pPuntos);
    List<QPoint> trazarCamino(int grid[][COL], Pair src, Pair dest);
    List<QPoint> trazar(QPointF pos);
};
#endif // PATHFINDING_H