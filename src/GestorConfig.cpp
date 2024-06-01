#include "GestorConfig.h"

/// @brief Metodo para cargar la configuración desde un fichero, 
void GestorConfig::RefreshConfig(MngrDisplays mngr)
{
    // Realizamos la carga de refresco
    //...

    // Y ponemos la nueva config en los Displays
   // SetConfig(mngr);

}

GestorConfig::GestorConfig(HoraLocal* ahora) 
{
    cf = new ConfigGeneral(ahora);
}

GestorConfig::~GestorConfig()
{
}


void GestorConfig::setBrillo(u_int8_t b)
{
    brilloDisplay = b;
}

u_int8_t GestorConfig::getBrillo()
{
    return brilloDisplay;
}

void GestorConfig::SetConfig(MngrDisplays mngr, HoraLocal* ahora)
{
    

    // Config Texto
    DisplayTexto* dspTxt =  (DisplayTexto*)mngr.GetDisplay(0);
    //dspTxt->setTexto(this->txtPpal);
    dspTxt->setCnf(*cf);

    // Config Hora
    DisplayHora* dspH =  (DisplayHora*)mngr.GetDisplay(1);
    //dspH->setTexto("DESPIERTA!!");
    dspH->setCnf(*cf);

        // Config Dibujos
    DisplayDibujos* dspDib =  (DisplayDibujos*)mngr.GetDisplay(2);
    dspDib->setCnf(*cf);

    //
}

