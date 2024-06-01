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
char* DisplayHora::getTexto()
{
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
       // Serial.println(t);
        pantalla->displayText(t, PA_CENTER, 0, 1000, PA_NO_EFFECT, PA_NO_EFFECT);
        pantalla->displayReset();
    }
}

uint32_t DisplayHora::getMilliseconsSleep() const
{
    return 1000;
}

std::string DisplayHora::getNombre()
{
    return "Pantalla Hora";
}

void DisplayHora::setCnf(ConfigGeneral cf)
{
    horaActual = cf.horaActual;
    horaAlarm = cf.horaAlarma;
    AlarmActiva = cf.AlarmaActiva;
    setTexto(cf.textoAlarma);
}
