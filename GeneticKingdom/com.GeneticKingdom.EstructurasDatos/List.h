#ifndef DATASTRUCTURES_LIST_H
#define DATASTRUCTURES_LIST_H

#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "Node.h"
#include "Node.cpp"

using namespace std;

template <class T>
class List {
public:
    List();
    ~List();
    int get_size();
    void add_end(T);
    Node<T> *get_Node(int) const;

private:
    Node<T> *_head;
    int _size;
};

#endif //DATASTRUCTURES_LIST_H
