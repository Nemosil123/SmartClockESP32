#ifndef CONFIGGENERAL_H
#define CONFIGGENERAL_H
#include "TimeJor.h"

class ConfigGeneral
{
private:


public:
    String textoMensajes;
    String textoMensajes2;
    String textoAlarma;
    String textoDibujos;
    HoraLocal* horaActual;
    HoraLocal* horaAlarma;
    bool AlarmaActiva;
    bool AutoCambiarScreens;
    u_int8_t HoraIniNoche;
    u_int8_t HoraFinNoche;
    /// @brief Día de la semana, contando 1 = Lunes y 7=Viernes
    u_int8_t diaActual;

    ConfigGeneral(HoraLocal *ahora);
    
};





#endif
