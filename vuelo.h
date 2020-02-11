#ifndef _vuelo_H_
#define _vuelo_H_
#include <string>

struct Vuelo
{
    std::string codigo;
    std::string dia;
    std::string origen;
    std::string destino;
    std::string hora;
    std::string duracion;
    int sillas;
    long costo;
};

#endif
