#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "Displays/DisplayTexto.h"
//#include "Displays/DisplayTexto.h"
// #include "EfectosTexto.h"
// #include "ScreenHora.h"

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::DR1CR0RR0_HW
#define MAX_DEVICES 4
#define CLK_PIN   18
#define DATA_PIN  23
#define CS_PIN    5

/********** Variables de MAIN   *****************/
MD_Parola pantalla = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
IDisplay* dspTxt;

bool botonPulsadoBT=false;
bool btnPulsadoAlarma=false;
bool btnSetPulsado=false;
/**********************************************/

/************Métodos MAIN  ****************/
void EncenderBT();
void LeerConfigNueva();
void ApagarAlarma();
void CambiarDisplay();

/****************************************/

void setup(void)
{
  dspTxt = new DisplayTexto(pantalla);
  dspTxt->Init();
}

void loop(void)
{
  if(botonPulsadoBT)
  {
    EncenderBT();
    LeerConfigNueva();
  }
  else if(btnPulsadoAlarma)
  {
    ApagarAlarma();
  }
  else if(btnSetPulsado)
  {
    CambiarDisplay();
  }
  else
  {
    dspTxt->PintarPantalla();
    if(dspTxt->displayAnimate())
      delay(dspTxt->getMilliseconsEachLoop());
  }
}
