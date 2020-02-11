#ifndef _VENTA_H_
#define _VENTA_H_
#include <string>

struct Venta
{
    std::string agencia;
    int Idventa;
    std::string vuelo;
    std::string cedula;
    std::string apellidos;
    std::string nombres;
    std::string fechavuelo;
    std::string fechacompra;
    std::string horacompra;
    char tipo;
};

#endif
