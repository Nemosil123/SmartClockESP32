#include <MD_Parola.h>
#include <MD_MAX72xx.h>
//#include <SPI.h>
#include "Displays/DisplayTexto.h"
#include "MngrDisplays.h"

#ifdef MODULO_WIFI_PRESENTE
/********* WIFI  *************/
#include "WiFiManager.h"
#include "ezTime.h"

#endif
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
IDisplay* dspActiva;
MngrDisplays mngrDsp;


bool botonPulsadoBT=false;
bool btnPulsadoAlarma=false;
bool btnSetPulsado=false;

#ifdef MODULO_WIFI_PRESENTE
Timezone horaTZ;
#endif

/**********************************************/

/************Métodos MAIN  ****************/
void EncenderBT();
void LeerConfigNueva();
void ApagarAlarma();
void CambiarDisplay();
void InitWifiMngr();
void InitScreens();

/****************************************/

void setup(void)
{
     // put your setup code here, to run once:
  Serial.begin(9600);
  InitWifiMngr();

  Serial.println("Inicilizando Screens");
  InitScreens(); 
  dspActiva = mngrDsp.GetActiveDisplay();
  //dspActiva = new DisplayTexto(pantalla);
  //dspActiva->Init();
}

void loop(void)
{
  
 // Serial.print("Loop");
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
  if(pantalla.displayAnimate())
  {
        //pantalla.displayText("SONSOLES BENITEZ DE SOTO", PA_CENTER, pantalla.getSpeed(), 1000, PA_SCROLL_RIGHT, PA_SCROLL_RIGHT);
        pantalla.displayText(dspActiva->getTexto(), PA_CENTER, pantalla.getSpeed(), 1000, PA_SCROLL_DOWN, PA_SCROLL_DOWN);
  }
    // Serial.println("pintar pantalla");
    // //dspActiva->PintarPantalla();
    // Serial.println("end pintar pantalla");
  
    if(pantalla.displayAnimate())
    {
       delay(dspActiva->getMilliseconsSleep());
    }
  }
}

void InitScreens()
{
  Serial.println("InitPantalla");
  pantalla.begin();
  mngrDsp.Init();
  pantalla.setIntensity(mngrDsp.getBrillo());
  Serial.println("GetActiveDisplay");
  dspActiva = mngrDsp.GetActiveDisplay();
  //mngrDsp.AddDisplay(new DisplayTexto("Soy Jorge Super chip"),0);
}

void InitWifiMngr()
{
    #ifdef MODULO_WIFI_PRESENTE
    
    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;
    wm.setConnectRetries(3);
    wm.setConnectTimeout(20);

        // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result

    bool res;
    res = wm.autoConnect("DesperatadorAP"); // password protected ap

    if(!res) {
        Serial.println("No se puede conectar");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
    }

    // Ajustamos la hora
    horaTZ.setLocation(F("Europe/Madrid"));
    #endif

#ifdef DEBUG_MODE
    #ifdef MODULO_WIFI_PRESENTE

    Serial.print(horaTZ.hour());
    Serial.print(":");
    Serial.print(horaTZ.minute());
    #endif
#endif
}

void EncenderBT(){}
void LeerConfigNueva(){}
void ApagarAlarma(){}
void CambiarDisplay(){}