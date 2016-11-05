#include "Array.h"

/**
 * Costructor
 * @return arreglo creado
 */
template <typename T>
Array<T>::Array(){
    _index=0;
    _size=20;
    _array = new T[_size];
}

/**
 * Obtiene el tamaño del arreglo
 * @return tamanño del arreglo
 */
template <typename T>
int Array<T>::get_size(){
    return _index;
}

/**
 * Amplia el tamaño del arreglo
 * @param pArray arreglo a aumentar el tamaño
 */
template <typename T>
void Array<T>::resize(T* pArray){
    int new_size = _size*2;
    T* new_array = new T[new_size];
    for(int i=0;i<_size;i++){
        new_array[i]=pArray[i];
    }
    *_array=*new_array;
    _size=new_size;
}

/**
 * Inserta un dato en el arreglo
 * @param pData dato a insertar
 */
template <typename T>
void Array<T>::insert(T pData){
    if(_index>=_size){
        resize(_array);
    }
    _array[_index]=pData;
    _index++;
}

/**
 * Obtiene un dato
 * @param pIndex posicion del dato en el arreglo
 * @return dato obtenido
 */
template <typename T>
T Array<T>::get_data(int pIndex) {
    if(pIndex<0||pIndex>=_index){
        cout<<"Fuera de rango";
    }else {
        return _array[pIndex];
    }
}