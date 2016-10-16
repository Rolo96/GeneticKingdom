//
// Created by bryan on 04/09/16.
//

#include "List.h"

using namespace std;

// Constructor por defecto
template<typename T>
List<T>::List()
{
    _size = 0;
    _head = NULL;
}

template<typename T>
int List<T>::get_size() {
    return _size;
}

template<typename T>
bool List<T>::is_empty() {
    return _size==0;
}

// Insertar al inicio
template<typename T>
void List<T>::add_head(T data_)
{
    Node<T>* new_node = new Node<T>(data_);
    if (_head!=NULL) {
        new_node->set_next(_head);
        _head->set_prev(new_node);
        _head = new_node;
    } else {
        _head = new_node;
        _tail = _head;
    }
    _size++;
}

// Insertar al final
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
        _tail=new_node;

    } else {
        _head = new_node;
        _tail=_head;
    }
    _size++;
}

// Insertar de manera ordenada
template<typename T>
void List<T>::add_sort(T data_)
{
    Node<T> *new_node = new Node<T> (data_);
    Node<T> *temp = _head;

    if (!_head) {
        _head = new_node;
    } else {
        if (_head->get_data() > data_) {
            new_node->set_next(_head);
            _head = new_node;
        } else {
            while ((temp->get_next() != NULL) && (temp->get_next()->get_data() < data_)) {
                temp = temp->get_next();
            }
            new_node->set_next(temp->get_next());
            temp->set_next(new_node);
        }
    }
    _size++;
}

// Concatenar a otra List
template<typename T>
void List<T>::concat(List list)
{
    Node<T> *temp2 = list._head;

    while (temp2) {
        add_end(temp2->get_data());
        temp2 = temp2->get_next();
    }
}

// Eliminar todos los nodos
template<typename T>
void List<T>::del_all()
{
    _head = NULL;//no libera el espacio???
    _tail=NULL;
    _size=0;
}

// Eliminar por _data del nodo
template<typename T>
void List<T>::del_by_data(T data_)
{
    Node<T> *temp = _head;
    Node<T> *temp1 = _head->get_next();

    int cont = 0;

    if (_head->get_data() == data_) {
        _head = temp->get_next();
    } else {
        while (temp1) {
            if (temp1->get_data() == data_) {
                Node<T> *aux_node = temp1;
                temp->set_next(temp1->get_next());
                delete aux_node;
                cont++;
                _size--;
            }
            temp = temp->get_next();
            temp1 = temp1->get_next();
        }
    }

    if (cont == 0) {
        cout << "No existe el dato " << endl;
    }
}

template<typename T>
void List<T>::del_head()
{
    Node<T> *temp = _head;
    if(_head!=NULL){
        if(_head->get_next()==NULL){
            _head=_tail=NULL;
        } else {
            _head = _head->get_next();
            _head->set_prev(NULL);
            delete temp;
        }
    }else cout<<"Empty List";
}

template<typename T>
void List<T>::del_tail()
{
    Node<T> *temp = _head;
    Node<T> *temp1 = temp->get_next();
    if(_head!=NULL){
        if(_head->get_next()==NULL){
            _head=_tail=NULL;
        } else{
            while(temp1->get_next()!=NULL){
                temp=temp->get_next();
                temp1=temp1->get_next();
            }
            _tail=temp;
            _tail->set_next(NULL);
            temp1->set_prev(NULL);
            delete temp1;
        }
    }else cout<<"Empty List";
}

template<typename T>
Node<T>* List<T>::get_Node(int pIndex) const{

    if(pIndex < 0 || pIndex > _size-1){
        cout<<"Fuera de rango";
        return NULL; // qué retorno???
    }else {
        Node<T> *tmp = _head;
        for(int i=0;i<pIndex;i++){
            tmp=tmp->get_next();
        }
        return tmp;
    }
}

// Eliminar por posición del nodo
template<typename T>
void List<T>::del_by_position(int pIndex)
{
    Node<T> *temp = _head;
    Node<T> *temp1 = temp->get_next();

    if (pIndex < 0 || pIndex > _size-1) {
        cout << "Fuera de rango " << endl;
    } else if (pIndex == 0) {
        _head = _head->get_next();
        delete temp;
    } else {
        for (int i = 1; i <= pIndex; i++) {
            if (i == pIndex) {
                if(temp1==_tail){
                    _tail=temp;
                }else{
                    (temp1->get_next())->set_prev(temp);
                }
                Node<T> *aux_node = temp1;
                temp->set_next(temp1->get_next());
                delete aux_node;
                _size--;
            }
            temp = temp->get_next();
            temp1 = temp1->get_next();
        }
    }

}

// Llenar la Lista por teclado
template<typename T>
void List<T>::fill_by_user(int dim)
{
    T ele;
    for (int i = 0; i < dim; i++) {
        cout << "Ingresa el elemento " << i + 1 << endl;
        cin >> ele;
        add_end(ele);
    }
}

// Llenar la Lista aleatoriamente para enteros
template<typename T>
void List<T>::fill_random(int dim)
{
    srand(time(NULL));
    for (int i = 0; i < dim; i++) {
        add_end(rand() % 100);
    }
}

// Usado por el método intersección
template<typename T>
void insert_sort(T a[], int size)
{
    T temp;
    for (int i = 0; i < size; i++) {
        for (int j = i-1; j>= 0 && a[j+1] < a[j]; j--) {
            temp = a[j+1];
            a[j+1] = a[j];
            a[j] = temp;
        }
    }
}

// Números que coinciden en 2 Lists
template<typename T>
void List<T>::intersection(List list_2)
{
    Node<T> *temp = _head;
    Node<T> *temp2 = list_2._head;

    // Creo otra Lista
    List intersection_list;

    int num_nodes_2 = list_2._size;
    int num_inter = 0;

    // Creo 2 vectores dinámicos
    T *v1 = new T[_size];
    T *v2 = new T[num_nodes_2];

    // Lleno los vectores v1 y v2 con los datas de la lista original y segunda lista respectivamente
    int i = 0;

    while (temp) {
        v1[i] = temp->get_data();
        temp = temp->get_next();
        i++;
    }

    int j = 0;

    while (temp2) {
        v2[j] = temp2->get_data();
        temp2 = temp2->get_next();
        j++;
    }

    // Ordeno los vectores
    insert_sort(v1, _size);
    insert_sort(v2, num_nodes_2);

    // Índice del 1er vector (v1)
    int v1_i = 0;

    // Índice del 2do vector (v2)
    int v2_i = 0;

    // Mientras no haya terminado de recorrer ambas Lists
    while (v1_i < _size && v2_i < num_nodes_2) {
        if (v1[v1_i] == v2[v2_i]) {
            intersection_list.add_end(v1[v1_i]);
            v1_i++;
            v2_i++;
            num_inter++;
        } else if (v1[v1_i] < v2[v2_i]) {
            v1_i++;
        } else {
            v2_i++;
        }
    }

    // Solo si hay alguna intersección imprimo la nueva lista creada
    if (num_inter > 0) {
        cout << "Existen " << num_inter << " intersecciones " << endl;
        intersection_list.print();
    } else {
        cout << "No hay intersección en ambas listas" << endl;
    }
}

// Invertir la lista
template<typename T>
void List<T>::invert()
{
    Node<T> *prev = NULL;
    Node<T> *next = NULL;
    Node<T> *temp = _head;

    while (temp) {
        next = temp->get_next();
        temp->set_next(prev);
        prev = temp;
        temp = next;
    }
    _head = prev;
}

// Cargar una lista desde un archivo
template<typename T>
void List<T>::load_file(string file)
{
    T line;
    ifstream in;
    in.open(file.c_str());

    if (!in.is_open()) {
        cout << "No se puede abrir el archivo: " << file << endl << endl;
    } else {
        while (in >> line) {
            add_end(line);
        }
    }
    in.close();
}

// Imprimir la Lista
template<typename T>
void List<T>::print()
{
    Node<T> *temp = _head;
    if (!_head) {
        cout << "La Lista está vacía " << endl;
    } else {
        while (temp!=NULL) {
            cout << temp->get_data()<<endl;
            temp = temp->get_next();
        }
    }
}

// Buscar el dato de un nodo
template<typename T>
void List<T>::search(T data_)
{
    Node<T> *temp = _head;
    int cont = 1;
    int cont2 = 0;

    while (temp) {
        if (temp->get_data() == data_) {
            cout << "El dato se encuentra en la posición: " << cont << endl;
            cont2++;
        }
        temp = temp->get_next();
        cont++;
    }

    if (cont2 == 0) {
        cout << "No existe el dato " << endl;
    }
    cout << endl << endl;
}

// Ordenar de manera ascendente
template<typename T>
void List<T>::sort()
{
    T temp_data;
    Node<T> *aux_node = _head;
    Node<T> *temp = aux_node;

    while (aux_node) {
        temp = aux_node;

        while (temp->get_next()) {
            temp = temp->get_next();

            if (aux_node->get_data() > temp->get_data()) {
                temp_data = aux_node->get_data();
                aux_node->set_data(temp->get_data());
                temp->set_data(temp_data);
            }
        }
        aux_node = aux_node->get_next();
    }
}

// Guardar una lista en un archivo
template<typename T>
void List<T>::save_file(string file)
{
    Node<T> *temp = _head;
    ofstream out;
    out.open(file.c_str());

    if (!out.is_open()) {
        cout << "No se puede guardar el archivo " << endl;
    } else {
        while (temp) {
            out << temp->get_data();
            out << " ";
            temp = temp->get_next();
        }
    }
    out.close();
}

template <typename T>
Node<T> *List<T>::get_head() const {
    return _head;
}

template <typename T>
void List<T>::set_head(Node<T> *_head) {
    List<T>::_head = _head;
}

template <typename T>
Node<T> *List<T>::get_tail() const {
    return _tail;
}

template <typename T>
void List<T>::set_tail(Node<T> *_tail) {
    List<T>::_tail = _tail;
}

template <typename T>
void List<T>::set_size(int _size) {
    List<T>::_size = _size;
}

template<typename T>
List<T>::~List() {}