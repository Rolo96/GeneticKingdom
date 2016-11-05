#ifndef DATASTRUCTURES_NODE_H
#define DATASTRUCTURES_NODE_H

#include <iostream>

using namespace std;

/**
 * Clase que crea los nodos de la lista
 */
template <class T>
class Node
{
public:
    Node();
    Node(T);
    ~Node();
    T get_data() const;
    void set_data(T _data);
    Node *get_next() const;
    void set_next(Node *_next);
    Node *get_prev() const;
    void set_prev(Node *_prev);

private:
    Node* _next;
    Node* _prev;
    T _data;
};

#endif //DATASTRUCTURES_NODE_H