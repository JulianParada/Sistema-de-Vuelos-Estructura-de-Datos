#ifndef ARBOLGENERAL_HXX_INCLUDED
#define ARBOLGENERAL_HXX_INCLUDED
#include "ArbolGeneral.h"
#include "Nodo.h"
#include <list>
#include <iostream>
template< class T >
ArbolGeneral<T>::ArbolGeneral()
{
    ArbolGeneral::raiz = NULL;
}
template< class T >
ArbolGeneral<T>::ArbolGeneral(T val)
{
    ArbolGeneral::raiz = NULL;
    Nodo<T> *n = new Nodo<T>(val, NULL);
    ArbolGeneral::fijarRaiz(n);
}
template< class T >
bool  ArbolGeneral<T>::esVacio()
{
    if(ArbolGeneral::raiz==NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
template< class T >
Nodo<T>* ArbolGeneral<T>::obtenerRaiz()
{
    return ArbolGeneral::raiz;
}
template< class T >
void  ArbolGeneral<T>::fijarRaiz(Nodo<T>*nraiz)
{
    if(ArbolGeneral::raiz==NULL)
    {
        ArbolGeneral::raiz=nraiz;
        if(!(ArbolGeneral::raiz->obtenerLista().empty()))
        {
            ArbolGeneral::raiz = raiz->obtenerLista().front();
        }
    }
    else if(nraiz!=NULL)
    {
        raiz->fijarAnterior(nraiz);
        std::list<Nodo<T>*> listA = nraiz->obtenerLista();
        listA.push_back(raiz);
        nraiz->fijarLista(listA);
        ArbolGeneral::raiz=nraiz;
    }
    else
    {
        if(!(ArbolGeneral::raiz->obtenerLista().empty()))
        {
            Nodo<T>* aux = ArbolGeneral::raiz->obtenerLista().front();
            ArbolGeneral::raiz->~Nodo();
            ArbolGeneral::raiz=aux;
        }
        else
        {
            ArbolGeneral::raiz = NULL;
        }
    }

}
template< class T >
bool ArbolGeneral<T>::insertarNodo(T padre, T n)
{
    if(bool existencia = ArbolGeneral::buscar(n))
    {
        return false;
    }
    bool resultado = false;
    if (ArbolGeneral::raiz->obtenerDato()==n)
    {
        ArbolGeneral::raiz->adicionarDesc(n);
        resultado = true;
    }
    else if(!(ArbolGeneral::raiz->obtenerLista().empty()))
    {
        Nodo<T>* aux = ArbolGeneral::buscar(padre, ArbolGeneral::raiz);
        if(aux!=NULL)
        {
            aux->adicionarDesc(n);
            resultado = true;
        }
    }
    else if(padre == ArbolGeneral::raiz->obtenerDato())
    {
        ArbolGeneral::raiz->adicionarDesc(n);
        resultado = true;
    }
    return resultado;
}
template< class T >
Nodo<T>* ArbolGeneral<T>::buscar(T n, Nodo<T>* inicio)
{
    if(inicio->obtenerDato()==n)
    {
        return inicio;
    }
    if(!(inicio->obtenerLista().empty()))
    {

        std::list<Nodo<T>*> listAux = inicio->obtenerLista();
        auto iT = listAux.begin();
        for(; iT!=listAux.end(); iT++)
        {
            Nodo<T>* nuevo = *(iT);
            Nodo<T>* aux = ArbolGeneral::buscar(n, nuevo);
            if(aux!=NULL)
            {
                return aux;
            }
        }
    }
    else if(n == inicio->obtenerDato())
    {
        return inicio;
    }
    return NULL;
}
template< class T >
bool ArbolGeneral<T>::eliminarNodo(T n)
{
    bool resultado = false;
    if((ArbolGeneral::raiz->obtenerDato())==n)
    {
        ArbolGeneral::fijarRaiz(NULL);
        resultado = true;
    }
    else if(!(ArbolGeneral::raiz->obtenerLista().empty()))
    {
        Nodo<T>* aux = ArbolGeneral::buscar(n, ArbolGeneral::raiz);
        if(aux!=NULL)
        {
            aux->obtenerAnterior()->eliminarDesc(n);
            resultado = true;
        }
    }
    else if(n == ArbolGeneral::raiz->obtenerDato())
    {
        raiz->eliminarDesc(n);
        resultado = true;
    }
    return resultado;
}
template< class T >
bool ArbolGeneral<T>::buscar(T n)
{
    bool resultado = false;
    if((ArbolGeneral::raiz->obtenerDato())==n)
    {
        resultado = true;
    }
    else if(!(ArbolGeneral::raiz->obtenerLista().empty()))
    {
        Nodo<T>* aux = ArbolGeneral::buscar(n, ArbolGeneral::raiz);
        if(aux!=NULL)
        {
            resultado = true;
        }
    }
    else if(n == ArbolGeneral::raiz->obtenerDato())
    {
        resultado = true;
    }
    return resultado;
}
template<class T>
unsigned int ArbolGeneral<T>::altura(Nodo<T>* inicio)
{
    return ArbolGeneral::determinarAltura(inicio, 0);
}
template<class T>
unsigned int ArbolGeneral<T>::determinarAltura(Nodo<T>* inicio, int n)
{
    if(!(inicio->obtenerLista().empty()))
    {
        std::list<Nodo<T>*> listAux = inicio->obtenerLista();
        auto iT = listAux.begin();
        n++;
        for(; iT!=listAux.end(); iT++)
        {
            Nodo<T>* aux = *(iT);
            unsigned int a;
            a = determinarAltura(aux, n);
            if((int)a>(int)n)
            {
                n = a;
            }
        }
    }
    return n;
}
template<class T>
unsigned int ArbolGeneral<T>::tamano(Nodo<T>* inicio)
{
    if(inicio!=NULL)
    {
        return determinarTamano(inicio);
    }
   return 0;
}
template<class T>
unsigned int ArbolGeneral<T>::determinarTamano(Nodo<T>* inicio)
{
    int n=1;
    if(!(inicio->obtenerLista().empty()))
    {
        std::list<Nodo<T>*> listAux = inicio->obtenerLista();
        auto iT = listAux.begin();
        for(; iT!=listAux.end(); iT++)
        {
            Nodo<T>* aux = *(iT);
            n = n+determinarTamano(aux);

        }
    }
    return n;
}
template<class T>
void ArbolGeneral<T>::preOrden(Nodo<T>* inicio)
{
    std::cout<<inicio->obtenerDato()<<"->";
    inicio->switchVisitado();
    if(!(inicio->obtenerLista().empty()))
    {
        std::list<Nodo<T>*> listAux = inicio->obtenerLista();
        auto iT = listAux.begin();
        for(; iT!=listAux.end(); iT++)
        {
            Nodo<T>* aux = *(iT);
            preOrden(aux);
        }
    }
}
template<class T>
void ArbolGeneral<T>::posOrden(Nodo<T>* inicio)
{
    /*
    if(!(inicio->obtenerLista().empty()))
    {
        std::list<Nodo<T>*> listAux = inicio->obtenerLista();
        auto iT = listAux.begin();
        for(; iT!=listAux.end(); iT++)
        {
            std::cout<<inicio->obtenerDato()<<"->";
            inicio->switchVisitado();
        }
        iT = listAux.begin();
        for(; iT!=listAux.end(); iT++)
        {
            Nodo<T>* aux = *(iT);
            posOrden(aux);
        }

    }
    */
    if(!(inicio->obtenerLista().empty()))
    {
        std::list<Nodo<T>*> listAux = inicio->obtenerLista();
        auto iT = listAux.begin();
        for(; iT!=listAux.end(); iT++)
        {
            Nodo<T>* aux = *(iT);
            posOrden(aux);
        }
    }
    std::cout<<inicio->obtenerDato()<<"->";
    inicio->switchVisitado();

}
#endif // ARBOLGENERAL_HXX_INCLUDED
