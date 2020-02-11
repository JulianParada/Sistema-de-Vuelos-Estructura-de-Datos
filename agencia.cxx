#include"agencia.h"
#include"venta.h"
#include"vuelo.h"
#include"sistema.h"
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

std::list<Vuelo> generarReporteDisponibles(std::list<Vuelo>& as)
{
    std::list<Vuelo> resultado;

    for (std::list<Vuelo>::iterator it = as.begin(); it != as.end(); it++)
    {
        if(it->sillas > 0)
        {
            resultado.push_back(*it);
        }
    }

    return resultado;
}

std::list<Vuelo> generarReporteOrigenFecha(std::list<Vuelo>& as, std::string origen,std::string fecha)
{
    std::list<Vuelo> resultado;

    for (std::list<Vuelo>::iterator it = as.begin(); it != as.end(); it++)
    {
        if(it->origen.compare(origen) == 0)
        {
            std::string day = diaFecha(fecha);
            if(it->dia.compare(day) == 0)
            {
                resultado.push_back(*it);
            }
        }
    }
    return resultado;
}

std::list<Vuelo> generarReporteOrigen(std::list<Vuelo>& as, std::string origen)
{
    std::list<Vuelo> resultado;

    for (std::list<Vuelo>::iterator it = as.begin(); it != as.end(); it++)
    {
        if(it->origen.compare(origen) == 0)
        {
            resultado.push_back(*it);
        }
    }
    return resultado;
}

Vuelo encontrarVuelo(std::list<Vuelo> as, std::string id, std::string d)
{
    Vuelo found;

    for (std::list<Vuelo>::iterator it = as.begin(); it != as.end(); it++)
    {
        if(it->codigo.compare(id)==0 && it->dia.compare(d) == 0)
        {
            found = (*it);
            break;
        }
    }
    return found;
}

Venta venderVueloSencillo(std::list<Vuelo> as, std::string id, std::string fch, Agencia& ag, std::list<Venta>& tv, std::list<Vuelo>& pr,  std::list<Agencia>& emd)
{
    Venta v;
    Vuelo fl;
    std::list<Vuelo> disp;
    disp = generarReporteDisponibles(as);
    std::string day = diaFecha(fch);
    fl = encontrarVuelo(disp, id, day);

    if(!fl.codigo.empty() && fl.dia.compare(day) == 0)
    {
        v.agencia = ag.user;
        v.Idventa = ag.tiquetesVendidos.size()+1000;
        v.vuelo = fl.codigo;
        v.tipo = 'v';
        std::string nombres;
        std::string apellidos;
        std::string cedula;

        std::cout<<"Ingrese sus nombres: ";
        std::getline(std::cin,nombres);

        std::cout<<"Ingrese sus apellidos: ";
        std::getline(std::cin,apellidos);

        std::cout<<"Ingrese su cedula: ";
        std::getline(std::cin,cedula);

        v.cedula = cedula;
        v.nombres = nombres;
        v.apellidos = apellidos;
        v.fechavuelo = fch;
        v.fechacompra = fechaActual();
        v.horacompra = horaActual();

        tv.push_back(v);

        Vuelo volar = buscarVueloR(as, v.vuelo);
        if(!buscarVuelo(pr, volar.codigo))
        {
            volar.dia = v.fechavuelo;
            volar.sillas--;
            pr.push_back(volar);
        }
        else
        {
            sillasVuelo(pr, volar.codigo);
        }
    }
    else
    {
        std::cout<<"No hay vuelos que coincidan"<<std::endl;
    }

    for(std::list<Agencia>::iterator it = emd.begin(); it != emd.end(); it++)
    {
        if(it->user == ag.user)
        {
            it->tiquetesVendidos = tv;
        }
    }

    return v;
}

void reportMoney(Agencia ag, std::list<Vuelo>& programados)
{
    int acumVendidos = 0;
    int ganAcumModificados = 0;
    int perAcumModificados = 0;
    int ganAcumCancelados = 0;
    int perAcumCancelados = 0;
    int balancePagos = 0;
    int balanceGanado = 0;
    int totalUtilidad = 0;

    std::list<Venta> auxV = ag.tiquetesVendidos;
    std::list<Venta> auxM = ag.tiquetesModificados;
    std::list<Venta> auxC = ag.tiquetesCancelados;
    std::list<Venta>::iterator it; 

    float diferencia = 0;

    for (it = auxV.begin(); it != auxV.end(); it++)
    {   
        Vuelo nuevo;
        Vuelo original;

        if(it->tipo == 'v') 
        {
            Vuelo s = buscarVueloR(programados, it->vuelo);
            acumVendidos = acumVendidos + s.costo;
            
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
            std::cout<<"    Dinero Ganado por este vuelo: $"<<s.costo<<std::endl;
        }
        else if(it->tipo == 'm') 
        {
            Venta asO = *it;
            std::cout<<"----------------------------------------------------------------------------------------------"<<std::endl;
            std::cout<<"Agencia: "<<it->agencia<<"   ID: "<<it->Idventa<<"  Vuelo: "<<it->vuelo<<"  Tipo: ";
            if(it->tipo=='v')
                std::cout<<"Vendido";
            if(it->tipo=='m')
                std::cout<<"Tiquete Modificado";
            if(it->tipo=='c')
                std::cout<<"Cancelado";
            std::cout<<std::endl;
            std::cout<<"    Cedula: "<<it->cedula<<"    Apellidos: "<<it->apellidos<<"    Nombres: "<<it->nombres<<std::endl;
            
            original = buscarVueloR(programados, it->vuelo);
            Vuelo nuevo;

            for (std::list<Venta>::iterator its = auxM.begin(); its != auxM.end(); its++)
            {
                if((it->cedula == its->cedula) && (it->nombres == its->nombres))
                {
                    nuevo = buscarVueloR(programados, its->vuelo);
                    
                    std::cout<<"Agencia: "<<its->agencia<<"   ID: "<<its->Idventa<<"  Vuelo: "<<its->vuelo<<"  Tipo: ";
                    if(its->tipo=='v')
                        std::cout<<"Vendido";
                    if(its->tipo=='m')
                        std::cout<<"Tiquete Definitivo";
                    if(its->tipo=='c')
                        std::cout<<"Cancelado";
                    std::cout<<std::endl;
                    std::cout<<"    Cedula: "<<its->cedula<<"    Apellidos: "<<its->apellidos<<"    Nombres: "<<its->nombres<<std::endl;
                    std::cout<<std::endl;
                    std::cout<<"    Costo final por este vuelo: $"<<nuevo.costo<<std::endl;
                    break;
                }
                

            }

            diferencia = 0;
            diferencia = nuevo.costo - original.costo;

            if(diferencia >= 0)
            {
                ganAcumModificados = ganAcumModificados + diferencia;
                acumVendidos = acumVendidos + original.costo;
                std::cout<<"    Dinero ganado por este vuelo: $"<<diferencia<<std::endl;
                std::cout<<"    Dinero perdido por este vuelo: $0"<<std::endl;
            }if(diferencia < 0)
            {
                diferencia = diferencia * (-1);
                perAcumModificados = perAcumModificados + diferencia;
                acumVendidos = acumVendidos + original.costo;
                std::cout<<"    Dinero perdido por este vuelo: $"<<diferencia<<std::endl;
                std::cout<<"    Dinero ganado por este vuelo: $0"<<std::endl;
            }
        }
        else if(it->tipo == 'c') 
        {
            std::cout<<"----------------------------------------------------------------------------------------------"<<std::endl;
            std::cout<<"Agencia: "<<it->agencia<<"   ID: "<<it->Idventa<<"  Vuelo: "<<it->vuelo<<"  Tipo: ";
            if(it->tipo=='v')
                std::cout<<"Vendido";
            if(it->tipo=='m')
                std::cout<<"Tiquete Modificado";
            if(it->tipo=='c')
                std::cout<<"Tiquete Cancelado";
            std::cout<<std::endl;
            std::cout<<"    Cedula: "<<it->cedula<<"    Apellidos: "<<it->apellidos<<"    Nombres: "<<it->nombres<<std::endl;

            Vuelo s = buscarVueloR(programados, it->vuelo);
            bool existe = buscarTiquete(auxC, (*it));
            if(!s.codigo.empty() && existe)
            {
                ganAcumCancelados = ganAcumCancelados + (s.costo * 0.15);
                perAcumCancelados = perAcumCancelados + (s.costo * 0.85);
                std::cout<<"    Dinero ganado por este vuelo: $"<<(s.costo * 0.15)<<std::endl;
                std::cout<<"    Dinero perdido por este vuelo: $"<<(s.costo * 0.85)<<std::endl;
            }
        }
    }
    std::cout<<"----------------------------------------------------------------------------------------------"<<std::endl;
    balancePagos = perAcumModificados + perAcumCancelados;
    balanceGanado = acumVendidos + ganAcumModificados + ganAcumCancelados;

    totalUtilidad = balanceGanado - balancePagos;
    std::cout<<"Ingresos por ventas : $"<<acumVendidos<<std::endl;
    std::cout<<"Egresos por cancelaciones : $"<<perAcumCancelados<<std::endl;
    std::cout<<"Ingresos por cancelaciones : $"<<ganAcumCancelados<<std::endl;
    std::cout<<"Egresos por modificaciones : $"<<perAcumModificados<<std::endl;
    std::cout<<"Ingresos por modificaciones : $"<<ganAcumModificados<<std::endl;

    std::cout<<"Dinero recibido total : $"<<balanceGanado<<std::endl;
    std::cout<<"Dinero pagado total : $"<<balancePagos<<std::endl;
    std::cout<<"TOTAL GANADO: $"<<totalUtilidad<<std::endl;

    //std::cout<<"                              ****LISTA DE VENTAS****                                      "<<std::endl;
    //imprimirTiquetes(ag.tiquetesVendidos);
}

bool cancelar(std::string ids, Agencia& ag, std::list<Vuelo>& programados,std::list<Agencia>& as,std::list<Vuelo>& dsp)
{
    bool esvuelo=false;
    std::list<Venta> auxV = ag.tiquetesVendidos;
    std::list<Venta> auxM = ag.tiquetesModificados;
    std::list<Venta> auxC = ag.tiquetesCancelados;

    if(buscarVuelo(dsp, ids))
    {
        esvuelo = true;
    }
    int id=-1;
    if(esvuelo==false)
    {
        id = atoi(ids.c_str());
    }
    

    bool check = false;


    for (std::list<Venta>::iterator it = auxV.begin(); it != auxV.end(); it++)
    {

        if(esvuelo==false)
        {
            if(it->agencia.compare(ag.user) == 0 && it->Idventa == id)
            {
                if(it->tipo == 'v') 
                {
                    it->tipo = 'c';
                    Venta v = *it;
                    //std::cout<<v.vuelo;
                    v.vuelo = "0";
                    auxC.push_back(v);
                    sillasVueloPositiva(programados, it->vuelo);
                    check = true;
                }
                else if(it->tipo == 'm') 
                {

                    Venta tiq = buscarTiqueteR(auxM, (*it));
                    if(tiq.Idventa == id)
                    {
                        
                        it->tipo = 'c';
                        //Venta v = *it;
                        //std::cout<<v.vuelo;
                        //v.vuelo = "0";
                        borrarTiqueteN(auxM, tiq);
                        tiq.tipo = 'c';
                        std::string vuelito = tiq.vuelo;
                        tiq.vuelo = "0";
                        auxC.push_back(tiq);
                        sillasVueloPositiva(programados, vuelito);
                        check = true;
                    }
                }
                else if(it->tipo == 'c') 
                {
                    std::cout<<"El paquete ya se ha cancelado"<<std::endl;
                }
            }
            else if(it->Idventa != id && it->tipo == 'm')
            {
                Venta tiq = buscarTiqueteR(auxM, (*it));
                if(tiq.Idventa == id)
                {
                    it->tipo = 'c';
                    std::string vuelito = tiq.vuelo;
                    tiq.vuelo = "0";
                    borrarTiqueteN(auxM, tiq);
                    tiq.tipo = 'c';
                    auxC.push_back(tiq);
                    sillasVueloPositiva(programados, vuelito);
                    check = true;
                }
            }
        }
        else
        {
            if(it->agencia.compare(ag.user) == 0 && it->vuelo == ids)
            {
                if(it->tipo == 'v') 
                {
                    it->tipo = 'c';
                    Venta v = *it;
                    //std::cout<<v.vuelo;
                    v.vuelo = "0";
                    
                    auxC.push_back(v);
                    sillasVueloPositiva(programados, it->vuelo);
                    check = true;
                }
                else if(it->tipo == 'm') 
                {

                    Venta tiq = buscarTiqueteR(auxM, (*it));
                    if(tiq.vuelo == ids)
                    {
                        it->tipo = 'c';
                        
                        borrarTiquete(auxM, tiq);
                        std::string vuelito = tiq.vuelo;
                        tiq.vuelo = "0";
                        tiq.tipo = 'c';
                        auxC.push_back(tiq);
                        sillasVueloPositiva(programados, vuelito);
                        check = true;
                    }
                }
                else if(it->tipo == 'c') 
                {
                    std::cout<<"El paquete ya se ha cancelado"<<std::endl;
                }
            }
            if(it->vuelo != ids && it->tipo == 'm')
            {
                Venta tiq = buscarTiqueteR(auxM, (*it));
                if(tiq.vuelo == ids)
                {
                    it->tipo = 'c';
                    std::string vuelito = tiq.vuelo;
                    tiq.vuelo = "0";
                    //std::cout<<tiq.vuelo;
                    borrarTiqueteN(auxM, tiq);
                    tiq.tipo = 'c';
                    auxC.push_back(tiq);
                    sillasVueloPositiva(programados, vuelito);
                    check = true;
                }
            }
        }
    }

    ag.tiquetesVendidos = auxV;
    ag.tiquetesModificados = auxM;
    ag.tiquetesCancelados = auxC;


    for (std::list<Agencia>::iterator ita = as.begin(); ita != as.end(); ita++)
    {
        if(ita->user.compare(ag.user) == 0)
        {
            ita->tiquetesVendidos = auxV;
            ita->tiquetesModificados = auxM;
            ita->tiquetesCancelados = auxC;
        }
    }
    return check;
}

std::list<Venta> seleccionarVendidos(std::list<Venta>& as){

    std::list<Venta> listica;
    std::list<Venta>::iterator it;


    for (it = as.begin(); it != as.end(); it ++){
        if ((*it).tipo == 'v'){
            listica.push_back(*it);
        }
    }
    return listica;
}