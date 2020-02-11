#ifndef NODO_HXX_INCLUDED
#define NODO_HXX_INCLUDED
#include "Nodo.h"
#include "list"

template< class T >
Nodo<T>::Nodo(Nodo<T>* anterior)
{
    Nodo::anterior=anterior;
    Nodo::visitado=false;
}
template< class T >
Nodo<T>::Nodo(T val, Nodo<T>* anterior)
{
//std::cout<<val<<std::endl;
    Nodo::dato = val;
    Nodo::anterior=anterior;
    Nodo::visitado=false;
}
template< class T >
Nodo<T>::~Nodo()
{
    if(Nodo::anterior==NULL)
    {

        Nodo<T>* aux = Nodo::desc.front();
        std::list<Nodo<T>*> listNuevo = aux->obtenerLista();
        std::list<Nodo<T>*> listAux2 = Nodo::desc;
        auto iT = listAux2.begin();
        while(iT!=listAux2.end())
        {
            if(iT!=listAux2.end())
            {
                iT++;
            }
            if(iT==listAux2.end())
            {
                break;
            }
            listNuevo.push_back(*(iT));

            iT++;
        }
        aux->fijarLista(listNuevo);
        aux->fijarAnterior(NULL);
    }
    else if(!Nodo::desc.empty())
    {
        Nodo<T>* aux = Nodo::desc.front();
        std::list<Nodo<T>*> listNuevo = aux->obtenerLista();
        std::list<Nodo<T>*> listAux2 = Nodo::desc;
        auto iT = listAux2.begin();
        while(iT!=listAux2.end())
        {
            if(iT!=listAux2.end())
            {
            iT++;
            }
            listNuevo.push_back(*(iT));
            iT++;
        }
        aux->fijarLista(listNuevo);
        std::list<Nodo<T>*> listAux = Nodo::anterior->obtenerLista();
        listAux.push_front(aux);
        Nodo::anterior->fijarLista(listAux);
        aux->fijarAnterior(Nodo::anterior);
    }
}
template< class T >
void Nodo<T>::fijarLista(std::list<Nodo<T>*>desc)
{
    Nodo::desc=desc;
}
template< class T >
T Nodo<T>::obtenerDato()
{
    return Nodo::dato;
}
template< class T>
void Nodo<T>::limpiarLista()
{
    while(!Nodo::desc.empty())
    {
        Nodo::desc.back()->limpiarLista();
        Nodo::desc.back()->~Nodo();
        Nodo::desc.back()=NULL;
        Nodo::desc.pop_back();
    }
}
template< class T>
void Nodo<T>::adicionarDesc(T nval)
{
    Nodo<T>* nNodo = new Nodo<T>(nval, this);
    Nodo::desc.push_back(nNodo);
}
template< class T>
void Nodo<T>::eliminarDesc(T nval)
{
    std::list<Nodo<T>*> listAux = Nodo::desc;
    for(auto iT = listAux.begin(); iT!= listAux.end(); iT++)
    {
        Nodo<T>* aux =*(iT);
        T dato = aux->obtenerDato();
        if(dato == nval)
        {
           Nodo::desc.remove(*iT);
           aux->~Nodo();
        }
    }
}
template< class T>
std::list< Nodo<T>* > Nodo<T>::obtenerLista()
 {
    return Nodo::desc;
 }
 template< class T>
 Nodo<T>* Nodo<T>::obtenerAnterior()
 {
     return Nodo::anterior;
 }
 template< class T>
void Nodo<T>::fijarAnterior(Nodo<T>*n)
{
    Nodo::anterior = n;
}
template< class T>
void Nodo<T>::switchVisitado()
{
    Nodo::visitado = !Nodo::visitado;
}

#endif // NODO_HXX_INCLUDED
