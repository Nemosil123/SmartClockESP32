
#ifndef GESTORCONFIG_H
#define GESTORCONFIG_H
#include "MngrDisplays.h"
class GestorConfig
{
private:
     /*************Config de pantalla Texto ************/
     char* txtPpal = "TE QUIERO PAPA";
    // bool txtbFraseMotiva = true;
    // bool txtbEfectoRnd = true;
    u_int8_t brilloDisplay=5;
    
public:
    /**********GLOBLALES **********************/
    bool cambioAutomaticoPantalla = false;

   void setBrillo(u_int8_t b);
    u_int8_t getBrillo();
    void RefreshConfig(MngrDisplays mngr);
    GestorConfig(/* args */);
    ~GestorConfig();
    void SetConfig(MngrDisplays mngr, HoraLocal* ahora);
   // MngrDisplays::sCatalogEfects getEfectScreen(u_int8_t indxScreen);
};
#endif

