#include "DisplayConfig.h"
#include <cstring>  // Para strcpy

DisplayConfig::DisplayConfig()
{
    cnf.posicion=PA_CENTER;
    cnf.EfectoScreen = PA_SPRITE;
}

DisplayConfig::~DisplayConfig()
{
}

char *DisplayConfig::getTexto()
{
    //return "ALARMA: ";
    String dev ="ALARMA: ";
    if(cnfPpal->AlarmaActiva)
        dev = dev + cnfPpal->horaAlarma->getFormattedTime();
    else
        dev = "ALARMA: OFF";
   // Serial.println(dev);
    
    char* cstr = new char[dev.length() + 1];
    std::strcpy(cstr, dev.c_str());
    return cstr;

}

void DisplayConfig::Init(MD_Parola *pantalla)
{
    Serial.println("Init Config");
   // pantalla->displayText(getTexto(), PA_CENTER, 50, 1000, PA_SPRITE, PA_SPRITE);
}

std::string DisplayConfig::getNombre()
{
    return "Pantalla Config";
}

void DisplayConfig::setCnf(ConfigGeneral cnf)
{
    cnfPpal = &cnf;
}

void DisplayConfig::Pintar(MD_Parola *pantalla)
{
    if(pantalla->displayAnimate())
    {
        char* t = getTexto();

        Serial.println(t);
        pantalla->displayText(t, PA_CENTER, 50, 1000, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        pantalla->displayReset();
    }
}
