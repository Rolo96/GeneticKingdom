//
// Created by bryan on 04/09/16.
//
#include "Node.h"

// Constructor por defecto
template<typename T>
Node<T>::Node()
{
    _data = NULL;
    _next = NULL;
    _prev = NULL;
}

// Constructor por parámetro
template<typename T>
Node<T>::Node(T pData)
{
    _data = pData;
    _next = NULL;
    _prev = NULL;
}

template<typename T>
T Node<T>::get_data() const {
    cout<<_data;
    return _data;
}

template<typename T>
void Node<T>::set_data(T pData) {
    Node<T>::_data = pData;
}

template<typename T>
Node<T> *Node<T>::get_next() const {
    return _next;
}

template<typename T>
void Node<T>::set_next(Node<T>* pNext) {
    Node<T>::_next = pNext;
}

template<typename T>
Node<T> *Node<T>::get_prev() const {
    return _prev;
}

template<typename T>
void Node<T>::set_prev(Node<T> *_prev) {
    Node<T>::_prev = _prev;
}

template<typename T>
Node<T>::~Node() {}

