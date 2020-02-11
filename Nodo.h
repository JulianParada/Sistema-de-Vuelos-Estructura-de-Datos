#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED
#include <list>
template< class T >
class Nodo
{
protected:
    T dato;
    Nodo<T>* anterior;
    std::list< Nodo<T>* > desc;
    bool visitado;
public:
    Nodo(Nodo<T>* anterior);
    Nodo(T val, Nodo<T>* anterior);
    ~Nodo();
    T obtenerDato();
    void fijarDato(T val);
    void limpiarLista();
    void adicionarDesc(T nval);
    void eliminarDesc(T val);
    void fijarLista(std::list<Nodo<T>*>desc);
    Nodo<T>* obtenerAnterior();
    void fijarAnterior(Nodo<T>*n);
    std::list< Nodo<T>* > obtenerLista();
    void switchVisitado();
};
#include "Nodo.hxx"
#endif // NODO_H_INCLUDED
