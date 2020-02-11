#ifndef _FECHAHORA_H_
#define _FECHAHORA_H_
#include <string>

std::string diaFecha(std::string fecha);
std::string horaActual();
std::string fechaActual();
long tiempoVuelo(std::string hora);
std::string fechachange( std::string fecha, std::string origen, std::string destino);

#endif
