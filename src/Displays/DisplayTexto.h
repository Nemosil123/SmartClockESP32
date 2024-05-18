#ifndef DISPLAYTEXTO_H
#define DISPLAYTEXTO_H
//#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "IDisplay.h"

class DisplayTexto : public IDisplay
{
    private:
       char* Texto;
       textEffect_t efectos[] = 
       {

       };   
    public:
        DisplayTexto(char* txt);
        char* getTexto() override;
        void Init() override;
        uint32_t getMilliseconsSleep() const override;
        //bool displayAnimate()  override;


};
#endif