#include "MngrDisplays.h"
#define NUM_EFECTOS 28
// Global data

// Velocidad cuanto un valor es mayor mas despacio
const static MngrDisplays::sCatalogEfects catalogEfects[] =
{
   { PA_PRINT, 1, 1},
  { PA_SCROLL_UP, 50, 1},
  { PA_SCROLL_DOWN, 50, 1 },
  { PA_SCROLL_LEFT, 40, 1 },
  { PA_SCROLL_RIGHT, 40, 1 },
  { PA_SPRITE, 50, 1 },
  { PA_SLICE, 8, 1 },
  { PA_MESH, 50, 1 },
  { PA_FADE, 50, 1 },
  { PA_DISSOLVE, 50, 1 },
  { PA_BLINDS, 50, 1 },
  { PA_RANDOM, 25, 1 },
  { PA_WIPE, 25, 1 },
  { PA_WIPE_CURSOR, 25, 1 },
  { PA_SCAN_HORIZ, 25, 1 },
  { PA_SCAN_HORIZX, 25, 1 },
  { PA_SCAN_VERT, 70, 1 },
  { PA_SCAN_VERTX, 70, 1 },
  { PA_OPENING, 40, 1 },
  { PA_OPENING_CURSOR, 40, 1 },
  { PA_CLOSING, 40, 1 },
  { PA_CLOSING_CURSOR, 60, 1 },
  { PA_SCROLL_UP_LEFT, 60, 1 },
  { PA_SCROLL_UP_RIGHT, 60, 1 },
  { PA_SCROLL_DOWN_LEFT, 60, 1 },
  { PA_SCROLL_DOWN_RIGHT, 60, 1 },
  { PA_GROW_UP, 60, 1 },
  { PA_GROW_DOWN, 60, 1 },
};

static MngrDisplays::sCatalogEfects efFijo =  { PA_PRINT, 50, 10};

MngrDisplays::MngrDisplays(){}//MD_Parola pantalla) : screenLED(pantalla){}

MngrDisplays::~MngrDisplays(){}

void MngrDisplays::AddDisplay(IDisplay* dsp, u_int8_t idx)
{
    LstDisplays[idx] = dsp;
}

u_int8_t MngrDisplays::getNumDisplays()
{
    return NUM_SCREENS;
}

#ifdef MODULO_WIFI_PRESENTE
void MngrDisplays::Init(Timezone* hora)
#else
void MngrDisplays::Init(HoraLocal* hora)
#endif
{

    LstDisplays[0]=new DisplayTexto("inicio");
  Serial.println("Instancia 1");

    LstDisplays[1]= new DisplayHora(hora);
  Serial.println("Instancia 2");

    LstDisplays[2]= new DisplayDibujos();
  Serial.println("Instancia 3");

}


IDisplay *MngrDisplays::GetActiveDisplay()
{
    return LstDisplays[idxDisplayActivo];
}


IDisplay *MngrDisplays::GetDisplay(u_int8_t idx)
{
    if(idx>=NUM_SCREENS) return nullptr;
    return LstDisplays[idx];
}

IDisplay *MngrDisplays::NextDisplay()
{
    if(idxDisplayActivo+1>=NUM_SCREENS)
    {
        idxDisplayActivo=0;
    }
    idxDisplayActivo++;
    return GetActiveDisplay();
}

u_int8_t MngrDisplays::getIdxActive()
{
    return idxDisplayActivo;
}

static u_int8_t iIdxEfecto;
MngrDisplays::sCatalogEfects MngrDisplays::getEfectoRnd()
{
    if(iIdxEfecto+1>NUM_EFECTOS) iIdxEfecto=0;
    return catalogEfects[iIdxEfecto++];
}


MngrDisplays::sCatalogEfects MngrDisplays::getEfectoFijo()
{
    return efFijo;
}
