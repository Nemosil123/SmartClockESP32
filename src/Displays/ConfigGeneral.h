#ifndef CONFIGGENERAL_H
#define CONFIGGENERAL_H
#include "TimeJor.h"

class ConfigGeneral
{
private:
    /* data */
public:
    char* textoMensajes;
    char* textoMensajes2;
    char* textoAlarma;
    char* textoDibujos;
    HoraLocal* horaActual;
    HoraLocal* horaAlarma;
    bool AlarmaActiva;
    bool AutoCambiarScreens;
    // u_int8_t HoraIniNoche;
    // u_int8_t HoraFinNoche;

    ConfigGeneral(HoraLocal *ahora);

};





#endif
