#include"fechaHora.h"
#include <string>
#include <string.h>
#include <iostream>

std::string horaActual()
{
    time_t rawtime;
    time (&rawtime);
    std::string fyh=ctime(&rawtime);


    char date[50];
    strcpy(date, fyh.c_str());

    char *p = strtok(date, " ");
    p = strtok(NULL, " ");

    p = strtok(NULL, " ");
    std::string d= p;

    p = strtok(NULL, " :");
    char *h= p;

    p = strtok(NULL, ":");
    std::string minu = p;

    p = strtok(NULL, " ");
    p = strtok(NULL, " ");
    std::string a = p;

    strcat(h,minu.c_str());

    return h;
}

std::string fechaActual()
{
    time_t rawtime;
    time (&rawtime);
    std::string fyh=ctime(&rawtime);


    char date[50];
    strcpy(date, fyh.c_str());

    char *p = strtok(date, " ");
    p = strtok(NULL, " ");

    std::string me;
    if(strcmp(p,"Jan")==0)
        me="01";
    if(strcmp(p,"Feb")==0)
        me="02";
    if(strcmp(p,"Mar")==0)
        me="03";
    if(strcmp(p,"Apr")==0)
        me="04";
    if(strcmp(p,"May")==0)
        me="05";
    if(strcmp(p,"Jun")==0)
        me="06";
    if(strcmp(p,"Jul")==0)
        me="07";
    if(strcmp(p,"Aug")==0)
        me="08";
    if(strcmp(p,"Sep")==0)
        me="09";
    if(strcmp(p,"Oct")==0)
        me="10";
    if(strcmp(p,"Nov")==0)
        me="11";
    if(strcmp(p,"Dec")==0)
        me="12";

    p = strtok(NULL, " ");
    std::string d= p;

    p = strtok(NULL, " :");
    char *h= p;

    p = strtok(NULL, ":");
    std::string minu = p;

    p = strtok(NULL, " ");
    p = strtok(NULL, " \n");
    char *a = p;

    strcat(a,me.c_str());
    strcat(a,d.c_str());
    return a;
}

std::string diaFecha(std::string fch)
{
    std::string day;

    char *date = new char[8];
    strcpy(date, fch.c_str());
    tm tm1;
    sscanf(date,"%4d%2d%2d",&tm1.tm_year,&tm1.tm_mon,&tm1.tm_mday);

    int ano = tm1.tm_year;
    int mes = tm1.tm_mon;
    int fecha = tm1.tm_mday;
    int dia;
    int modulo_mes;
    std::string dias[7] = {"domingo","lunes","martes","miercoles","jueves","viernes","sabado"};
    if((ano%4==0) && (ano%100!=0) || (ano%400==0))
    {
        if(mes==1)
            modulo_mes=0;
        if(mes==2)
            modulo_mes=3;
        if(mes==3)
            modulo_mes=4;
        if(mes==4)
            modulo_mes=0;
        if(mes==5)
            modulo_mes=2;
        if(mes==6)
            modulo_mes=5;
        if(mes==7)
            modulo_mes=0;
        if(mes==8)
            modulo_mes=3;
        if(mes==9)
            modulo_mes=6;
        if(mes==10)
            modulo_mes=1;
        if(mes==11)
            modulo_mes=4;
        if(mes==12)
            modulo_mes=6;
    }
    else
    {
        if(mes==1)
            modulo_mes=0;
        if(mes==2)
            modulo_mes=3;
        if(mes==3)
            modulo_mes=3;
        if(mes==4)
            modulo_mes=6;
        if(mes==5)
            modulo_mes=1;
        if(mes==6)
            modulo_mes=4;
        if(mes==7)
            modulo_mes=6;
        if(mes==8)
            modulo_mes=2;
        if(mes==9)
            modulo_mes=5;
        if(mes==10)
            modulo_mes=0;
        if(mes==11)
            modulo_mes=3;
        if(mes==12)
            modulo_mes=5;
    }
    dia=  ((ano-1)%7+ ((ano-1)/4 -(3*((ano-1)/100+1)/4))%7+modulo_mes+fecha%7)%7;

    for(int i =0; i<=8; i++)
    {
        if(i == dia)
            day = dias[i];
    }

    return day;
}

long tiempoVuelo(std::string hora){
    std::string horas = hora.substr(0,2);
    std::string minutos = hora.substr(2,4);
    long h = std::stol(horas)*60;
    long m = std::stol(minutos);
    long hm = h+m;
    return hm;
}

std::string fechachange( std::string fecha, std::string origen, std::string destino)//int main()
{
    //
    //std::string fecha ;
    //std::cout <<"INgrese una fecha"<< std::endl;
    //std::cin>>fecha;

    std::string dia = fecha.substr(6,2);
    std::string mes = fecha.substr(4,2);
    std::string ano = fecha.substr(0,4);

    int d=stoi(dia);
    int m=stoi(mes);
    int y=stoi(ano);
   // std::cout<<d<<"__________"<<m<<"_______"<<y<<std::endl;
    dia="x";
    mes="y";
    ano="n";
    std::string x;
    bool cambio;
    int j=0;
    if(origen=="lunes")
        j=0;
    if(origen=="martes")
        j=1;
    if(origen=="miercoles")
        j=2;
    if(origen=="jueves")
        j=3;
    if(origen=="viernes")
        j=4;
    if(origen=="sabado")
        j=5;
    if(origen=="domingo")
        j=6;
    x=destino;
    std::string dias [7]= {"lunes","martes","miercoles","jueves","viernes","sabado","domingo"};
    int i =0;
    //std::cout<<"WWWWWWWWWWWWWWWWWWWWWWWWWW"<<dias[j]<<std::endl;
    for ( i =0; i <7; i++)
    {
        if(j==7)
            j=0;
        // std::cout<<dias[j]<<std::endl;
        if(dias[j]==x)
        {
            // std::cout<<"WWWWWWWWWWWWWWWWWWWWWWWWWW"<<std::endl;
            //j++;
            break;
        }
        j++;
    }
    if(i==0)
        i=7;

    //std::cout<<d<<"/"<<m<<"/"<<y<<"         AAAAAAAAAAAAAAAAA"<<i<<std::endl;

    for(int x=0; x<i; x++)
    {
        cambio=false;
        if(m==1||m==3||m==5||m==7||m==10||m==12)
        {
            if(d==31)
            {
                d=1;
                m++;
                cambio=true;
            }
            if(m==13)
            {
                m=1;
                y++;
            }
            if(cambio==false)
                d++;
        }
        if(m==4||m==6||m==9||m==11||m==8)
        {
            if(d==30)
            {
                d=1;
                m++;
                cambio=true;
            }
            if(m==13)
            {
                m=1;
                y++;
            }
            if(cambio==false)
                d++;
        }
        if(m==2)
        {
            if(d==28)
            {
                d=1;
                m++;
                cambio=true;
            }
            if(m==13)
            {
                m=1;
                y++;
            }
            if(cambio==false)
                d++;
        }
    }
   // std::cout<<d<<"/"<<m<<"/"<<y<<""<<std::endl;
    dia =std::to_string(d);
    mes =std::to_string(m);
    ano =std::to_string(y);
    if(d<10)
        dia="0"+dia;
    if(m<10)
        mes="0"+mes;
   // std::cout<<dia<<"*"<<mes<<"*"<<ano<<""<<std::endl;
    std::string result = ano+mes+dia;
    //std::cout<<"AAAAAAAAAAAAAAAA"<<result<<std::endl;
    //std::string result = ano+mes+dia;

    return result;
}