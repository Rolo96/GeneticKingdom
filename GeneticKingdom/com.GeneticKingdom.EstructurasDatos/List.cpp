#include "List.h"
using namespace std;

// Constructor por defecto
template<typename T>
List<T>::List()
{
    _size = 0;
    _head = NULL;
}

/**
 * Obtiene el tamaño de la lista
 * @return tamaño de la lista
 */
template<typename T>
int List<T>::get_size() {
    return _size;
}

/**
 * Obtiene un nodo de la lista
 * @param pIndex indice del nodo
 * @return dato obtenido
 */
template<typename T>
Node<T>* List<T>::get_Node(int pIndex) const{
    if(pIndex < 0 || pIndex > _size-1){
        cout<<"Fuera de rango";
        return NULL;
    }else {
        Node<T> *tmp = _head;
        for(int i=0;i<pIndex;i++){
            tmp=tmp->get_next();
        }
        return tmp;
    }
}

/**
 * Agrega un nodo al final de la lista
 * @param data_ dato a guardar
 */
template<typename T>
void List<T>::add_end(T data_)
{
    Node<T> *new_node = new Node<T> (data_);
    Node<T> *temp = _head;

    if (_head!=NULL) {
        while (temp->get_next() != NULL) {
            temp = temp->get_next();
        }
        temp->set_next(new_node);
        new_node->set_prev(temp);

    } else {
        _head = new_node;
    }
    _size++;
}


/**
 * Destructor
 */
template<typename T>
List<T>::~List() {}
