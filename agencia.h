#ifndef _AGENCIA_H_
#define _AGENCIA_H_
#include"fechaHora.h"
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "venta.h"
#include "vuelo.h"


struct Agencia
{
	std::list<Venta> tiquetesVendidos;
	std::list<Venta> tiquetesModificados;
	std::list<Venta> tiquetesCancelados;
	std::string user;
	std::string password;
};

std::list<Vuelo> generarReporteDisponibles(std::list<Vuelo>& as);
std::list<Vuelo> generarReporteOrigenFecha(std::list<Vuelo>& as, std::string origen,std::string fecha);
std::list<Vuelo> generarReporteOrigen(std::list<Vuelo>& as, std::string origen);
Vuelo encontrarVuelo(std::list<Vuelo> as, std::string id, std::string d);
Venta venderVueloSencillo(std::list<Vuelo> as, std::string id, std::string fch, Agencia& ag, std::list<Venta>& tv,std::list<Vuelo>& pr, std::list<Agencia>& emd);
void reportMoney(Agencia ag, std::list<Vuelo>& programados);
bool cancelar(std::string ids, Agencia& ag, std::list<Vuelo>& programados, std::list<Agencia>& as,std::list<Vuelo>& dsp);
std::list<Venta> seleccionarVendidos(std::list<Venta>& as);

#endif
