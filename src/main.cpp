#include <MD_Parola.h>
#include <MD_MAX72xx.h>
//#include <SPI.h>
#include "Displays/DisplayTexto.h"
#include "MngrDisplays.h"
#include "GestorConfig.h"

#include "Displays/DisplayDibujos.h" // borrar
#include <string> // borrar

/********* WIFI  *************/
#ifdef MODULO_WIFI_PRESENTE
#include "WiFiManager.h"
#include "ezTime.h"
#else
#include "TimeJor.h"
#include <Ticker.h>
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
GestorConfig mngrCnfg;

bool botonPulsadoBT=false;
bool btnPulsadoAlarma=false;
bool btnSetPulsado=false;

#ifdef MODULO_WIFI_PRESENTE
Timezone horaTZ;
#else
HoraLocal horaLoc(0,0,0);
Ticker ticksHora;
#endif

/**********************************************/

/************Métodos MAIN  ****************/
void EncenderBT();
void LeerConfigNueva();
void ApagarAlarma();
void CambiarDisplay();
void InitWifiMngr();
void InitScreens();
void pulsoSeg();

/****************************************/

void setup(void)
{
     // put your setup code here, to run once:
  Serial.begin(9600);
  InitWifiMngr();
  ticksHora.attach(1,pulsoSeg);

  Serial.println("Inicializando Screens");
  InitScreens(); 

  mngrCnfg.SetConfig(mngrDsp, &horaLoc);

#ifdef DEBUG_MODE
   mngrDsp.NextDisplay();
 // mngrDsp.NextDisplay();
#endif

  dspActiva = mngrDsp.GetActiveDisplay();
}

//int veces=0;
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
//       if(pantalla.displayAnimate())
//       {
//           MngrDisplays::sCatalogEfects ef;
//           if(dspActiva->cnf.efectoRnd && mngrDsp.getIdxActive() != 2)
//           {
//             ef = mngrDsp.getEfectoRnd();
//           }
//           else
//           {
//             ef.effect = dspActiva->cnf.EfectoScreen;
//             ef.pause = 0;
//             ef.speed = 40;
//           }

//           bool esMot = false;
//           char* txt=dspActiva->getTexto(esMot);

// #ifdef DEBUG_MODE
//           Serial.print("efecto SPRITE: ");
//           Serial.print(ef.effect==PA_SPRITE?"SI":"NO");
//           Serial.print(" Efecto Rnd: ");
//           Serial.print(dspActiva->cnf.efectoRnd? "SI": "NO");
//           Serial.print(" TXT: ");
//           Serial.println(txt);
// #endif
//         if(veces>=2 && mngrDsp.getIdxActive() == 2) // pANTALLA DE DIBUJOS
//          {
            
//              pantalla.displayText(txt, PA_CENTER, 20, 1000, PA_SPRITE, PA_SPRITE);
//              pantalla.setSpriteData(rocket, W_ROCKET, F_ROCKET, rocket, W_ROCKET, F_ROCKET);
//              veces=0;
//          }
//          else
//          {
//             pantalla.displayScroll(txt, dspActiva->cnf.posicion, (!esMot ?  ef.effect : PA_SCROLL_LEFT), ef.speed);

//          }
       // Serial.println("loop pintar");

          // if(mngrCnfg.cambioAutomaticoPantalla)
          //    dspActiva=mngrDsp.NextDisplay();
          dspActiva->Pintar(&pantalla);
             
          //delay(dspActiva->getMilliseconsSleep());
          // veces++;
          // Serial.println(veces);
  }
  
    // Serial.println("pintar pantalla");
    // //dspActiva->PintarPantalla();
    // Serial.println("end pintar pantalla");
  
  
}


void InitScreens()
{
  Serial.println("InitScreens");
  pantalla.begin();
#ifdef MODULO_WIFI_PRESENTE
  mngrDsp.Init(&horaTZ);
#else
  mngrDsp.Init(&horaLoc);
#endif

  for(uint8_t i=0;i<mngrDsp.getNumDisplays();i++)
  {
   // Serial.println(mngrDsp.GetDisplay(i)->getNombre().c_str());
    mngrDsp.GetDisplay(i)->Init(&pantalla);
  }

  pantalla.setIntensity(mngrCnfg.getBrillo());
  Serial.print("Brillo: ");
  Serial.println(mngrCnfg.getBrillo());
  dspActiva = (DisplayHora*)mngrDsp.GetActiveDisplay(); // QUITAR EL CAST Y DEJAR COMO GENERICO

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
    waitForSync();
    Serial.println(horaTZ.dateTime());


    Serial.print(horaTZ.hour());
    Serial.print(":");
    Serial.print(horaTZ.minute());
#else
  horaLoc = HoraLocal(22,35,0);
  Serial.print(horaLoc.getFormattedTime());
#endif
}

void pulsoSeg()
{
  horaLoc.tick();
  // Serial.print("H: "); Serial.print(horaLoc.getHours());
  // Serial.print(" M: "); Serial.print(horaLoc.getMinutes());
  // Serial.print(" S: "); Serial.println(horaLoc.getSeconds());
  // char buffer[9]; // HH:MM:SS
  // snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", horaLoc.getHours(), horaLoc.getMinutes(), horaLoc.getSeconds());

   //Serial.println(horaLoc.getFormattedTime());

}

void EncenderBT(){}
void LeerConfigNueva(){}
void ApagarAlarma(){}
void CambiarDisplay(){}