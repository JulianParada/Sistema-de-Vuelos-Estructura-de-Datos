#ifndef ARBOLGENERAL_H_INCLUDED
#define ARBOLGENERAL_H_INCLUDED

#include "Nodo.h"
#include <list>

template <class T>
class ArbolGeneral
{
protected:
    Nodo<T>* raiz;
    unsigned int determinarAltura(Nodo<T>* inicio, int n);
    unsigned int determinarTamano(Nodo<T>* inicio);
    Nodo<T>* buscar(T n, Nodo<T>* inicio);
public:
    ArbolGeneral();
    ArbolGeneral(T val);
    ~ArbolGeneral();
    bool esVacio();
    Nodo<T>* obtenerRaiz();
    void fijarRaiz(Nodo<T>* nraiz);
    bool insertarNodo(T padre, T n);
    bool eliminarNodo(T n);
    bool buscar(T n);
    unsigned int altura(Nodo<T>* inicio);
    unsigned int tamano(Nodo<T>* inicio);
    void preOrden(Nodo<T>* inicio);
    void posOrden(Nodo<T>* inicio);
    //void nivelOrden(Nodo<T>* inicio);
};
#include "ArbolGeneral.hxx"

#endif // ARBOLGENERAL_H_INCLUDED
