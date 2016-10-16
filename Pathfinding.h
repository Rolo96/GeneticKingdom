#ifndef PATHFINDING_H
#define PATHFINDING_H
#include<bits/stdc++.h>
using namespace std;
#define ROW 10
#define COL 16

#endif // PATHFINDING_H
class Pathfinding{
public:
    Pathfinding();
    struct cell;
    typedef pair<int, int> Pair;
    typedef pair<double, pair<int, int>> pPair;
    bool isUnBlocked(int grid[][COL], int row, int col);
    bool isValid(int row, int col);
    bool isDestination(int row, int col, Pair dest);
    double calculateHValue(int row, int col, Pair dest);
    void tracePath(cell cellDetails[][COL], Pair dest);
    void aStarSearch(int grid[][COL], Pair src, Pair dest);
    void trazar();
};
