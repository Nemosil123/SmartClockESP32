#ifndef IDISPLAY_H
#define IDISPLAY_H
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "ConfigGeneral.h"

class IDisplay
{
    private:


    public:
        struct ConfigDisp
        {
           // bool efectoRnd;
            //bool fraseMotivadora;
            textEffect_t EfectoScreen;
            textPosition_t posicion;
        };
        ConfigDisp cnf;
        virtual ~IDisplay() = default;
        virtual  char* getTexto()=0;
        virtual void Init(MD_Parola* pantalla)=0;

       // virtual uint32_t  getMilliseconsSleep() const=0;
        virtual std::string getNombre()=0;
        virtual void setCnf(ConfigGeneral cnf)=0;
        virtual void Pintar(MD_Parola* pantalla)=0;

};

#endif



