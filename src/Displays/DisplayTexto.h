#ifndef DISPLAYTEXTO_H
#define DISPLAYTEXTO_H
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "IDisplay.h"

class DisplayTexto : public IDisplay
{
    private:
        MD_Parola screen;
    public:
        DisplayTexto(MD_Parola s);
        void PintarPantalla() override;
        void Init() override;
        uint32_t getMilliseconsEachLoop() const override;
        bool displayAnimate()  override;


};
#endif