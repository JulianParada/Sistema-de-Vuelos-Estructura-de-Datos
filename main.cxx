#include"fechaHora.h"
#include"agencia.h"
#include"sistema.h"
#include"venta.h"
#include"vuelo.h"
#include "ArbolGeneral.h"
#include "Nodo.h"
#include "Graph.h"
#include"Console.h"
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include<vector>

int  main(int argc, char * argv[])
{

	if(argc < 3)
	{
		std::cout<<"Faltan parametros para la ejecucion del programa.\n";
		std::cout<<"Se requiere el archivo de vuelos, de empresas y de tiquetes respectivamente."<<std::endl;
		return 0 ;
	}

    std::string archVuelos = argv[1];
    std::string archEmpresas = argv[2];
    std::string archTiquetes = argv[3];

    Console consolita("$", archEmpresas,archVuelos, archTiquetes );
    consolita.run();

std::cout<<"Sistema de agencias cerrado correctamente. \n";

return 0;
}
