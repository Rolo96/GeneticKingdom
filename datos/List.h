//
// Created by bryan on 04/09/16.
//

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

    bool is_empty();
    int get_size();
    void add_head(T);
    void add_end(T);
    void add_sort(T);
    void concat(List);
    void del_all();
    void del_by_data(T);
    void del_by_position(int);
    void fill_by_user(int);
    void fill_random(int);
    void intersection(List);
    void invert();
    void load_file(string);
    void print();
    void save_file(string);
    void search(T);
    void sort();
    void del_head();
    void del_tail();
    Node<T> *get_Node(int) const;
    Node<T> *get_head() const;
    void set_head(Node<T> *_head);
    Node<T> *get_tail() const;
    void set_tail(Node<T> *_tail);
    void set_size(int _size);

private:
    Node<T> *_head;
    Node<T> *_tail;
    int _size;
};

#endif //DATASTRUCTURES_LIST_H
