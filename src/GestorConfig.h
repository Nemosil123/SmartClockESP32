
#ifndef GESTORCONFIG_H
#define GESTORCONFIG_H
#include "MngrDisplays.h"
class GestorConfig
{
private:
     /*************Config de pantalla Texto ************/
    char* txtPpal = "TE QUIERO PAPA";
    bool txtbFraseMotiva = true;
    bool txtbEfectoRnd = true;

    
public:
    /**********GLOBLALES **********************/
    bool cambioAutomaticoPantalla = false;

    void RefreshConfig(MngrDisplays mngr);
    GestorConfig(/* args */);
    ~GestorConfig();
    void SetConfig(MngrDisplays mngr);
   // MngrDisplays::sCatalogEfects getEfectScreen(u_int8_t indxScreen);
};
#endif

