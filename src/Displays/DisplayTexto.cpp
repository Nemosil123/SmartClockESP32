#include "DisplayTexto.h"
#define NUM_EFECTOS 28

// Sprite Definitions
const uint8_t F_PMAN1 = 6;
const uint8_t W_PMAN1 = 8;
static const uint8_t PROGMEM pacman1[F_PMAN1 * W_PMAN1] =  // gobbling pacman animation
{
  0x00, 0x81, 0xc3, 0xe7, 0xff, 0x7e, 0x7e, 0x3c,
  0x00, 0x42, 0xe7, 0xe7, 0xff, 0xff, 0x7e, 0x3c,
  0x24, 0x66, 0xe7, 0xff, 0xff, 0xff, 0x7e, 0x3c,
  0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c,
  0x24, 0x66, 0xe7, 0xff, 0xff, 0xff, 0x7e, 0x3c,
  0x00, 0x42, 0xe7, 0xe7, 0xff, 0xff, 0x7e, 0x3c,
};

const uint8_t F_PMAN2 = 6;
const uint8_t W_PMAN2 = 18;
static const uint8_t PROGMEM pacman2[F_PMAN2 * W_PMAN2] =  // ghost pursued by a pacman
{
  0x00, 0x81, 0xc3, 0xe7, 0xff, 0x7e, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe,
  0x00, 0x42, 0xe7, 0xe7, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe,
  0x24, 0x66, 0xe7, 0xff, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe,
  0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x73, 0xfb, 0x7f, 0xf3, 0x7b, 0xfe,
  0x24, 0x66, 0xe7, 0xff, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x73, 0xfb, 0x7f, 0xf3, 0x7b, 0xfe,
  0x00, 0x42, 0xe7, 0xe7, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x73, 0xfb, 0x7f, 0xf3, 0x7b, 0xfe,
};

static char* mensajesMotivacionales[] = {
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
DisplayTexto::DisplayTexto(char * msg):Texto(msg)
{
  cnf.efectoRnd = false;
}

u_int8_t iControlMotiv = 0;
char* DisplayTexto::getTexto(bool& esMotiv)
{

  iControlMotiv++;
  if(cnf.fraseMotivadora && iControlMotiv>4)
  {
      esMotiv=true;
      iControlMotiv=0;
      return mensajesMotivacionales[idxFraseMotiv++];
      if(idxFraseMotiv>=sizeof(mensajesMotivacionales))
        idxFraseMotiv=0;
  }
  else
  {
      esMotiv=false;
      return Texto;
  }
}

char *DisplayTexto::getTexto()
{
    return Texto;
}

void DisplayTexto::setTexto(char * txt)
{
    Texto = txt;
}

void DisplayTexto::Init(MD_Parola* pantalla)
{
    pantalla->setSpriteData(pacman1, W_PMAN1, F_PMAN1, pacman2, W_PMAN2, F_PMAN2);
}

char *DisplayTexto::getNombre()
{
    return "Pantalla Texto";
}

void DisplayTexto::setCnf(bool efRnd, bool fraseMotivadora )
{
  cnf.efectoRnd = efRnd;
  cnf.fraseMotivadora = fraseMotivadora;
}

uint32_t DisplayTexto::getMilliseconsSleep() const
{
    return 2000;
}


