#ifndef DATASTRUCTURES_ARRAY_H
#define DATASTRUCTURES_ARRAY_H
#include <iostream>
using namespace std;

/**
 * Clase que genera arreglos geneticos
 */
template <class T>
class Array{
public:
    Array();
    int get_size();
    void resize(T*);
    void insert(T);
    T get_data(int);

private:
    int _size;
    int _index;
    T* _array;
};

#endif //DATASTRUCTURES_ARRAY_H