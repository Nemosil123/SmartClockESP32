#ifndef MNGRDISPLAY_H
#define MNGRDISPLAY_H
#include "Displays/IDisplay.h"
#include "Displays/DisplayTexto.h"
#include "Displays/DisplayHora.h"
#include "Displays/DisplayDibujos.h"
#include "Displays/DisplayConfig.h"
#include <MD_Parola.h>
#ifdef MODULO_WIFI_PRESENTE
#include "ezTime.h"
#else
#include "TimeJor.h"
#endif



#define NUM_SCREENS 4

class MngrDisplays
{
private:
    u_int8_t idxDisplayActivo;

   // MD_Parola screenLED;
public:
    struct sCatalogEfects
    {
        textEffect_t  effect;   // text effect to display
        uint16_t      speed;    // speed multiplier of library default
        uint16_t      pause;    // pause multiplier for library default
    };
    



    IDisplay* LstDisplays[NUM_SCREENS];

    //static sCatalogEfects efectoFijo = { PA_PRINT, 1, 1};
    MngrDisplays();//MD_Parola pantalla);
    ~MngrDisplays();
    void AddDisplay(IDisplay* dsp, u_int8_t idx);
    u_int8_t getNumDisplays();
#ifdef MODULO_WIFI_PRESENTE
    void Init(Timezone* hora);
#else
    void Init(HoraLocal* hora);
#endif
    IDisplay* SetDisplayHora();
    IDisplay* GetActiveDisplay();
    IDisplay* GetDisplay(u_int8_t idx);
    IDisplay* NextDisplay();
    u_int8_t getIdxActive();
 
    static sCatalogEfects getEfectoRnd();
    sCatalogEfects getEfectoFijo();

};

#endif

