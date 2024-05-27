#ifndef CONFIGGENERAL_H
#define CONFIGGENERAL_H
#include "TimeJor.h"

class ConfigGeneral
{
private:
    /* data */
public:
    char* textoPrincipal;
    HoraLocal* horaActual;
    HoraLocal* horaAlarma;
    bool AlarmaActiva;

    ConfigGeneral(HoraLocal *ahora);

};





#endif
