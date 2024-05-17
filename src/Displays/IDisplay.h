#ifndef IDISPLAY_H
#define IDISPLAY_H
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
class IDisplay
{
    public:
        virtual ~IDisplay() = default;
        virtual void PintarPantalla()=0;
        virtual void Init()=0;
        virtual uint32_t  getMilliseconsEachLoop() const=0;
        virtual bool displayAnimate() =0;

};

#endif



