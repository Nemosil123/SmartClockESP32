#include "DisplayHora.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>  // Para strcpy

#ifdef MODULO_WIFI_PRESENTE
DisplayHora::DisplayHora(Timezone* hora) : horaTZ(hora)
#else
DisplayHora::DisplayHora(HoraLocal* h) : horaActual(h)
#endif
{
    cnf.EfectoScreen = PA_NO_EFFECT;
    cnf.posicion = PA_CENTER;
}

bool bUnoSiUnoNo = false;
long millisDia=0;
char* DisplayHora::getTexto()
{
    if(millis()-millisDia>30000)
    {
        millisDia= millis();
        return DiaSemanaLargo();
    }

    bUnoSiUnoNo = !bUnoSiUnoNo;

#ifdef MODULO_WIFI_PRESENTE
    String timeString = horaTZ.dateTime("H:i");
#else
    String timeString = horaActual->getFormattedTime();
        
#endif
    char* cstr = new char[timeString.length() + 1];
    std::strcpy(cstr, timeString.c_str());
    cstr[2]=(bUnoSiUnoNo ? ':' : ' ');
    if(AlarmActiva) cstr[5]='.';
    return cstr;
}


void DisplayHora::setTexto( char*)
{
}

void DisplayHora::Init(MD_Parola *pantalla)
{
}



void DisplayHora::Pintar(MD_Parola *pantalla)
{
    if(pantalla->displayAnimate())
    {

        char* t = getTexto();
        pantalla->displayText(t, PA_CENTER, 0, 1000, PA_NO_EFFECT, PA_NO_EFFECT);
        pantalla->displayReset();
    }
}


std::string DisplayHora::getNombre()
{
    return "Pantalla Hora";
}

void DisplayHora::setCnf(ConfigGeneral cf)
{
    horaActual = cf.horaActual;
    horaActual->diaActual = cf.diaActual;
    horaAlarm = cf.horaAlarma;
    AlarmActiva = cf.AlarmaActiva;
    //Serial.println("Dia: "+String(cf.diaActual));
    
    //setTexto(cf.textoAlarma);
}

char * DisplayHora::DiaSemanaLargo()
{
    
    switch (horaActual->diaActual)
    {
        case 1:
            return "Lunes";
            break;
        case 2:
            return "Martes";
            break;
        case 3:
            return "Miercoles";
            break;
        case 4:
            return "Jueves";
            break;
        case 5:
            return "Viernes";
            break;
        case 6:
            return "Sabado";
            break;
        case 7:
            return "Domingo";
            break;
        default:
            return "NO DIA";
            break;
    }
}


