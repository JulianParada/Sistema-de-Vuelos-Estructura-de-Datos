#include"sistema.h"
#include "ArbolGeneral.h"
#include "Nodo.h"
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <algorithm>
#include<vector>
#include<sstream>

std::string resta(const std::string &a, const std::string &b)
{
    std::string result;
    // Identificar la cadena más corta y más larga.
    const std::string &largo = a.size() < b.size() ? b : a;
    const std::string &corto = a.size() < b.size() ? a : b;

    // El resultado será, como mucho, tan largo como la cadena corta.
    result.reserve(corto.size());
    // Copiamos el contenido de 'largo' que cumpla la lambda
    std::copy_if(largo.begin(), largo.end(), std::back_inserter(result), [&corto](const std::string::value_type &c)
    {
        // Verdadero sólo si 'corto' no contiene 'c'.
        return std::find(corto.begin(), corto.end(), c) == corto.end();
    });

    return result;
}

bool login(std::list<Agencia>& as, std::string us, std::string pass, Agencia& ag)
{
    bool found=false;
    for (std::list<Agencia>::iterator it = as.begin(); it != as.end(); it++)
    {
        if(it->user.compare(us)==0 && (it->password.compare(pass)==0))
        {
            ag.user=us;
            ag.password=pass;
            ag.tiquetesVendidos=it->tiquetesVendidos;
            ag.tiquetesModificados = it->tiquetesModificados;
            ag.tiquetesCancelados = it->tiquetesCancelados;
            found = true;
            break;
        }
    }
    return found;
}

bool sillasVuelo(std::list<Vuelo>& as,std::string s)
{
    bool existe = false;
    for (std::list<Vuelo>::iterator it = as.begin(); it != as.end(); it++)
    {
        if(it->codigo.compare(s)==0)
        {
            it->sillas--;
            existe = true;
            break;
        }
    }
    return existe;
}

bool buscarVuelo(std::list<Vuelo>& as,std::string s)
{
    bool existe = false;
    for (std::list<Vuelo>::iterator it = as.begin(); it != as.end(); it++)
    {
        if(it->codigo.compare(s)==0)
        {
            existe = true;
            break;
        }
    }
    return existe;
}

Vuelo buscarVueloR(std::list<Vuelo>& as,std::string s)
{
    Vuelo existe;
    for (std::list<Vuelo>::iterator it = as.begin(); it != as.end(); it++)
    {
        if(it->codigo.compare(s)==0)
        {
            existe = (*it);
            break;
        }
    }
    return existe;
}

void actualizarAsientos(std::list<Vuelo>& disponibles, std::list<Vuelo>& programados, std::list<Agencia>& ag)
{
    std::list<Agencia>::iterator it;
    std::list<Venta>::iterator its;
    for(it = ag.begin(); it!=ag.end(); it++)
    {
        if(!it->tiquetesVendidos.empty()){
            for(its = it->tiquetesVendidos.begin(); its != it->tiquetesVendidos.end(); its++)
            {
               if(its->tipo == 'v')
               {
                Vuelo volar = buscarVueloR(disponibles, its->vuelo);
                if(!buscarVuelo(programados, volar.codigo))
                {
                    volar.dia = its->fechavuelo;
                    volar.sillas--;
                    programados.push_back(volar);
                    break;
                }
                else
                {
                    sillasVuelo(programados, volar.codigo);
                    break;
                }
            }
            else if(its->tipo == 'm')
            {
                Vuelo volarOriginal = buscarVueloR(disponibles, its->vuelo);

                std::list<Venta>::iterator itm;
                for(itm = it->tiquetesModificados.begin(); itm != it->tiquetesModificados.end(); its++)
                {
                    Vuelo volar = buscarVueloR(disponibles, itm->vuelo);
                    if(volarOriginal.codigo != volar.codigo)
                    {
                        sillasVueloPositiva(programados, volarOriginal.codigo);
                        if(!buscarVuelo(programados, volar.codigo))
                        {
                            volar.dia = itm->fechavuelo;
                            volar.sillas--;
                            programados.push_back(volar);
                            break;
                        }
                        else
                        {
                            sillasVuelo(programados, volar.codigo);
                            break;
                        }
                    }
                    
                }
            }
            else if(its->tipo == 'c')
            {

                Vuelo volarOriginal = buscarVueloR(disponibles, its->vuelo);
                sillasVueloPositiva(programados, volarOriginal.codigo);
                break;


                /*std::list<Venta>::iterator itc;
                for(itc = it->tiquetesCancelados.begin(); itc != it->tiquetesCancelados.end(); its++)
                {
                    Vuelo volar = buscarVueloR(disponibles, itc->vuelo);
                    if(!buscarVuelo(programados, volar.codigo))
                    {
                        volar.dia = itc->fechavuelo;
                        programados.push_back(volar);
                        break;
                    }
                }*/
            }
        }
    }
}
}
bool llenarListaVuelos(std::string name, std::list<Vuelo>& as)
{
    bool leer = false;
    std::string line;
    std::ifstream file(name);
    if (file.is_open())
    {
        while ( getline (file,line) )
        {
            char frase [500];
            strcpy( frase,line.c_str());
            char *p = strtok(frase," ;");

            Vuelo aux;

            aux.codigo = p;
            p=strtok(NULL, ";");

            aux.dia = p;
            p=strtok(NULL, ";");

            aux.origen =p;
            p=strtok(NULL, ";");

            aux.destino = p;
            p=strtok(NULL, ";");

            aux.hora = p;
            p=strtok(NULL, ";");

            aux.duracion = p;
            p=strtok(NULL, ";");

            aux.sillas = atoi(p);
            p=strtok(NULL, " ;");

            std::string cost=p;
            cost.erase(cost.find_last_not_of(" \n\r\t")+1);
            aux.costo = atoi(cost.c_str());

            as.push_back(aux);
        }
        file.close();
        leer = true;
    }
    else std::cout<<"Unable to open file" << std::endl;

    return leer;
}

bool llenarListaEmpresas(std::string name, std::list<Agencia>& as)
{
    bool leer = false;
    std::string line;
    std::ifstream file(name);
    if (file.is_open())
    {
        while ( getline (file,line) )
        {
            char frase [500];
            strcpy( frase,line.c_str());
            char *p = strtok(frase," ;");

            Agencia aux;
            aux.user = p;
            p=strtok(NULL, " ");
            std::string contra=p;
            contra.erase(contra.find_last_not_of(" \n\r\t")+1);
            aux.password = contra;
            as.push_back(aux);
        }
        file.close();
        leer = true;
    }
    else std::cout<<"Unable to open file" << std::endl;

    return leer;
}

bool llenarListaTiquetes(std::string name, std::list<Venta>& as)
{
    bool leer = false;
    std::string linea;
    std::ifstream file(name);
    if (file.is_open())
    {
        while ( getline (file,linea) )
        {
            Venta aux;

            std::stringstream ss(linea);
            std::string token;
            std::vector<std::string> arra;

            while(std::getline(ss, token, ';')) {
                arra.push_back(token);
                //std::cout << token << "|";
            }


            std::stringstream ss2(arra[0]);
            //std::cout << ss2 << "|";
            std::string token2;
            std::vector<std::string> arra2;
            while(std::getline(ss2, token2, '_'))
            {
                arra2.push_back(token2);
                //std::cout << token2 << " ";
            }

            std::stringstream ss3(arra[3]);
            std::string token3;
            std::vector<std::string> arra3;
            while(std::getline(ss3, token3, ','))
            {
                arra3.push_back(token3);
                //std::cout << token3 << "|";
            }

            aux.agencia = arra2[0];
            //std::cout << arra2[0] << "|";
            //std::cout << aux.agencia << "|";

            aux.Idventa = atoi(arra2[1].c_str());
            //std::cout << arra2[1] << "|";


            if(arra[1] == "")
            {
                aux.vuelo = "0";
                //std::cout << 0 << "|";
            }else
            {
                aux.vuelo = arra[1];
                //std::cout << arra[1] << "|";
            }

            aux.cedula = arra[2];
            //std::cout << arra[2] << "|";

            aux.apellidos = arra3[0];
            //std::cout << arra3[0] << "|";

            aux.nombres = arra3[1];
            //std::cout << arra3[1] << "|";

            aux.fechavuelo = arra[4];
            //std::cout << arra[4] << "|";

            aux.fechacompra = arra[5];
            //std::cout << arra[5] << "|";

            aux.horacompra = arra[6];
            //std::cout << arra[6];

            //std::cout<<arra.size()<<std::endl;
            //std::cout << '\n';

            as.push_back(aux);
        }
        file.close();
        leer = true;
    }
    else std::cout<<"Unable to open file" << std::endl;

    return leer;
}

void llenarListasAgencias(std::list<Venta>& as, std::list<Agencia>& ag, std::list<Vuelo> vuelos)
{
    std::list<Venta>::iterator it;
    std::list<Agencia>::iterator its;
    for(it = as.begin(); it!=as.end(); it++)
    {
        std::string agen = it->agencia;
        for(its = ag.begin(); its != ag.end(); its++)
        {
            if(agen.compare(its->user)==0)
            {


                std::list<Venta> tempV = its->tiquetesVendidos;
                std::list<Venta> tempM = its->tiquetesModificados;
                std::list<Venta> tempC = its->tiquetesCancelados;
                bool esta = buscarVuelo(vuelos,it->vuelo);

                if(esta)
                {
                    if(!buscarTiquete(tempV, (*it)))
                    {
                        it->tipo = 'v';
                        tempV.push_back((*it));
                    }
                    else if(buscarTiquete(tempV, (*it)))
                    {
                        if(!buscarTiquete(tempM, (*it)))
                        {
                            it->tipo = 'm';
                            modificarVendidos(tempV, (*it), 'm');
                            tempM.push_back((*it));
                        }
                        else if(buscarTiquete(tempM, (*it)) && borrarTiquete(tempM, (*it)))
                        {
                            it->tipo = 'm';
                            modificarVendidos(tempV, (*it), 'm');
                            tempM.push_back((*it));
                        }
                    }

                }
                else if (it->vuelo == "0")
                {
                    if(buscarTiquete(tempV, (*it)))
                    {
                        if(!buscarTiquete(tempM, (*it)))
                        {
                            it->tipo = 'c';
                            modificarVendidos(tempV, (*it), 'c');
                            tempC.push_back((*it));
                        }
                        else if(buscarTiquete(tempM, (*it)) && borrarTiqueteN(tempM, (*it)))
                        {
                            it->tipo = 'c';
                            modificarVendidos(tempV, (*it), 'c');
                            tempC.push_back((*it));
                        }
                        
                    }
                }

                its->tiquetesVendidos = tempV;
                its->tiquetesModificados = tempM;
                its->tiquetesCancelados = tempC;

            }
        }
    }
}

bool borrarTiquete(std::list<Venta>& l, Venta v)
{

    bool borrar = false;
    if(!l.empty())
    {
        std::list<Venta>::iterator it;
        std::list<Venta>::iterator ita = l.end();
        for (it = l.begin(); it != l.end(); it++)
        {
            int fch = comparaFecha(it->fechacompra, v.fechacompra);
            if((it->cedula== v.cedula) && (it->nombres== v.nombres))
            {
                if((fch == -1))
                {
                    ita = it;
                    break;
                }
            }
        }
        if(ita != l.end())
        {
            l.erase(ita);
            borrar = true; 
        }
    }
    return (borrar);
}

bool borrarTiqueteN(std::list<Venta>& l, Venta v)
{

    bool borrar = false;
    if(!l.empty())
    {
        std::list<Venta>::iterator it;
        std::list<Venta>::iterator ita = l.end();
        for (it = l.begin(); it != l.end(); it++)
        {

            if((it->cedula== v.cedula) && (it->nombres== v.nombres))
            {
                ita = it;
                break;
            }
        }
        if(ita != l.end())
        {
            l.erase(ita);
            borrar = true; 
        }
    }
    return (borrar);
}

bool buscarTiquete(std::list<Venta>& l, Venta v)
{

    bool encontro = false;
    if(!l.empty())
    {
        std::list<Venta>::iterator it;
        for (it = l.begin(); it != l.end(); it++)
        {
            if((it->cedula== v.cedula) && (it->nombres== v.nombres))
            {
                encontro = true;
                break;
            }
        }
    }
    return (encontro);
}

Venta buscarTiqueteR(std::list<Venta>& l, Venta v)
{

    Venta encontro;
    if(!l.empty())
    {
        std::list<Venta>::iterator it;
        for (it = l.begin(); it != l.end(); it++)
        {
            if((it->cedula== v.cedula) && (it->nombres== v.nombres))
            {
                encontro = (*it);
                break;
            }
        }
    }
    return (encontro);
}

bool modificarVendidos(std::list<Venta>& l, Venta v, char hc)
{
    bool encontro = false;
    if(!l.empty())
    {
        std::list<Venta>::iterator it;
        for (it = l.begin(); it != l.end(); it++)
        {
            if((it->cedula== v.cedula) && (it->nombres== v.nombres))
            {
                it->tipo = hc;
                encontro = true;
                break;
            }
        }
    }
    return (encontro);
}

void imprimirVenta(Venta as)
{
    std::cout<<"----------------------------------------------------------------------------------------------"<<std::endl;
    std::cout<<"                                ****Venta Realizada****                                       "<<std::endl;
    std::cout<<"Agencia: "<<as.agencia<<"   ID: "<<as.Idventa<<"  Vuelo: "<<as.vuelo<<std::endl;
    std::cout<<"    Cedula: "<<as.cedula<<"    Apellidos: "<<as.apellidos<<"    Nombres: "<<as.nombres<<std::endl;
    std::cout<<"    Fecha Vuelo: "<<as.fechavuelo<<"   Fecha Compra: "<<as.fechacompra<<"    Hora Compra: "<<as.horacompra<<std::endl;
    std::cout<<"----------------------------------------------------------------------------------------------"<<std::endl;
}

void imprimirEmpresas(std::list<Agencia> as)
{
    std::cout<<"----------------------------------+"<<std::endl;
    std::cout<<"AgenciaUser \t "<<"Constraseña \t"<<std::endl;
    std::cout<<"----------------------------------+"<<std::endl;
    for (std::list<Agencia>::iterator it = as.begin(); it != as.end(); it++)
    {
        std::cout<<it->user<<"\t         ";
        std::cout<<it->password<<"\t "<<std::endl;
    }
}

void imprimirVuelos(std::list<Vuelo> as)
{
    std::cout<<"                                    ****LISTA DE VUELOS****                                    "<<std::endl;
    for (std::list<Vuelo>::iterator it = as.begin(); it != as.end(); it++)
    {
        std::cout<<"----------------------------------------------------------------------------------------------"<<std::endl;
        std::cout<<"Codigo: "<<it->codigo<<"   Dia: "<<it->dia<<"   Hora: "<<it->hora<<std::endl;
        std::cout<<"    Origen: "<<it->origen<<"    Destino: "<<it->destino<<"      Duracion: "<<it->duracion<<std::endl;
        std::cout<<"    Sillas Disponibles: "<<it->sillas<<"   Costo por Silla: "<<"$"<<it->costo<<std::endl;
        std::cout<<std::endl;
        std::cout<<"----------------------------------------------------------------------------------------------"<<std::endl;

    }
}

void imprimirTiquetes(std::list<Venta> as)
{

    for (std::list<Venta>::iterator it = as.begin(); it != as.end(); it++)
    {
        std::cout<<"----------------------------------------------------------------------------------------------"<<std::endl;
        std::cout<<"Agencia: "<<it->agencia<<"   ID: "<<it->Idventa<<"  Vuelo: "<<it->vuelo<<"  Tipo: ";
        if(it->tipo=='v')
            std::cout<<"Vendido";
        if(it->tipo=='m')
            std::cout<<"Modificado";
        if(it->tipo=='c')
            std::cout<<"Cancelado";
        std::cout<<std::endl;
        std::cout<<"    Cedula: "<<it->cedula<<"    Apellidos: "<<it->apellidos<<"    Nombres: "<<it->nombres<<std::endl;
        std::cout<<"    Fecha Vuelo: "<<it->fechavuelo<<"   Fecha Compra: "<<it->fechacompra<<"    Hora Compra: "<<it->horacompra<<std::endl;
    }
    std::cout<<"----------------------------------------------------------------------------------------------"<<std::endl;
}

/* Función comparaFecha, devuelve:
   -1 si fecha1 < fecha2
   0 si fecha1 = fecha2
   1 si fecha1 > fecha2
*/
int comparaFecha( std::string fecha1, std::string fecha2 )
{

    char *date = new char[8];
    strcpy(date, fecha1.c_str());
    tm tm1;
    sscanf(date,"%4d%2d%2d",&tm1.tm_year,&tm1.tm_mon,&tm1.tm_mday);

    int ano1 = tm1.tm_year;
    int mes1 = tm1.tm_mon;
    int dia1 = tm1.tm_mday;

    char *date2 = new char[8];
    strcpy(date2, fecha2.c_str());
    tm tm2;
    sscanf(date2,"%4d%2d%2d",&tm2.tm_year,&tm2.tm_mon,&tm2.tm_mday);

    int ano2 = tm2.tm_year;
    int mes2 = tm2.tm_mon;
    int dia2 = tm2.tm_mday;

    int val;

    if ( ano1 < ano2 )
        val = -1;
    else if ( ano1 > ano2 )
        val = 1;
    else
    {
        if ( mes1 < mes2 )
            val = -1;
        else if ( mes1 > mes2 )
            val = 1;
        else
        {
            if ( dia1 < dia2 )
                val = -1;
            else if ( dia1 > dia2 )
                val = 1;
            else
                val = 0;
        }
    }

    return val;
}

bool sillasVueloPositiva(std::list<Vuelo>& as,std::string s)
{
    bool existe = false;
    for (std::list<Vuelo>::iterator it = as.begin(); it != as.end(); it++)
    {
        if(it->codigo.compare(s)==0)
        {
            it->sillas++;
            existe = true;
            break;
        }
    }
    return existe;
}


//  los tres archivos
void consolidarI(Agencia& agen,std::list<Vuelo>& vuelos, std::list<Agencia>& ag, std::list<Vuelo>& vuelosdis)
{
    actualizarVuelosProgramados(vuelos);
    
    actualizarTiquetesAgencia(ag);
    for (std::list<Agencia>::iterator it = ag.begin(); it != ag.end(); it++)
    {
        if(it->user == agen.user)
        {
            agen.tiquetesCancelados = it->tiquetesCancelados;
            agen.tiquetesModificados = it->tiquetesModificados;
            agen.tiquetesVendidos = it->tiquetesVendidos;
        }
    }

    escribirarchtickets(ag);
    
}


void actualizarTiquetesAgencia(std::list<Agencia>& ag)
{
    for (std::list<Agencia>::iterator it = ag.begin(); it != ag.end(); it++)
    {
        std::list<Venta> vend = it->tiquetesVendidos;
        std::list<Venta> modf = it->tiquetesModificados;
        std::list<Venta> canc = it->tiquetesCancelados;

        for (std::list<Venta>::iterator itv = vend.begin(); itv != vend.end(); itv++)
        {
            if(itv->tipo == 'v')
            {
                int fch = comparaFecha(itv->fechavuelo, fechaActual());
                if(fch == 0 || fch == -1)
                {
                    borrarTiqueteN(vend, (*itv));
                    break;
                }
            }
            else if(itv->tipo == 'm')
            {

                Venta ven = buscarTiqueteR(modf, (*itv));
                int fch = comparaFecha(ven.fechavuelo, fechaActual());
                if(fch == 0 || fch == -1)
                {
                    borrarTiqueteN(modf, (*itv));
                    borrarTiqueteN(vend, (*itv));
                    break;
                }
            }
            else if(itv->tipo == 'c')
            {

                Venta ven = buscarTiqueteR(canc, (*itv));
                int fch = comparaFecha(ven.fechavuelo, fechaActual());
                if(fch == 0 || fch == -1)
                {
                    borrarTiqueteN(modf, (*itv));
                    borrarTiqueteN(canc, (*itv));
                    break;
                }
            }
        }

        it->tiquetesVendidos = vend;
        it->tiquetesModificados = modf;
        it->tiquetesCancelados = canc;
    }
    std::cout<<"Tiquetes consolidados correctamente"<<std::endl;
}

void actualizarVuelosProgramados(std::list<Vuelo>& pr)
{

    std::string fechaA = fechaActual();
    std::list<Vuelo> auxpr = pr;
    for (std::list<Vuelo>::iterator it = pr.begin(); it != pr.end(); it++)
    {
        int fch = comparaFecha(it->dia,fechaA);
        if(fch == 0 || fch == -1)
        {
           borrarVuelo(auxpr, (*it));
       }   
   }
   pr = auxpr;
   std::cout<<"Vuelos Programados consolidados correctamente"<<std::endl;

}

bool borrarVuelo(std::list<Vuelo>& l, Vuelo v)
{

    bool borrar = false;
    if(!l.empty())
    {
        std::list<Vuelo>::iterator it;
        std::list<Vuelo>::iterator ita = l.end();
        for (it = l.begin(); it != l.end(); it++)
        {
            if(it->codigo == v.codigo)
            {
                ita = it;
                break;
            }
        }
        if(ita != l.end())
        {
            l.erase(ita);
            borrar = true; 
        }
    }
    return (borrar);
}

void escribirarchtickets(std::list<Agencia> ag)
{
    if (ag.size()>0)
    {
        std::ofstream arch;
        arch.open("consolidate_tickets.txt");
        std::list<Agencia>::iterator ita;
        for (ita=ag.begin();ita!=ag.end();ita++)
        {

            for (std::list<Venta>::iterator it= ita->tiquetesVendidos.begin(); it!=ita->tiquetesVendidos.end(); it++)
            {
                if((*it).tipo == 'v'){


                   arch<<it->agencia;
                   arch<<"_";
                   arch<<it->Idventa;
                   arch<<";";

                   if(it->vuelo == "0")
                   {
                    arch<<";";
                }
                else
                {
                    arch<<it->vuelo;
                    arch<<";";
                }

                arch<<it->cedula;
                arch<<";";
                arch<<it->apellidos;
                arch<<";";
                arch<<it->nombres;
                arch<<";";
                arch<<it->fechavuelo;
                arch<<";";
                arch<<it->fechacompra;
                arch<<";";
                arch<<it->horacompra;
      //arch<<";";
      //arch<<it->tipo;
                arch<<std::endl;
            }
        }

        for (std::list<Venta>::iterator it= ita->tiquetesModificados.begin(); it!=ita->tiquetesModificados.end(); it++)
        {
           arch<<it->agencia;
           arch<<"_";
           arch<<it->Idventa;
           arch<<";";
           arch<<it->vuelo;
           arch<<";";
           arch<<it->cedula;
           arch<<";";
           arch<<it->apellidos;
           arch<<";";
           arch<<it->nombres;
           arch<<";";
           arch<<it->fechavuelo;
           arch<<";";
           arch<<it->fechacompra;
           arch<<";";
           arch<<it->horacompra;
      //arch<<";";
      //arch<<it->tipo;
           arch<<std::endl;
       }
   }
   arch.close();
}

}

void llenarlistasarbol(std::list< std::string>& listaorigenes, std::list< std::string>& listaidvuelo, std::list< std::string>& listafecha, std::list<Vuelo>  pr,std::list<Vuelo> prog)
{
    for(std::list<Vuelo>::iterator it = pr.begin(); it!= pr.end(); it++)
    {
        listaidvuelo.push_back(it->codigo);
        listaorigenes.push_back(it->origen);
        listaorigenes.push_back(it->destino);
    }
    for(std::list<Vuelo>::iterator ita = prog.begin(); ita!= prog.end(); ita++)
    {
     listafecha.push_back(ita->dia);
 }

}

void llenarlistaCedulas(std::list<Venta> listaTiquetes, std::list<std::string>& listaa)
{
    for(std::list<Venta>::iterator itb = listaTiquetes.begin(); itb != listaTiquetes.end(); itb++)
    {
        listaa.push_back(itb->cedula);
    }


}

void llenarAgenciasArbol(std::list< std::string>& listaa, std::list<Agencia>  pr)
{
    for(std::list<Agencia>::iterator it = pr.begin(); it!= pr.end(); it++)
    {
        listaa.push_back(it->user);
    }

}
void llenarlistaVentasArbol(std::list< std::string>& listaa,std::list<Venta> pr)
{
   for(std::list<Venta>::iterator it = pr.begin(); it!= pr.end(); it++)
   {
    //std::cout<<it->agencia+"_"+std::to_string(it->Idventa)<<std::endl;
    listaa.push_back(it->agencia+"_"+std::to_string(it->Idventa));
}
}

std::list<std::string> autocomp (std::string input,ArbolGeneral<std::string>* aG)
{
    std::list<std::string> listica;
    Nodo<std::string>* posi = buscartrie(input,aG->obtenerRaiz());
    if (posi!=NULL)
    { 
        getauto(posi,listica);
        return listica;
    }
    return listica;

}

Nodo<std::string >* buscartrie(std::string  n, Nodo<std::string >* inicio)
{
    if(inicio->obtenerDato()==n)
    {
        return inicio;
    }
    if(!(inicio->obtenerLista().empty()))
    {

        std::list<Nodo<std::string >*> listAux = inicio->obtenerLista();
        auto iT = listAux.begin();
        for(; iT!=listAux.end(); iT++)
        {
            Nodo<std::string >* nuevo = *(iT);
            Nodo<std::string >* aux = buscartrie(n, nuevo);
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

void getauto(Nodo<std::string>* inicio, std::list<std::string>& listaa)
{
    if(inicio->obtenerLista().empty())        
        listaa.push_back(inicio->obtenerDato());

    if(!(inicio->obtenerLista().empty()))
    {
        std::list<Nodo<std::string>*> listAux = inicio->obtenerLista();
        auto iT = listAux.begin();
        for(; iT!=listAux.end(); iT++)
        {
            Nodo<std::string>* aux = *(iT);
            getauto(aux,listaa);
        }
    }

}

void llenar(std::list<std::string>listica,ArbolGeneral<std::string>* aG){
 for(std::list<std::string>::iterator it = listica.begin() ; it != listica.end(); it++)
 {
    std::string putito = *it;

    int i;
    for(i = 0; i < putito.length(); i++)
    {
        std::string hijo = putito.substr(0,i+1);

        if(i == 0)
        {
            if(!(aG->buscar(hijo)))
            {
                aG->insertarNodo("#+",hijo);
            }
        }
        else 
        {
            std::string padre = putito.substr(0,i);
            if((aG->buscar(padre)))
            {
                aG->insertarNodo(padre,hijo);
            }
        }
    }
}
}

void imprimirVuelosR(std::list<Vuelo> as)
{
    std::cout<<"                                    ****LISTA DE VUELOS****                                    "<<std::endl;
    for (std::list<Vuelo>::iterator it = as.begin(); it != as.end(); it++)
    {
        std::cout<<"--------------------------------------------------------------------------------------------------------------"<<std::endl;
        std::cout<<"Codigo: "<<it->codigo<<"   Dia: "<<it->dia<<"   Hora: "<<it->hora;
        std::cout<<"    Origen: "<<it->origen<<"    Destino: "<<it->destino<<"      Duracion: "<<it->duracion<<std::endl;
        std::cout<<"--------------------------------------------------------------------------------------------------------------"<<std::endl;

    }
}

void llenarGrafoTiempo(std::list<Vuelo> vuelospr, Graph<std::string, long>& grafito, Graph<std::string, float>& grafito2, Graph<std::string, int>& grafito3){
    std::list<Vuelo>::iterator it;

    for(it=vuelospr.begin(); it!=vuelospr.end(); it++){
        std::string inicio = (*it).origen;
        std::string fin = (*it).destino;

        long ida = grafito.AddNode(inicio);
        long idb = grafito.AddNode(fin);
        grafito2.AddNode(inicio);
        grafito2.AddNode(fin);
        grafito3.AddNode(inicio);
        grafito3.AddNode(fin);

        grafito.AddArc(ida, idb, tiempoVuelo((*it).duracion)+120);//CON LOS 120 MINUTOS ACA
        grafito2.AddArc(ida, idb, (*it).costo);
        grafito3.AddArc(ida, idb, 1);
    }

}



Vuelo buscarVueloDisponible(std::string origen, std::string destino, std::list<Vuelo> as){
    Vuelo encontrado;

    for (std::list<Vuelo>::iterator it = as.begin(); it != as.end(); it++)
    {
        if(it->origen.compare(origen)==0 && it->destino.compare(destino)==0)
        {
            encontrado = (*it);
            break;
        }
    }
    return encontrado;
}

bool change(std::list<Vuelo>& disponibles, std::list<Vuelo>& programados, std::list<Agencia>& ag,std::string cc, std::string idviejo,std::string idnuevo){
    std::list<Agencia>::iterator it;
    std::list<Venta>::iterator its;
    std::list<Venta>::iterator itsM;
    bool bien = false;
    for(it = ag.begin(); it!=ag.end(); it++)
    {
        std::list<Venta> tempV = it->tiquetesVendidos;
        std::list<Venta> tempM = it->tiquetesModificados;
        std::list<Venta> tempC = it->tiquetesCancelados;
        for(its = it->tiquetesVendidos.begin(); its != it->tiquetesVendidos.end(); its++)
        {
            if((*its).cedula==cc &&(*its).vuelo==idviejo && (*its).tipo == 'v')
            {
                Vuelo volar = buscarVueloR(disponibles,idnuevo);
                Vuelo volarAn = buscarVueloR(disponibles,(*its).vuelo);
                std::string pr = volar.dia;

                std::string datep = (*its).fechavuelo;
                std::string dia = diaFecha(datep);

                std::string nuevafecha= fechachange(datep,dia,pr);
                //std::cout<<datep<<",,,,,,"<<nuevafecha;
                (*its).tipo = 'm';
                Venta nueva;
                nueva.agencia=(*its).agencia;
                nueva.Idventa=(*its).Idventa;
                nueva.vuelo=idnuevo;
                nueva.cedula=(*its).cedula;
                nueva.apellidos=(*its).apellidos;
                nueva.nombres=(*its).nombres;
                nueva.fechavuelo=nuevafecha;
                nueva.fechacompra = fechaActual();
                nueva.horacompra = horaActual();
                nueva.tipo = 'm';

                sillasVueloPositiva(programados, (*its).vuelo);

                if(!buscarVuelo(programados, volar.codigo))
                {
                    volar.dia = nuevafecha;
                    volar.sillas--;
                    programados.push_back(volar);
                }
                else
                {
                    sillasVuelo(programados, volar.codigo);
                }
                tempM.push_back(nueva);

                std::cout<<"Tarifa Anterior: $"<<volarAn.costo<<std::endl;
                std::cout<<"Tarifa Nueva: $"<<volar.costo<<std::endl;

                bien=true;
            }
            else if((*its).cedula==cc &&(*its).vuelo==idviejo && (*its).tipo == 'm'){

                for(itsM = it->tiquetesModificados.begin(); itsM != it->tiquetesModificados.end(); itsM++){
                    if((*itsM).cedula==cc &&(*itsM).vuelo==idviejo && (*itsM).tipo == 'm'){
                        Vuelo volar = buscarVueloR(disponibles,idnuevo);
                        Vuelo volarAn = buscarVueloR(disponibles,(*its).vuelo);
                        std::string pr = volar.dia;

                        std::string datep = (*itsM).fechavuelo;
                        std::string dia = diaFecha(datep);

                        std::string nuevafecha= fechachange(datep,dia,pr);
                //std::cout<<datep<<",,,,,,"<<nuevafecha;
                        (*itsM).tipo = 'm';
                        Venta nueva;
                        nueva.agencia=(*itsM).agencia;
                        nueva.Idventa=(*itsM).Idventa;
                        nueva.vuelo=idnuevo;
                        nueva.cedula=(*itsM).cedula;
                        nueva.apellidos=(*itsM).apellidos;
                        nueva.nombres=(*itsM).nombres;
                        nueva.fechavuelo=nuevafecha;
                        nueva.fechacompra = fechaActual();
                        nueva.horacompra = horaActual();
                        nueva.tipo = 'm';

                        sillasVueloPositiva(programados, (*itsM).vuelo);

                        if(!buscarVuelo(programados, volar.codigo))
                        {
                            volar.dia = nuevafecha;
                            volar.sillas--;
                            programados.push_back(volar);
                        }
                        else
                        {
                            sillasVuelo(programados, volar.codigo);
                        }
                        borrarTiqueteN(tempM, (*itsM));
                        tempM.push_back(nueva);

                        std::cout<<"Tarifa Anterior: $"<<volarAn.costo<<std::endl;
                        std::cout<<"Tarifa Nueva: $"<<volar.costo<<std::endl;

                        bien=true;
                    }
                }

            }
        }

        it->tiquetesModificados = tempM;
    }
    return bien;
}