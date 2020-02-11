// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================
#ifndef __Console__h__
#define __Console__h__

#include "PUJ/Console.h"
#include"agencia.h"
#include"sistema.h"
#include "ArbolGeneral.h"
#include "Nodo.h"
#include "Graph.h"
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>

/**
 */
class Console
: public PUJ::Console
{
public:
	typedef Console      Self;
	typedef PUJ::Console Superclass;

protected:
	Agencia agenciaP;
	Sistema sistemaP;

	bool ingresado;

	ArbolGeneral<std::string> *ARorigenes;
	ArbolGeneral<std::string> *ARfechas;
	ArbolGeneral<std::string> *ARvuelos ;
	ArbolGeneral<std::string> *ARap;
	ArbolGeneral<std::string> *ARAgencias;
	ArbolGeneral<std::string> *ARVentas;
	ArbolGeneral<std::string> *ARcedulas;

	std::list< std::string> listaorigenes;
	std::list< std::string> listafecha;
	std::list< std::string> listaidvuelo;
	std::list<std::string> listica;
	std::list<std::string> listaAgencias;
	std::list<std::string> listaIdVentas;
	std::list<std::string> listaCedulas;

public:
	Console( );
	Console( const std::string& prompt ,const std::string archEmpresas,const std::string archVuelos,const std::string archTiquetes );
	virtual ~Console( );

	virtual int trigger( const std::string& s ) override;
	virtual int hotkeys( char c ) override;
};

#endif // __Console__h__

// eof - Console.h
