// =========================================================================
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// =========================================================================

#include "Console.h"
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>

// -------------------------------------------------------------------------
Console::
Console( )
: Superclass( )
{
}

// -------------------------------------------------------------------------
Console::
Console( const std::string& prompt, const std::string archEmpresas, const std::string archVuelos, const std::string archTiquetes  )
: Superclass( prompt )
{


  this->ingresado = false;

  if(llenarListaEmpresas(archEmpresas, sistemaP.empresasDisp))
  {
    std::cout<<"Se cargo el archivo de empresas" << std::endl;
        //imprimirEmpresas(sistemaP.empresasDisp);

  }
  if(llenarListaVuelos(archVuelos, sistemaP.vuelosDisp))
  {
    std::cout<<"Se cargo el archivo de vuelos" << std::endl;
        //imprimirVuelos(sistemaP.vuelosDisp);
  }
  if(llenarListaTiquetes(archTiquetes, sistemaP.listaTiquetes))
  {
    std::cout<<"Se cargo el archivo de tiquetes" << std::endl;
        //imprimirTiquetes(sistemaP.vuelosDisp);
  }

  llenarListasAgencias(sistemaP.listaTiquetes, sistemaP.empresasDisp, sistemaP.vuelosDisp);
  //imprimirEmpresas(sistemaP.empresasDisp);
  //imprimirVuelos(sistemaP.vuelosDisp);
  actualizarAsientos(sistemaP.vuelosDisp, sistemaP.vuelosProgramados, sistemaP.empresasDisp);
  //imprimirVuelos(sistemaP.vuelosProgramados);

  std::cout << "---------------------------------------\n";

  ARorigenes = new ArbolGeneral<std::string>("#+");
  ARfechas = new ArbolGeneral<std::string>("#+");
  ARvuelos = new ArbolGeneral<std::string>("#+");
  ARap = new ArbolGeneral<std::string>("#+");
  ARAgencias = new ArbolGeneral<std::string>("#+");
  ARVentas = new ArbolGeneral<std::string>("#+");
  ARcedulas = new ArbolGeneral<std::string>("#+");

  listica.push_back("login");
  listica.push_back("logout");
  listica.push_back("exit");
  listica.push_back("report inventory");
  listica.push_back("report money");
  listica.push_back("report flights");
  listica.push_back("sell");
  listica.push_back("consolidate");
  listica.push_back("help");
  listica.push_back("cancel");
  listica.push_back("path");
  listica.push_back("change");

  llenarlistasarbol(listaorigenes,listaidvuelo,listafecha,this->sistemaP.vuelosDisp,this->sistemaP.vuelosProgramados);
  llenarAgenciasArbol(listaAgencias, this->sistemaP.empresasDisp);
  llenarlistaVentasArbol(listaIdVentas,this->sistemaP.listaTiquetes);
  llenarlistaCedulas(this->sistemaP.listaTiquetes, listaCedulas);

  llenar(listica,ARap);
  llenar(listaorigenes,ARorigenes);
  llenar(listafecha,ARfechas);
  llenar(listaidvuelo,ARvuelos);
  llenar(listaIdVentas,ARVentas);
  llenar(listaAgencias,ARAgencias);
  llenar(listaCedulas,ARcedulas);

/*
  gt = new Graph<std::string, long> ;
  gc = new Graph<std::string, float> ;
  gp = new Graph<std::string, int> ;
*/

}

// -------------------------------------------------------------------------
Console::
~Console( )
{
}

// -------------------------------------------------------------------------
int Console::
trigger( const std::string& s )
{
  //std::cout<<this->sistemaP.vuelosDisp.size();
  //std::cout<<"Numero de vertices: "<<this->gt.getNumberOfVertices()<<std::endl;
  //std::cout<<"Numero de aristas: "<<this->gt.getNumEdges()<<std::endl;
  //std::cout<<"Numero de vertices: "<<this->gc.getNumberOfVertices()<<std::endl;
  //std::cout<<"Numero de aristas: "<<this->gc.getNumEdges()<<std::endl;

  typedef Graph< std::string, long > TGraph ;
  typedef Graph< std::string, float > TGraph2 ;
  typedef Graph< std::string, int > TGraph3 ;
  TGraph gt;
  TGraph2 gc;
  TGraph3 gp;


  llenarGrafoTiempo(this->sistemaP.vuelosDisp, gt, gc, gp);
  //llenarGrafoCosto(this->sistemaP.vuelosDisp, gc);

  //std::cout<<gt.GetVerticesSize()<<std::endl;

  std::string comando;
  std::string dato1;
  std::string dato2;
  std::string dato3;
  std::string dato4;

  std::cout << "---------------------------------------\n";
  //std::cout<<gt.GetVerticesSize()<<std::endl;
  std::stringstream ss(s);
  getline(ss,comando,' ');
  if(comando=="login")
  {
    if(!this->ingresado)
    {
      getline(ss,dato1);
      std::string password;
      std::cout<< "Ingrese contrasena por favor: ";
      std::cin>>password;
      std::cin.ignore();
      this->ingresado = login(this->sistemaP.empresasDisp, dato1, password, this->agenciaP);

      if(this->ingresado)
      {
        //imprimirTiquetes(agenciaP.tiquetesVendidos);
        //imprimirTiquetes(agenciaP.tiquetesModificados);
        //imprimirTiquetes(agenciaP.tiquetesCancelados);
        std::cout << "Sesion iniciada correctamente." << std::endl;
        //change(this->sistemaP.vuelosDisp,this->sistemaP.vuelosProgramados, this->sistemaP.empresasDisp,"CC1234567904","RX407", "RX408");
          //thi-disponibles, std::list<Vuelo>& programados, std::list<Agencia>& ag,std::string cc, std::string idviejo,std::string idnuevo)
      }
      else
        std::cout << "Usuario o contrasena invalidas. Intente de nuevo." << std::endl;
    }
    else
    {
      std::cout<<"Ya hay una sesion activa "<< std::endl;
    }
  }
  else if(comando=="logout")
  {
    if(this->ingresado)
    {
      this->agenciaP.tiquetesVendidos.clear();
      this->agenciaP.tiquetesModificados.clear();
      this->agenciaP.tiquetesCancelados.clear();
      this->agenciaP.user = "";
      this->agenciaP.password = "";
      this->ingresado = false;

      std::cout<<"Sesion cerrada correctamente "<< std::endl;
    }
    else
    {
      std::cout<<"No tiene acceso a esta funcionalidad "<< std::endl;
    }
  }

  else if(comando=="report")
  {
    ss >> comando;
    if(comando == "flights" )
    {
      if(this->ingresado)
      {
        std::list<Vuelo> reporte;
        if(ss>>dato1)
        {
          if(ss>>dato2)
          {
            if(ARorigenes->buscar(dato1 + " " + dato2))
            {
              reporte = generarReporteOrigen(this->sistemaP.vuelosDisp, dato1+" "+dato2);
            }
            else
            {
              reporte = generarReporteOrigenFecha(this->sistemaP.vuelosDisp, dato1, dato2);
            }
          }
          else
          {
            reporte = generarReporteOrigen(this->sistemaP.vuelosDisp, dato1);
          }

        }
        else
        {
          reporte = generarReporteDisponibles(this->sistemaP.vuelosDisp);
        }

        if(!reporte.empty())
        {
          std::cout<<"Reporte generado correctamente "<<std::endl;
          //std::cout<<reporte.size()<<std::endl;
          imprimirVuelosR(reporte);
        }
        else
        {
          std::cout<<"No existen vuelos con las espeficaciones dadas."<<std::endl;
        }
      }
      else
      {
        std::cout<<"No tiene acceso a esta funcionalidad "<< std::endl;
      }

    }
    else if(comando == "inventory")
    {
      if(this->ingresado)
      {
        std::list<Agencia>::iterator it;
        for(it = this->sistemaP.empresasDisp.begin(); it!=this->sistemaP.empresasDisp.end(); it++)
        {
          std::cout<<std::endl;
          std::list<Venta> listota = seleccionarVendidos(it->tiquetesVendidos);
          std::cout<<"++++INVENTARIO DE LA AGENCIA: "<<it->user<<"++++"<<std::endl;
          if(!listota.empty())
          {
            std::cout<<"                        ****LISTA DE TIQUETES VENDIDOS****                                      "<<std::endl;
            imprimirTiquetes(listota);
          }
          else
          {
            std::cout<<"                        ****NO HAY TIQUETES VENDIDOS****                                      "<<std::endl;
          }

          if(!it->tiquetesModificados.empty())
          {
            std::cout<<"                      ****LISTA DE TIQUETES MODIFICADOS****                                     "<<std::endl;
            imprimirTiquetes(it->tiquetesModificados);
          }
          else
          {
            std::cout<<"                      ****NO HAY TIQUETES MODIFICADOS****                                     "<<std::endl;
          }

          if(!it->tiquetesCancelados.empty())
          {
            std::cout<<"                       ****LISTA DE TIQUETES CANCELADOS****                                     "<<std::endl;
            imprimirTiquetes(it->tiquetesCancelados);
          }
          else
          {
            std::cout<<"                       ****NO HAY TIQUETES CANCELADOS****                                     "<<std::endl;
          }
          std::cout<<std::endl;
          std::cout<<std::endl;
        }
      }
      else
      {
        std::cout<<"No tiene acceso a esta funcionalidad "<< std::endl;
      }

    }
    else if(comando == "money")
    {
      if(this->ingresado)
      {
        reportMoney(this->agenciaP, this->sistemaP.vuelosDisp);

                    //imprimirTiquetes(agenciaP.tiquetesModificados);
                    //imprimirTiquetes(agenciaP.tiquetesCancelados);

      }
      else
      {
        std::cout<<"No tiene acceso a esta funcionalidad "<< std::endl;
        std::cout<<"No tiene acceso a esta funcionalidad "<< std::endl;
      }
    }
  }
  else if(comando=="path")
  {
    std::vector<std::string> vertices = gt.getVertices();
    
    

    if(this->ingresado)
    {
      std::vector< long > pathTiempo;
      std::vector< long > pathCosto;
      std::vector< long > pathOther;
      bool ban = false;
      bool ban2 = false;
      if(ss>>dato1)
      {
        if(ss>>dato2)
        {
          if(ss>>dato3)
          {
            if(ss>>dato4)
            {
              if(ARorigenes->buscar(dato3 + " " + dato4))
              {
                ban = true;
                pathTiempo = gt.GetShortestPath( gt.getIndexof(dato1 + " " + dato2), gt.getIndexof(dato3 + " " + dato4));
                pathCosto = gc.GetShortestPath( gc.getIndexof(dato1 + " " + dato2), gc.getIndexof(dato3 + " " + dato4));
                pathOther = gp.GetShortestPath( gp.getIndexof(dato1 + " " + dato2), gp.getIndexof(dato3 + " " + dato4));
              }
            }

            else if(ARorigenes->buscar(dato1 + " " + dato2) && !ban && !ban2)
            {
              ban2 = true;
              pathTiempo = gt.GetShortestPath( gt.getIndexof(dato1 + " " + dato2), gt.getIndexof(dato3));
              pathCosto = gc.GetShortestPath( gc.getIndexof(dato1 + " " + dato2), gc.getIndexof(dato3));
              pathOther = gp.GetShortestPath( gp.getIndexof(dato1 + " " + dato2), gp.getIndexof(dato3));
            }
            else if(ARorigenes->buscar(dato2 + " " + dato3) && !ban && !ban2)
            {
              ban2 = true;
              pathTiempo = gt.GetShortestPath( gt.getIndexof(dato1), gt.getIndexof(dato2 + " " + dato3));
              pathCosto = gc.GetShortestPath( gc.getIndexof(dato1), gc.getIndexof(dato2 + " " + dato3));
              pathOther = gp.GetShortestPath( gp.getIndexof(dato1), gp.getIndexof(dato2 + " " + dato3));
            }
            
          }
          if(!ban && !ban2){
            pathTiempo = gt.GetShortestPath( gt.getIndexof(dato1), gt.getIndexof(dato2));
            pathCosto = gc.GetShortestPath( gc.getIndexof(dato1), gc.getIndexof(dato2));
            pathOther = gp.GetShortestPath( gp.getIndexof(dato1), gp.getIndexof(dato2));
          }
        }
      }
      if(!pathTiempo.empty()){
        std::cout<<"-------------------------------------------------------------------------"<<std::endl;
        std::cout<<"                  ***RUTA MAS RAPIDA***          "<<std::endl;
        std::cout<<"Comenzando con ";
        std::vector< long > aux;
        std::vector<long>::reverse_iterator rIt = pathTiempo.rbegin();

        for( ; rIt != pathTiempo.rend() ; rIt++ ){
          //std::cout<< gt.GetNode(*rIt)   <<std::endl;
          aux.push_back(*rIt);
        }

        for( unsigned int i = 0; i < aux.size( )-1; ++i ){

          Vuelo v = buscarVueloDisponible(vertices[ aux[ i ] ], vertices[ aux[ i+1 ] ], this->sistemaP.vuelosDisp);
          std::cout<<"el vuelo "<<v.codigo;
          std::cout<<" desde " <<vertices[ aux[ i ] ] <<" hacia "<<vertices[ aux[ i+1 ] ]<<std::endl;
          if(i < aux.size( )-2)
          {
            std::cout<<"y seguido por ";
          }
        }
      }
      else{
        std::cout<<"No hay ruta mas rapida"<<std::endl;
      }
          //std::vector<std::string> vertices = gc.getVertices();
      if(!pathCosto.empty()){
        std::cout<<"-------------------------------------------------------------------------"<<std::endl;
        std::cout<<"                  ***RUTA MAS ECONOMICA***         "<<std::endl;
        std::cout<<"Comenzando con ";
        std::vector< long > aux;
        std::vector<long>::reverse_iterator rIt = pathCosto.rbegin();

        for( ; rIt != pathCosto.rend() ; rIt++ ){
          //std::cout<< gt.GetNode(*rIt)   <<std::endl;
          aux.push_back(*rIt);
        }

        for( unsigned int i = 0; i < aux.size( )-1; ++i ){

          Vuelo v = buscarVueloDisponible(vertices[ aux[ i ] ], vertices[ aux[ i+1 ] ], this->sistemaP.vuelosDisp);
          std::cout<<"el vuelo "<<v.codigo;
          std::cout<<" desde " <<vertices[ aux[ i ] ] <<" hacia "<<vertices[ aux[ i+1 ] ]<<std::endl;
          if(i < aux.size( )-2)
          {
            std::cout<<"y seguido por ";
          }
        }
        std::cout<<"-------------------------------------------------------------------------"<<std::endl;
      }
      else{
        std::cout<<"No hay ruta mas economica"<<std::endl;
      }

      if(!pathOther.empty()){
        std::cout<<"                  ***RUTA DE MENOS PARADAS***          "<<std::endl;
        std::cout<<"Comenzando con ";
        std::vector< long > aux;
        std::vector<long>::reverse_iterator rIt = pathOther.rbegin();

        for( ; rIt != pathOther.rend() ; rIt++ ){
          //std::cout<< gt.GetNode(*rIt)   <<std::endl;
          aux.push_back(*rIt);
        }

        for( unsigned int i = 0; i < aux.size( )-1; ++i ){

          Vuelo v = buscarVueloDisponible(vertices[ aux[ i ] ], vertices[ aux[ i+1 ] ], this->sistemaP.vuelosDisp);
          std::cout<<"el vuelo "<<v.codigo;
          std::cout<<" desde " <<vertices[ aux[ i ] ] <<" hacia "<<vertices[ aux[ i+1 ] ]<<std::endl;
          if(i < aux.size( )-2)
          {
            std::cout<<"y seguido por ";
          }
        }
        std::cout<<"-------------------------------------------------------------------------"<<std::endl;
      }
      else{
        std::cout<<"No hay ruta de menos paradas"<<std::endl;
      }
    }
    else
    {
      std::cout<<"No tiene acceso a esta funcionalidad "<< std::endl;
    }
  }
  else if(comando=="sell")
  {
    if(this->ingresado)
    {
      ss >> dato1;
      ss >> dato2;
      Venta v =  venderVueloSencillo(this->sistemaP.vuelosDisp,dato1,dato2,this->agenciaP, this->agenciaP.tiquetesVendidos, this->sistemaP.vuelosProgramados, this->sistemaP.empresasDisp);
      if(!v.vuelo.empty())
      {
        imprimirVenta(v);
                    //imprimirVuelos(sistemaP.vuelosProgramados);
      }
      else
      {
        std::cout<<"No se realizo la venta correctamente" << std::endl;
      }
    }
    else
    {
      std::cout<<"No tiene acceso a esta funcionalidad "<< std::endl;
    }
  }
  else if(comando=="consolidate")
  {
    if(this->ingresado)
    {
      consolidarI(this->agenciaP, this->sistemaP.vuelosProgramados, this->sistemaP.empresasDisp, this->sistemaP.vuelosDisp);
      //imprimirVuelos(this->sistemaP.vuelosProgramados);
      llenarlistasarbol(listaorigenes,listaidvuelo,listafecha,this->sistemaP.vuelosDisp,this->sistemaP.vuelosProgramados);
      llenarlistaVentasArbol(listaIdVentas,this->sistemaP.listaTiquetes);

    }
    else
    {
      std::cout<<"No tiene acceso a esta funcionalidad "<< std::endl;
    }
  }

  else if(comando=="cancel")
  {
    if(this->ingresado)
    {
      ss >> dato1;
      std::string agencia =dato1.substr(0,4);
      std::string id= dato1.substr(5,5);
      std::list<Agencia>::iterator its;
      Agencia ag;

      for(its= this->sistemaP.empresasDisp.begin();its != this->sistemaP.empresasDisp.end();its++)
      {
        if((*its).user==agencia)
          ag=(*its);

      }
      bool borradoCorrecto = cancelar(id, ag, this->sistemaP.vuelosProgramados, this->sistemaP.empresasDisp, this->sistemaP.vuelosDisp);
      if(borradoCorrecto)
      {
        llenarlistasarbol(listaorigenes,listaidvuelo,listafecha,this->sistemaP.vuelosDisp,this->sistemaP.vuelosProgramados);
        std::cout<<"Se borro el paquete o tiquete correctamente"<<std::endl;
      }
      else
      {
        std::cout<<"NO se borro el paquete o tiquete correctamente"<<std::endl;
      }
    }
    else
    {
      std::cout<<"No tiene acceso a esta funcionalidad "<< std::endl;
    }
  }
  else if(comando == "change")
  {
    if(this->ingresado)
    {
      ss>>dato1;
      ss>>dato2;
      ss>>dato3;
      bool correct = change(this->sistemaP.vuelosDisp,this->sistemaP.vuelosProgramados, this->sistemaP.empresasDisp, dato1,dato2, dato3);
      if(correct)
      {
        std::cout<<"Se cambio el paquete o tiquete correctamente"<<std::endl;
      }
      else
      {
        std::cout<<"NO se cambio el paquete o tiquete correctamente"<<std::endl;
      }
    }
    else
    {
      std::cout<<"No tiene acceso a esta funcionalidad "<< std::endl;
    }
  }
  else if(comando=="help")
  {
    if(ss >> dato1)
    {
      if(dato1 == "login")
      {
        std::cout<<"    login <id_agencia>" << std::endl;
        std::cout<<"        -Inicia sesion de una agencia -> login XX00, luego se le pedira que ingrese la contraseña."<< std::endl;
      }
      if(dato1 == "report")
      {
        ss >> dato2;
        if(dato2 == "flights")
        {
          std::cout<<"    report flights [origen] [fecha]"<< std::endl;
          std::cout<<"        -Genera el reporte de vuelos, ya sea: "<< std::endl;
          std::cout<<"           ->report flights, genera el reporte de vuelos con sillas disponibles."<< std::endl;
          std::cout<<"           ->report flights [origen], genera el reporte de vuelos con sillas disponibles y que salen de ese origen."<< std::endl;
          std::cout<<"           ->report flights [origen] [fecha], genera el reporte de vuelos con sillas disponibles, que salen de ese"<< std::endl;
          std::cout<<"             origen y el dia de esa fecha."<< std::endl;
        }
        if(dato2 == "inventory")
        {
          std::cout<<"    report inventory"<< std::endl;
          std::cout<<"        -Genera el reporte de los tiquetes vendidos por agencia autenticada."<< std::endl;
        }
        if(dato2 == "money")
        {
          std::cout<<"    report money"<< std::endl;
          std::cout<<"        -Debe estar autenticado. Genera un reporte de las ventas, pagos y ganacias que ha tenido la agencia."<< std::endl;
        }
        else if(dato2 != "flights" && dato2 != "inventory" && dato2 != "money")
        {
          std::cout<<"El comando no existe"<<std::endl;
        }
      }
      if(dato1 == "consolidate")
      {
        std::cout<<"    consolidate"<< std::endl;
        std::cout<<"        -Debe estar AUTENTICADO. Comando que se ejecuta al cierre del día: eliminar de la base de datos todos "<< std::endl;
        std::cout<<"         los datos que están relacionados con transacciones pasadas (es decir, vuelos que ya se realizaron)."<< std::endl;
      }
      if(dato1 == "sell")
      {
        std::cout<<"    sell <id_vuelo> <fecha>"<< std::endl;
        std::cout<<"        -Debe estar AUTENTICADO. Vende un vuelo sencillo de un solo trayecto -> sell XX000 YYYYMMDD,"<< std::endl;
        std::cout<<"         se verifica que el vuelo exista y salga en el dia que corresponde a esa fecha,"<< std::endl;
        std::cout<<"         seguidamente se le solicita que ingrese los nombres, apellidos y identificacion del viajero."<< std::endl;
      }
      if(dato1 == "path")
      {
        std::cout<<"    path <origen> <destino>"<< std::endl;
        std::cout<<"        -Debe estar AUTENTICADO. Muestra tres rutas sugeridad entre un origen y un destino dado,"<< std::endl;
        std::cout<<"         se verifica que el origen y destino exista, las rutas sigeridas son la mas economica,"<< std::endl;
        std::cout<<"         la de menor duracion y la de menos escalas."<< std::endl;
      }
      if(dato1 == "change")
      {
        std::cout<<"    change <id pasajero> <id vuelo original> <id nuevo vuelo>"<< std::endl;
        std::cout<<"        -Debe estar AUTENTICADO. Dado el identificador de un pasajero, el identificador de "<< std::endl;
        std::cout<<"         los vuelos original y nuevo, respectivamente; cambia los datos del vuelo. "<< std::endl;
        std::cout<<"         Ademas, informa el cambio de la tarifa"<< std::endl;
      }
      if(dato1 == "cancel")
      {
        std::cout<<"    cancel <id>"<< std::endl;
        std::cout<<"        -Debe estar AUTENTICADO. Cancela todos los paquetes o tiquetes que administre la agencia"<< std::endl;
        std::cout<<"         que tengan el Id de la venta ingresado."<< std::endl;
      }
      if(dato1 == "logout")
      {
        std::cout<<"    logout"<< std::endl;
        std::cout<<"        -Debe estar AUTENTICADO. Termina la sesion de la agencia autenticada."<< std::endl;
      }
      if(dato1 == "exit")
      {
        std::cout<<"    exit"<< std::endl;
        std::cout<<"        -Cierra el sistema en ejecucion."<< std::endl;
      }
      else if(dato1 != "login" && dato1 != "report" && dato1 != "consolidate" && dato1 != "sell" && dato1 != "cancel" && dato1 != "logout" && dato1 != "exit" && dato1 != "path" && dato1 != "change")
      {
        std::cout<<"El comando no existe"<<std::endl;
      }
    }
    else
    {
      std::cout<<"Comandos disponibles: " << std::endl;
      std::cout<<"    login <id_agencia>" << std::endl;
      std::cout<<"    report flights [origen] [fecha]"<< std::endl;
      std::cout<<"    report inventory"<< std::endl;
      std::cout<<"    report money"<< std::endl;
      std::cout<<"    consolidate"<< std::endl;
      std::cout<<"    sell <id_vuelo> <fecha>"<< std::endl;
      std::cout<<"    path <origen> <destino>"<<std::endl;
      std::cout<<"    change <id pasajero> <id vuelo original> <id nuevo vuelo>"<<std::endl;
      std::cout<<"    cancel <id>"<< std::endl;
      std::cout<<"    logout"<< std::endl;
      std::cout<<"    exit"<< std::endl;
    }
  }
  else if(comando == "exit")
  {
    this->quit();
  }
  else
    std::cout << "El comando no existe" << std::endl;

}


// -------------------------------------------------------------------------
int Console::
hotkeys( char c )
{
  if( c == Superclass::TAB )
  {

    std::string leido = this->getBuffer();
    std::stringstream ss(leido);
    std::string token;
    std::vector<std::string> arra;

    while(getline(ss, token, ' '))
    {
      //ss >> leido;
      arra.push_back(token);
      //std::cout<<leido;
    }



    if(arra.size() == 1)
    {
      std::list<std::string> listota=  autocomp(arra[0],ARap);
      if(listota.size() == 1)
      {
        std::string pr = listota.front();
        this->setBuffer(pr);
        int tam = arra[0].size();
        int tam2 = pr.size();

        std::string mostrar = pr.substr(tam,tam2);
        std::cout<<mostrar;
      }else
      {
        std::cout<<std::endl;
        for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
        {
          std::cout<<*it<<std::endl;
        }
        if(arra[0] == "r" || arra[0] == "re" || arra[0] == "rep" || arra[0] == "repo" || arra[0] == "repor" || arra[0] == "report")
        {
          this->setBuffer("report ");
          std::cout<<"$"<<"report ";
        }
        else
        {
          std::cout<<"$"<<arra[0];
        }
      }
    }
    else if(arra.size()==2)
    {
      if(arra[0] == "login" || arra[0] == "sell" || arra[0] == "cancel" || arra[0] == "path" || arra[0] == "change")
      {
        if(arra[0] == "login")
        {
          std::list<std::string> listota=  autocomp(arra[1],ARAgencias);
          if(listota.size() == 1)
          {
            std::string pr = listota.front();
            this->setBuffer(pr);
            std::string mostrar = resta(arra[0], pr);
            std::cout<<mostrar;
          }else
          {
            std::cout<<std::endl;
            for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
            {
              std::cout<<"login "<<*it<<std::endl;
            }
            std::cout<<"$"<<arra[0]<<" "<<arra[1];
          }
        }
        else if(arra[0] == "path")
        {
          std::list<std::string> listota=  autocomp(arra[1],ARorigenes);
          if(listota.size() == 1)
          {
            std::string pr = listota.front();
            this->setBuffer(arra[0]+" "+pr);
            int tam = arra[1].size();
            int tam2 = pr.size();

            std::string mostrar = pr.substr(tam,tam2);
          //std::string mostrar = resta(arra[2],pr);
            std::cout<<mostrar;


          }else
          {
            std::cout<<std::endl;
            for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
            {
              std::cout<<"path "<<*it<<std::endl;
            }
            std::cout<<"$"<<arra[0]<<" "<<arra[1];
          }
        }
        else if(arra[0] == "change")
        {
          std::list<std::string> listota=  autocomp(arra[1],ARcedulas);
          if(listota.size() == 1)
          {
            std::string pr = listota.front();
            this->setBuffer(arra[0]+" "+pr);
            int tam = arra[1].size();
            int tam2 = pr.size();

            std::string mostrar = pr.substr(tam,tam2);
          //std::string mostrar = resta(arra[2],pr);
            std::cout<<mostrar;


          }else
          {
            std::cout<<std::endl;
            for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
            {
              std::cout<<"change "<<*it<<std::endl;
            }
            std::cout<<"$"<<arra[0]<<" "<<arra[1];
          }
        }
        else if(arra[0] == "sell")
        {

          std::list<std::string> listota=  autocomp(arra[1],ARvuelos);
          if(listota.size() == 1)
          {
            std::string pr = listota.front();
            this->setBuffer(pr);
            std::string mostrar = resta(arra[0], pr);
            std::cout<<mostrar;
          }else
          {
            std::cout<<std::endl;
            for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
            {
              std::cout<<"sell "<<*it<<std::endl;
            }
            std::cout<<"$"<<arra[0]<<" "<<arra[1];
          }
        }
        else if(arra[0] == "cancel")
        {

          std::list<std::string> listota;

          if(ARVentas->buscar(arra[1]))
          {
            listota =  autocomp(arra[1],ARVentas);
          }
          else
          {
            listota =  autocomp(arra[1],ARvuelos);
          }

          if(listota.size() == 1)
          {
            std::string pr = listota.front();
            this->setBuffer(pr);
            std::string mostrar = resta(arra[0], pr);
            std::cout<<mostrar;
          }else
          {
            std::cout<<std::endl;
            for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
            {
              std::cout<<"cancel "<<*it<<std::endl;
            }
            std::cout<<"$"<<arra[0]<<" "<<arra[1];
          }
        }
      }
      else if (arra[0] == "report")
      {

        std::list<std::string> listota=  autocomp(leido,ARap);
        if(listota.size() == 1)
        {
          std::string pr = listota.front();
          this->setBuffer(pr);

          std::stringstream ss2(pr);
          std::string token2;
          std::vector<std::string> arra2;

          while(getline(ss2, token2, ' '))
          {
      //ss >> leido;
            arra2.push_back(token2);
      //std::cout<<leido;
          }

          std::string mostrar = resta(arra2[1], arra[1]);
          std::cout<<mostrar;
        }else
        {
          std::cout<<std::endl;
          for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
          {
            std::cout<<*it<<std::endl;
          }
          std::cout<<"$"<<arra[0]<<" "<<arra[1];
        }
      }
      else if(arra[0] == "help")
      {
        std::list<std::string> listota=  autocomp(arra[1],ARap);
        if(listota.size() == 1)
        {
          std::string pr = listota.front();
          this->setBuffer(arra[0]+" "+pr);
          std::string mostrar = resta(arra[1], pr);
          std::cout<<mostrar;
        }else
        {
          std::cout<<std::endl;
          for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
          {
            std::cout<<"help "<<*it<<std::endl;
          }
          std::cout<<"$"<<arra[0]<<" "<<arra[1];
        }
      }

    }
    else if(arra.size()==3)
    {
      if (arra[0] == "report")
      {
        std::list<std::string> listota=  autocomp(arra[2],ARorigenes);
        if(listota.size() == 1)
        {
          std::string pr = listota.front();
          this->setBuffer(arra[0]+" "+arra[1]+" "+pr);
          int tam = arra[2].size();
          int tam2 = pr.size();

          std::string mostrar = pr.substr(tam,tam2);
          //std::string mostrar = resta(arra[2],pr);
          std::cout<<mostrar;
        }else
        {
          std::cout<<std::endl;
          for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
          {
            std::cout<<"report "<<arra[1]<<" "<<*it<<std::endl;
          }
          std::cout<<"$"<<arra[0]<<" "<<arra[1]<<" "<<arra[2];
        }
      }
      else if (arra[0] == "sell")
      {
        std::list<std::string> listota=  autocomp(arra[2],ARfechas);
        if(listota.size() == 1)
        {
          std::string pr = listota.front();
          this->setBuffer(arra[0]+" "+arra[1]+" "+pr);
          int tam = arra[2].size();
          int tam2 = pr.size();

          std::string mostrar = pr.substr(tam,tam2);//resta(arra[2],pr);
          //std::cout<<resta(arra[2],pr);
          std::cout<<mostrar;
        }else
        {
          std::cout<<std::endl;
          for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
          {
            std::cout<<"sell "<<arra[1]<<" "<<*it<<std::endl;
          }
          std::cout<<"$"<<arra[0]<<" "<<arra[1]<<" "<<arra[2];
        }
      }
      else if(arra[0] == "change")
      {
        std::list<std::string> listota=  autocomp(arra[2],ARvuelos);
        if(listota.size() == 1)
        {
          std::string pr = listota.front();
          this->setBuffer(arra[0]+" "+arra[1]+" "+pr);
          int tam = arra[2].size();
          int tam2 = pr.size();

          std::string mostrar = pr.substr(tam,tam2);//resta(arra[2],pr);
          //std::cout<<resta(arra[2],pr);
          std::cout<<mostrar;
        }else
        {
          std::cout<<std::endl;
          for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
          {
            std::cout<<"change "<<arra[1]<<" "<<*it<<std::endl;
          }
          std::cout<<"$"<<arra[0]<<" "<<arra[1]<<" "<<arra[2];
        }
      }
      else if (arra[0] == "path")
      {
        std::list<std::string> listota=  autocomp(arra[1]+" "+arra[2],ARorigenes);
      //std::cout<<listota.size()<<std::endl;
        if(!listota.empty())
        {

          if(listota.size() == 1)
          {
            std::string pr = listota.front();
            this->setBuffer(arra[0]+" "+pr);
            std::string jaja =arra[1]+" "+arra[2];
            int tam = jaja.size();
            int tam2 = pr.size();

            std::string mostrar = pr.substr(tam,tam2);//resta(arra[2],pr);
            //std::cout<<resta(arra[2],pr);
            std::cout<<mostrar;
          }
          else
          {
            std::cout<<std::endl;
            for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
            {
              std::cout<<"report "<<arra[1]<<" "<<*it<<std::endl;
            }
            std::cout<<"$"<<arra[0]<<" "<<arra[1]<<" "<<arra[2];
          }
        }
        else
        {
          std::list<std::string> listota2=  autocomp(arra[2],ARorigenes);
          if(listota2.size() == 1)
          {
            std::string pr = listota2.front();
            this->setBuffer(arra[0]+" "+arra[1]+" "+pr);
            int tam = arra[2].size();
            int tam2 = pr.size();

          std::string mostrar = pr.substr(tam,tam2);//resta(arra[2],pr);
          //std::cout<<resta(arra[2],pr);
          std::cout<<mostrar;
        }else
        {
          std::cout<<std::endl;
          for (std::list<std::string>::iterator it = listota2.begin(); it != listota2.end(); it++)
          {
            std::cout<<"path "<<arra[1]<<" "<<*it<<std::endl;
          }
          std::cout<<"$"<<arra[0]<<" "<<arra[1]<<" "<<arra[2];
        }
      }
    }
    else if(arra[0] == "help")
    {
      std::list<std::string> listota=  autocomp(arra[1]+" "+arra[2],ARap);
      if(listota.size() == 1)
      {
        std::string pr = listota.front();
        this->setBuffer(arra[0]+" "+pr);
        std::string jaja =arra[1]+" "+arra[2];
        int tam = jaja.size();
        int tam2 = pr.size();

        std::string mostrar = pr.substr(tam,tam2);
        std::cout<<mostrar;
      }else
      {
        std::cout<<std::endl;
        for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
        {
          std::cout<<"help "<<*it<<std::endl;
        }
        std::cout<<"$"<<arra[0]<<" "<<arra[1];
      }
    }
  }
  else if(arra.size()==4)
  {
    if(arra[0] == "report")
    {
      std::list<std::string> listota=  autocomp(arra[2]+" "+arra[3],ARorigenes);
      //std::cout<<listota.size()<<std::endl;
      if(!listota.empty())
      {

        if(listota.size() == 1)
        {
          std::string pr = listota.front();
          this->setBuffer(arra[0]+" "+arra[1]+" "+pr);
          std::string jaja =arra[2]+" "+arra[3];
          int tam = jaja.size();
          int tam2 = pr.size();

            std::string mostrar = pr.substr(tam,tam2);//resta(arra[2],pr);
            //std::cout<<resta(arra[2],pr);
            std::cout<<mostrar;
          }
          else
          {
            std::cout<<std::endl;
            for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
            {
              std::cout<<"report "<<arra[1]<<" "<<*it<<std::endl;
            }
            std::cout<<"$"<<arra[0]<<" "<<arra[1]<<" "<<arra[2]<<" "<<arra[3];
          }
        }
        else
        {
          std::list<std::string> listota=  autocomp(arra[3],ARfechas);
          if(listota.size() == 1)
          {
            std::string pr = listota.front();
            this->setBuffer(arra[0]+" "+arra[1]+" "+arra[2]+" "+pr);
            int tam = arra[3].size();
            int tam2 = pr.size();

            std::string mostrar = pr.substr(tam,tam2);//resta(arra[2],pr);
            //std::cout<<resta(arra[2],pr);
            std::cout<<mostrar;
          }
          else
          {
            std::cout<<std::endl;
            for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
            {
              std::cout<<"report "<<arra[1]<<" "<<arra[2]<<" "<<*it<<std::endl;
            }
            std::cout<<"$"<<arra[0]<<" "<<arra[1]<<" "<<arra[2]<<" "<<arra[3];
          }
        }
      }
      if(arra[0] == "path")
      {
        std::list<std::string> listota=  autocomp(arra[2]+" "+arra[3],ARorigenes);
      //std::cout<<listota.size()<<std::endl;
        if(!listota.empty())
        {

          if(listota.size() == 1)
          {
            std::string pr = listota.front();
            this->setBuffer(arra[0]+" "+arra[1]+" "+pr);
            std::string jaja =arra[2]+" "+arra[3];
            int tam = jaja.size();
            int tam2 = pr.size();

            std::string mostrar = pr.substr(tam,tam2);//resta(arra[2],pr);
            //std::cout<<resta(arra[2],pr);
            std::cout<<mostrar;
          }
          else
          {
            std::cout<<std::endl;
            for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
            {
              std::cout<<"path "<<arra[1]<<" "<<*it<<std::endl;
            }
            std::cout<<"$"<<arra[0]<<" "<<arra[1]<<" "<<arra[2]<<" "<<arra[3];
          }
        }
        else
        {
          std::list<std::string> listota=  autocomp(arra[3],ARorigenes);
          if(listota.size() == 1)
          {
            std::string pr = listota.front();
            this->setBuffer(arra[0]+" "+arra[1]+" "+arra[2]+" "+pr);
            int tam = arra[3].size();
            int tam2 = pr.size();

            std::string mostrar = pr.substr(tam,tam2);//resta(arra[2],pr);
            //std::cout<<resta(arra[2],pr);
            std::cout<<mostrar;
          }
          else
          {
            std::cout<<std::endl;
            for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
            {
              std::cout<<"report "<<arra[1]<<" "<<arra[2]<<" "<<*it<<std::endl;
            }
            std::cout<<"$"<<arra[0]<<" "<<arra[1]<<" "<<arra[2]<<" "<<arra[3];
          }
        }
      }
      else if(arra[0] == "change")
      {
        std::list<std::string> listota=  autocomp(arra[3],ARvuelos);
        if(listota.size() == 1)
        {
          std::string pr = listota.front();
          this->setBuffer(arra[0]+" "+arra[1]+" "+arra[2]+" "+pr);
          int tam = arra[3].size();
          int tam2 = pr.size();

          std::string mostrar = pr.substr(tam,tam2);//resta(arra[2],pr);
          //std::cout<<resta(arra[2],pr);
          std::cout<<mostrar;
        }else
        {
          std::cout<<std::endl;
          for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
          {
            std::cout<<"change "<<arra[1]<<" "<<arra[2]<<" "<<*it<<std::endl;
          }
          std::cout<<"$"<<arra[0]<<" "<<arra[1]<<" "<<arra[2]<<" "<<arra[3];
        }
      }
    }
      //this->setBuffer("login");
    else if(arra.size()==5)
    {
      if(arra[0] == "path")
      {
        std::list<std::string> listota=  autocomp(arra[3]+" "+arra[4],ARorigenes);
      //std::cout<<listota.size()<<std::endl;
        if(!listota.empty())
        {

          if(listota.size() == 1)
          {
            std::string pr = listota.front();
            this->setBuffer(arra[0]+" "+arra[1]+" "+arra[2]+" "+pr);
            std::string jaja =arra[3]+" "+arra[4];
            int tam = jaja.size();
            int tam2 = pr.size();

            std::string mostrar = pr.substr(tam,tam2);//resta(arra[2],pr);
            //std::cout<<resta(arra[2],pr);
            std::cout<<mostrar;
          }
          else
          {
            std::cout<<std::endl;
            for (std::list<std::string>::iterator it = listota.begin(); it != listota.end(); it++)
            {
              std::cout<<"report "<<arra[1]<<" "<<arra[2]<<*it<<std::endl;
            }
            std::cout<<"$"<<arra[0]<<" "<<arra[1]<<" "<<arra[2]<<" "<<arra[3]<<" "<<arra[4];
          }
        }
      }
    }
  }
  else{
    return( 0 );
  }
}

// eof - Console.cxx
