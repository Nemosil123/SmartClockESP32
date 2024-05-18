#include "MngrDisplays.h"


MngrDisplays::MngrDisplays(){}//MD_Parola pantalla) : screenLED(pantalla){}

MngrDisplays::~MngrDisplays()
{
}

void MngrDisplays::AddDisplay(IDisplay* dsp, u_int8_t idx)
{
    LstDisplays[idx] = dsp;
}

u_int8_t MngrDisplays::getNumDisplays()
{
    return NUM_SCREENS;
}

void MngrDisplays::Init()
{
    LstDisplays[0]=new DisplayTexto("Super Guay!!");

}

IDisplay *MngrDisplays::GetActiveDisplay()
{
    return LstDisplays[idxDisplayActivo];
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

void MngrDisplays::setBrillo(u_int8_t b)
{
    brillo = b;
}

u_int8_t MngrDisplays::getBrillo()
{
    return brillo;
}
