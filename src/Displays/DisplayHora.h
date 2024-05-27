#ifndef DISPLAYHORA_H
#define DISPLAYHORA_H
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "IDisplay.h"
#ifdef MODULO_WIFI_PRESENTE
#include "ezTime.h"
#else
#include "TimeJor.h"
#endif


class DisplayHora : public IDisplay
{
    private:
        // u_int8_t hora;
        // u_int8_t min;
       char* Texto;
#ifdef MODULO_WIFI_PRESENTE
        Timezone hora;
#else
        HoraLocal* horaActual ;
        HoraLocal* horaAlarm ;
        bool AlarmActiva=false ;
#endif

    public:
#ifdef MODULO_WIFI_PRESENTE
        DisplayHora(Timezone* hora);
#else
        DisplayHora(HoraLocal* hora);
#endif

         char* getTexto() override;
        void setTexto( char* );
        void Init(MD_Parola* pantalla) override;
        uint32_t getMilliseconsSleep() const override;
        std::string getNombre() override;
        void setCnf(ConfigGeneral cf) override;
        void Pintar(MD_Parola *pantalla) override;


};
#endif