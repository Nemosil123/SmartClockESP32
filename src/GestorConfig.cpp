#include "GestorConfig.h"

/// @brief Metodo para cargar la configuración desde un fichero, 
void GestorConfig::RefreshConfig(MngrDisplays mngr)
{
    // Realizamos la carga de refresco
    //...

    // Y ponemos la nueva config en los Displays
    SetConfig(mngr);

}

GestorConfig::GestorConfig()
{
}

GestorConfig::~GestorConfig()
{
}

void GestorConfig::SetConfig(MngrDisplays mngr)
{
    // Config Texto
    DisplayTexto* dspTxt =  (DisplayTexto*)mngr.GetDisplay(0);
    dspTxt->setTexto(this->txtPpal);
    dspTxt->setCnf(txtbEfectoRnd,txtbFraseMotiva);
}

