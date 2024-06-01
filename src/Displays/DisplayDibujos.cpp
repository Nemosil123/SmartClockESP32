#include "DisplayDibujos.h"

DisplayDibujos::DisplayDibujos()
{
  cnf.posicion=PA_CENTER;
  cnf.EfectoScreen = PA_SPRITE;
  texto = "FAMILY";
}


u_int16_t curString =0;
char *DisplayDibujos::getTexto()
{
    return texto;
}

void DisplayDibujos::Init(MD_Parola *pantalla)
{
    Serial.println("Init DisplayDibujos");
    pantalla->displayText(getTexto(), PA_CENTER, 50, 1000, PA_SPRITE, PA_SPRITE);
   //pantalla.setSpriteData(rocket, W_ROCKET, F_ROCKET, rocket, W_ROCKET, F_ROCKET);
    pantalla->setSpriteData(wave, W_WAVE, F_WAVE, wave, F_WAVE, F_WAVE);
}

u_int8_t iSpriteAct = 0;
str_sprite  DisplayDibujos::getSpriteRnd()
{
    if(iSpriteAct>=NUM_SPRITES)
        iSpriteAct = 0;

    return sprite[iSpriteAct++];
}

void DisplayDibujos::Pintar(MD_Parola *pantalla)
{
      if(pantalla->displayAnimate())
      {


        char* txt=getTexto();

        str_sprite sp = getSpriteRnd();
        pantalla->displayText(txt, PA_CENTER, 50, 1000, PA_SPRITE, PA_SPRITE);
        pantalla->setSpriteData(sp.data, sp.width, sp.frames, sp.data, sp.width, sp.frames);
       // pantalla->setSpeedInOut(7,5);

        pantalla->displayReset();
      }
}



uint32_t DisplayDibujos::getMilliseconsSleep() const
{
    return 1000;
}

std::string DisplayDibujos::getNombre()
{
    return "Screen Dibujos";
}

void DisplayDibujos::setCnf(ConfigGeneral cf)
{
    texto = cf.textoDibujos;
}
