#ifndef SISTEMA_H_
#define SISTEMA_H_
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <algorithm>
#include "ArbolGeneral.h"
#include "Nodo.h"
#include "Graph.h"
#include"venta.h"
#include"vuelo.h"
#include"fechaHora.h"
#include "agencia.h"
#include<vector>
#include<sstream>

struct Sistema{
    std::list<Agencia> empresasDisp;
    std::list<Vuelo> vuelosDisp;
    std::list<Vuelo> vuelosProgramados;
    std::list<Venta> listaTiquetes;
};

bool login(std::list<Agencia>& as, std::string us, std::string pass, Agencia& ag);
bool llenarListaEmpresas(std::string name, std::list<Agencia>& as);
bool llenarListaVuelos(std::string name,std::list<Vuelo>& as);
bool llenarListaTiquetes(std::string name, std::list<Venta>& as);
void llenarListasAgencias(std::list<Venta>& as, std::list<Agencia>& ag, std::list<Vuelo> vuelos);
void actualizarAsientos(std::list<Vuelo>& disponibles, std::list<Vuelo>& programados, std::list<Agencia>& ag);
bool sillasVuelo(std::list<Vuelo>& as,std::string s);
bool sillasVueloPositiva(std::list<Vuelo>& as,std::string s);
bool borrarTiquete(std::list<Venta>& t, Venta v);
bool borrarTiqueteN(std::list<Venta>& l, Venta v);
bool buscarTiquete(std::list<Venta>& l, Venta v);
Venta buscarTiqueteR(std::list<Venta>& l, Venta v);
bool modificarVendidos(std::list<Venta>& l, Venta v, char hc);
int comparaFecha( std::string fecha1, std::string fecha2 );
bool buscarVuelo(std::list<Vuelo>& as,std::string s);
Vuelo buscarVueloR(std::list<Vuelo>& as,std::string s);
bool borrarVuelo(std::list<Vuelo>& l, Vuelo v);
void consolidarI(Agencia& agen, std::list<Vuelo>& vuelos, std::list<Agencia>& ag, std::list<Vuelo>& vuelosdis);
void actualizarVuelosProgramados(std::list<Vuelo>& pr);
void actualizarTiquetesAgencia(std::list<Agencia>& ag);
void imprimirEmpresas(std::list<Agencia> as);
void imprimirVuelos(std::list<Vuelo> as);
void imprimirTiquetes(std::list<Venta> as);
void imprimirVenta(Venta as);
void escribirarchtickets(std::list<Agencia> tiquetes);
std::string resta(const std::string &a, const std::string &b);
void llenarlistasarbol(std::list<std::string>& listaorigenes, std::list<std::string>& listaidvuelo, std::list<std::string>& listafecha, std::list<Vuelo>  pr, std::list<Vuelo> prog);
void llenarAgenciasArbol(std::list< std::string>& listaa, std::list<Agencia>  pr);
void llenarlistaVentasArbol(std::list< std::string>& listaa,std::list<Venta> pr);
void llenarlistaCedulas(std::list<Venta> listaTiquetes, std::list<std::string>& listaa);
void llenar(std::list<std::string>listica,ArbolGeneral<std::string>* aG);
std::list<std::string> autocomp (std::string input,ArbolGeneral<std::string>* aG);
void getauto(Nodo<std::string>* inicio, std::list<std::string>& listaa);
Nodo<std::string >* buscartrie(std::string  n, Nodo<std::string >* inicio);
void imprimirVuelosR(std::list<Vuelo> as);
void llenarGrafoTiempo(std::list<Vuelo> vuelospr, Graph<std::string, long>& grafito, Graph<std::string, float>& grafito2,Graph<std::string, int>& grafito3);
Vuelo buscarVueloDisponible(std::string origen, std::string destino, std::list<Vuelo> as);
bool change(std::list<Vuelo>& disponibles, std::list<Vuelo>& programados, std::list<Agencia>& ag,std::string cc, std::string idviejo,std::string idnuevo);

#endif
