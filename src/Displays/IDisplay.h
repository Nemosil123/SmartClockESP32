#ifndef IDISPLAY_H
#define IDISPLAY_H
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "ConfigDisp.h"

class IDisplay
{
    private:


    public:
        ConfigDisp cnf;
        virtual ~IDisplay() = default;
        virtual char* getTexto(bool &esMotiv)=0;
        virtual char* getTexto()=0;
        virtual void Init(MD_Parola* pantalla)=0;
        virtual uint32_t  getMilliseconsSleep() const=0;
        virtual char* getNombre()=0;
        virtual void setCnf(bool efectoRnd, bool fraseMotivadora)=0;

};

#endif



