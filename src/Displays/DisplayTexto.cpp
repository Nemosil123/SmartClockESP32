#include "DisplayTexto.h"
#include <cstring>  // Para strcpy
#define NUM_EFECTOS 28
#define NUM_FRASES 100

// // Sprite Definitions
// const uint8_t F_PMAN1 = 6;
// const uint8_t W_PMAN1 = 8;
// static const uint8_t PROGMEM pacman1[F_PMAN1 * W_PMAN1] =  // gobbling pacman animation
// {
//   0x00, 0x81, 0xc3, 0xe7, 0xff, 0x7e, 0x7e, 0x3c,
//   0x00, 0x42, 0xe7, 0xe7, 0xff, 0xff, 0x7e, 0x3c,
//   0x24, 0x66, 0xe7, 0xff, 0xff, 0xff, 0x7e, 0x3c,
//   0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c,
//   0x24, 0x66, 0xe7, 0xff, 0xff, 0xff, 0x7e, 0x3c,
//   0x00, 0x42, 0xe7, 0xe7, 0xff, 0xff, 0x7e, 0x3c,
// };

// const uint8_t F_PMAN2 = 6;
// const uint8_t W_PMAN2 = 18;
// static const uint8_t PROGMEM pacman2[F_PMAN2 * W_PMAN2] =  // ghost pursued by a pacman
// {
//   0x00, 0x81, 0xc3, 0xe7, 0xff, 0x7e, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe,
//   0x00, 0x42, 0xe7, 0xe7, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe,
//   0x24, 0x66, 0xe7, 0xff, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe,
//   0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x73, 0xfb, 0x7f, 0xf3, 0x7b, 0xfe,
//   0x24, 0x66, 0xe7, 0xff, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x73, 0xfb, 0x7f, 0xf3, 0x7b, 0xfe,
//   0x00, 0x42, 0xe7, 0xe7, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x73, 0xfb, 0x7f, 0xf3, 0x7b, 0xfe,
// };

const std::array<std::string, NUM_FRASES>  mensajesMotivacionales = {
     "Rie, es contagioso",
      "Hoy es un buen dia",
      "¡Tu puedes!",
      "No te rindas",
      "Vive y deja vivir",
      "Se tu mismo",
      "El cafe salva vidas",
      "Brilla siempre",
      "La vida es bella",
      "Hazlo con amor",
      "Se feliz, no perfecto",
      "Atrevete a sonar",
      "Tu eres increible",
      "La risa cura todo",
      "Ama sin limites",
      "Suena en grande",
      "Disfruta el viaje",
      "Se tu propio heroe",
      "Vive el momento",
      "Eres suficiente",
      "Hazlo con pasion",
      "Cree en ti",
      "Sonrie mas",
      "La vida es hoy",
      "Piensa en positivo",
      "La actitud importa",
      "Sigue adelante",
      "Se valiente",
      "La vida sigue",
      "Hazlo por ti",
      "No mires atras",
      "Cree y crea",
      "Hazlo ahora",
      "Ama la vida",
      "Cada dia cuenta",
      "Eres unico",
      "Vibra alto",
      "Hazlo con fe",
      "Nunca te rindas",
      "Sonrie siempre",
      "Vuela alto",
      "Se agradecido",
      "Vive feliz",
      "Todo es posible",
      "Se tu mejor version",
      "Suena despierto",
      "Hoy es tu dia",
      "Haz lo que amas",
      "Vive con pasion",
      "La magia eres tu",
      "Ama y rie",
      "Sigue tus suenos",
      "El exito te espera",
      "La vida sorprende",
      "Hazlo con ganas",
      "Disfruta el ahora",
      "Vive sin miedo",
      "Cree en la magia",
      "Se positivo",
      "Valora cada dia",
      "Persigue tus metas",
      "Cree en la suerte",
      "Se fuerte",
      "Lo mejor esta por venir",
      "No te detengas",
      "Vive intensamente",
      "Haz tu mejor esfuerzo",
      "Encuentra tu camino",
      "Da lo mejor de ti",
      "Vive con proposito",
      "Se constante",
      "Celebra la vida",
      "Eres extraordinario",
      "Hazlo con alegria",
      "Nunca es tarde",
      "La vida es corta",
      "Sigue tus pasiones",
      "Agradece siempre",
      "Confia en el proceso",
      "Se amable",
      "La risa es salud",
      "Vive con gratitud",
      "Elige ser feliz",
      "Cree en los milagros",
      "Hazlo diferente",
      "Vive con intensidad",
      "Sigue tu corazon",
      "Se autentico",
      "Aprecia lo simple",
      "No te preocupes",
      "Todo es aprendizaje",
      "La vida es arte",
      "Eres un campeon",
      "Rodeate de luz",
      "Encuentra tu paz",
      "Vive en armonia",
      "Hazlo memorable",
      "Se persistente",
      "Ama cada dia",
      "Haz lo imposible"
};
DisplayTexto::DisplayTexto( char* msg):Texto(msg)
{
  //cnf.efectoRnd = false;
  cnf.posicion=PA_CENTER;
}


u_int8_t iControlMotiv = 0;
//bool esMotivadora = false;
MngrDisplays::sCatalogEfects efTmp;

 char* DisplayTexto::getTexto(bool& esMotiv)
{

  iControlMotiv++;
  if(iControlMotiv>4)
  {
    esMotiv = true;
   // Serial.print(" <mot> ");
    efTmp = MngrDisplays::getEfectoRnd();
    iControlMotiv=0;
    // Obtener la cadena y su longitud
    const char* source = mensajesMotivacionales[idxFraseMotiv++].c_str();
    size_t length = std::strlen(source) + 1; // +1 para el carácter nulo
    // Asignar memoria en el heap
    char* cad = new char[length];
    // Copiar la cadena
    std::strcpy(cad, source);
    return cad;
  }
  else
  {
    //Serial.print(" <normal> ");
    esMotiv=false;
    return Texto;
  }
}

bool unaSiunaNo=true;
bool scroolR = true;
void DisplayTexto::Pintar(MD_Parola *pantalla)
{
  if(pantalla->displayAnimate())
  {
   // Serial.print('>');
    bool esMot = false;
    char* txt=getTexto(esMot);
// #ifdef DEBUG_MODE
//      Serial.print(unaSiunaNo);
//      Serial.print(" esMot= ");
//      Serial.print(esMot);
//     //Serial.print(ef.effect==PA_SPRITE?"SI":"NO");
// #endif
    if(!esMot)
    {
        if(unaSiunaNo)
        {
            textEffect_t t = PA_SCROLL_RIGHT;
            if(scroolR)
            {
              t = PA_SCROLL_LEFT;
            }
            scroolR=!scroolR;
            pantalla->displayScroll(txt, cnf.posicion,  t, 50);
        }
        else
        { 
          MngrDisplays::sCatalogEfects efR = MngrDisplays::getEfectoRnd();
            pantalla->displayText(txt, cnf.posicion, efR.speed, efR.pause, efR.effect, efR.effect);
        }
    }
    else
    {
            pantalla->displayScroll(txt, cnf.posicion,  PA_SCROLL_LEFT, 50);
    }
    unaSiunaNo=!unaSiunaNo;
    pantalla->displayReset();

    // Serial.print(" TXT: ");
    // Serial.println(txt);

  }
}

char* DisplayTexto::getTexto()
{
    return Texto;
}

void DisplayTexto::setTexto( char* txt)
{
    Texto = txt;
}

void DisplayTexto::Init(MD_Parola* pantalla)
{
    pantalla->setSpriteData(pacman1, W_PMAN1, F_PMAN1, pacman2, W_PMAN2, F_PMAN2);
}

std::string DisplayTexto::getNombre()
{
    return "Pantalla Texto";
}

void DisplayTexto::setCnf(ConfigGeneral cnfD)
{
    setTexto(cnfD.textoMensajes);
}


// uint32_t DisplayTexto::getMilliseconsSleep() const
// {
//     return 2000;
// }


