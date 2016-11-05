#include "../com.GeneticKingdom.Logica/Pathfinding.h"
#include "../com.GeneticKingdom.EstructurasDatos/List.cpp"


/**
 * Constructor por defecto
 */
Pathfinding::Pathfinding(){}


struct Pathfinding:: cell{int parent_i, parent_j;double f, g, h;};

/**
 * Verifica si la poscion dada se encuentra dentro de la matriz
 */
bool Pathfinding::posValida(int row, int col){
    return (row >= 0) && (row < ROW) &&
           (col >= 0) && (col < COL);
}

/**
 * Verifica si una posicion se enecuentra desbloqueada
 * @param grid matriz
 * @param row fila
 * @param col columna
 * @return boolean que indica si esta desbloqueada o no la celda
 */
bool Pathfinding::estaDesbloqueado(int grid[][COL], int row, int col){
    return 1 == grid[row][col];
}

/**
 * Verifica si ya llego a su destino
 * @param row fila
 * @param col columna
 * @param dest destino
 * @return boolean que indica si llego o no al destino
 */
bool Pathfinding:: esDestino(int row, int col, Pair destino){
    return row == destino.first && col == destino.second;
}

/**
 * Prepara las variables para trazar la ruta para llegar al destino
 * @param pos posicion desde donde trazar la ruta
 * @return una lista que contiene la ruta
 */
List<QPoint> Pathfinding:: trazar(QPointF pos){
    Pair posicion = make_pair(pos.y(),pos.x());
    Pair destino = make_pair(6, 15);
    return trazarCamino(grid, posicion, destino);
}

/**
 * Clacula el valor del movimiento
 * @param row fila
 * @param col columna
 * @param destino destino
 * @return valor del movimiento
 */
double Pathfinding::valorMovimiento(int row, int col, Pair destino){
    return sqrt ((row - destino.first) * (row - destino.first)
                 + (col-destino.second)*(col-destino.second));
}

/**
 * Guarda el camino de la ruta en una lista de punos que son los puntos por donde debe pasar ele enemigo
 * @param cellDetails matriz del mapa
 * @param destino destino
 * @param pPuntos lista de puntos
 */
void Pathfinding::guardarCamino(cell cellDetails[][COL], Pair destino, List<QPoint>* pPuntos){
    int row = destino.first;
    int col = destino.second;
    stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col ))
    {
        Path.push (make_pair (row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    QPoint puntoCreacion;
    Path.push (make_pair (row, col));
    while (!Path.empty())
    {
        pair<int,int> p = Path.top();
        Path.pop();
        puntoCreacion.setX(p.first);
        puntoCreacion.setY(p.second);
        pPuntos->add_end(puntoCreacion);
    }
    return;
}

/**
 * Algoritmo A* traza la ruta
 * @param grid matriz del mapa
 * @param pos posicion donde se enccuentra el enemigo
 * @param dest destino
 * @return la ruta si hay camino o una ruta de error si no lo hay
 */
List<QPoint> Pathfinding:: trazarCamino(int grid[][COL], Pair pos, Pair destino)
{
    List<QPoint> puntos;
    List<QPoint> fail;//No hay camino
    QPoint punto;
    punto.setX(-1);
    punto.setY(-1);
    fail.add_end(punto);

    //Verifica que la posicion sea vallida
    if (!posValida (pos.first, pos.second)) {return fail;}

    // Verifica que el destino sea valido
    if (!posValida (destino.first, destino.second)) {return fail;}

    //Si el destino no esta bloqueado
    if (!estaDesbloqueado(grid, destino.first, destino.second) || !estaDesbloqueado(grid, pos.first, pos.second))
    {return fail;}

    //Si ya esta en el destino
    if (esDestino(pos.first, pos.second, destino)) {return fail;}

    bool closedList[ROW][COL];
    memset(closedList, false, sizeof (closedList));
    cell cellDetails[ROW][COL];
    int i, j;

    for (i=0; i<ROW; i++)
    {
        for (j=0; j<COL; j++)
        {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    i = pos.first, j = pos.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;
    set<pPair> openList;
    openList.insert(make_pair (0.0, make_pair (i, j)));
    while (!openList.empty())
    {
        pPair p = *openList.begin();
        openList.erase(openList.begin());
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;
        double gNew, hNew, fNew;

        //---------Movimiento al norte------------
        if (posValida(i - 1, j))
        {
            if (esDestino(i - 1, j, destino))
            {
                cellDetails[i-1][j].parent_i = i;
                cellDetails[i-1][j].parent_j = j;
                guardarCamino (cellDetails, destino,&puntos);
                return puntos;
            }
            else if (!closedList[i - 1][j] && estaDesbloqueado(grid, i - 1, j))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = valorMovimiento (i-1, j, destino);
                fNew = gNew + hNew;
                if (cellDetails[i-1][j].f == FLT_MAX ||
                    cellDetails[i-1][j].f > fNew)
                {
                    openList.insert( make_pair(fNew,
                                               make_pair(i-1, j)));

                    cellDetails[i-1][j].f = fNew;
                    cellDetails[i-1][j].g = gNew;
                    cellDetails[i-1][j].h = hNew;
                    cellDetails[i-1][j].parent_i = i;
                    cellDetails[i-1][j].parent_j = j;
                }
            }
        }

        //--------Movimiento al sur-----------
        if (posValida(i + 1, j))
        {
            if (esDestino(i + 1, j, destino))
            {
                cellDetails[i+1][j].parent_i = i;
                cellDetails[i+1][j].parent_j = j;
                guardarCamino(cellDetails, destino, &puntos);
                return puntos;
            }
            else if (!closedList[i + 1][j] && estaDesbloqueado(grid, i+1, j))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = valorMovimiento(i+1, j, destino);
                fNew = gNew + hNew;
                if (cellDetails[i+1][j].f == FLT_MAX ||
                    cellDetails[i+1][j].f > fNew)
                {
                    openList.insert( make_pair (fNew, make_pair (i+1, j)));
                    cellDetails[i+1][j].f = fNew;
                    cellDetails[i+1][j].g = gNew;
                    cellDetails[i+1][j].h = hNew;
                    cellDetails[i+1][j].parent_i = i;
                    cellDetails[i+1][j].parent_j = j;
                }
            }
        }

        //---------Movimiento al este----------------------
        if (posValida (i, j+1) == true)
        {
            if (esDestino(i, j+1, destino) == true)
            {
                cellDetails[i][j+1].parent_i = i;
                cellDetails[i][j+1].parent_j = j;
                guardarCamino(cellDetails, destino, &puntos);
                return puntos;
            }
            else if (closedList[i][j+1] == false &&
                    estaDesbloqueado (grid, i, j+1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = valorMovimiento (i, j+1, destino);
                fNew = gNew + hNew;
                if (cellDetails[i][j+1].f == FLT_MAX ||
                    cellDetails[i][j+1].f > fNew)
                {
                    openList.insert( make_pair(fNew,
                                               make_pair (i, j+1)));
                    cellDetails[i][j+1].f = fNew;
                    cellDetails[i][j+1].g = gNew;
                    cellDetails[i][j+1].h = hNew;
                    cellDetails[i][j+1].parent_i = i;
                    cellDetails[i][j+1].parent_j = j;
                }
            }
        }

        // -----------------Movimiento al oeste---------------------
        if (posValida(i,j-1))
        {
            if (esDestino(i, j-1, destino) == true)
            {
                cellDetails[i][j-1].parent_i = i;
                cellDetails[i][j-1].parent_j = j;
                guardarCamino(cellDetails, destino, &puntos);
                return puntos;
            }
            else if (closedList[i][j-1] == false &&
                    estaDesbloqueado(grid, i, j-1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = valorMovimiento(i, j-1, destino);
                fNew = gNew + hNew;
                if (cellDetails[i][j-1].f == FLT_MAX ||
                    cellDetails[i][j-1].f > fNew)
                {
                    openList.insert( make_pair (fNew,
                                                make_pair (i, j-1)));
                    cellDetails[i][j-1].f = fNew;
                    cellDetails[i][j-1].g = gNew;
                    cellDetails[i][j-1].h = hNew;
                    cellDetails[i][j-1].parent_i = i;
                    cellDetails[i][j-1].parent_j = j;
                }
            }
        }
    }
    return fail;

}
