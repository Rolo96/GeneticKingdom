//
// Created by bryan on 04/09/16.
//

#ifndef DATASTRUCTURES_ARRAY_H
#define DATASTRUCTURES_ARRAY_H
#include <iostream>

using namespace std;

template <class T>
class Array{
public:
    Array();
    int get_size();
    void resize(T*);
    void insert(T);
    void edit(int,T);
    void remove(int);
    void show_array();
    T get_data(int);
    T get_last();
    T get_first();
    int get_index() const;

private:
    int _size;
    int _index;
    T* _array;
};




#endif //DATASTRUCTURES_ARRAY_H
