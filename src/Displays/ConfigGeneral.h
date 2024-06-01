#ifndef CONFIGGENERAL_H
#define CONFIGGENERAL_H
#include "TimeJor.h"

class ConfigGeneral
{
private:
    /* data */
public:
    char* textoMensajes;
    char* textoAlarma;
    char* textoDibujos;
    HoraLocal* horaActual;
    HoraLocal* horaAlarma;
    bool AlarmaActiva;
    bool AutoCambiarScreens;

    ConfigGeneral(HoraLocal *ahora);

};





#endif
