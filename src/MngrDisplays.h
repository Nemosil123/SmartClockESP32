#ifndef MNGRDISPLAY_H
#define MNGRDISPLAY_H
#include "Displays/IDisplay.h"
#include "Displays/DisplayTexto.h"
#include <MD_Parola.h>

#define NUM_SCREENS 1

class MngrDisplays
{
private:
    u_int8_t idxDisplayActivo;
    u_int8_t brillo =5;

   // MD_Parola screenLED;
public:
    struct sCatalogEfects
    {
        textEffect_t  effect;   // text effect to display
        uint16_t      speed;    // speed multiplier of library default
        uint16_t      pause;    // pause multiplier for library default
    };
    

u_int8_t iIdxEfecto = 0;


    IDisplay* LstDisplays[NUM_SCREENS];

    //static sCatalogEfects efectoFijo = { PA_PRINT, 1, 1};
    MngrDisplays();//MD_Parola pantalla);
    ~MngrDisplays();
    void AddDisplay(IDisplay* dsp, u_int8_t idx);
    u_int8_t getNumDisplays();
    void Init();
    IDisplay* GetActiveDisplay();
    IDisplay* GetDisplay(u_int8_t idx);
    IDisplay* NextDisplay();
    void setBrillo(u_int8_t b);
    u_int8_t getBrillo();
    sCatalogEfects getEfectoRnd();
    sCatalogEfects getEfectoFijo();

};

#endif

