#include <MD_Parola.h>
#include <MD_MAX72xx.h>
//#include <SPI.h>
#include "Displays/DisplayTexto.h"
#include "MngrDisplays.h"
#include "GestorConfig.h"
#include "Preferences.h"
#include "songs.h"
#include "button.h"

/********* WIFI  *************/
#ifdef MODULO_WIFI_PRESENTE
#include "WiFiManager.h"
#include "ezTime.h"
#else
#include "TimeJor.h"
#include <Ticker.h>
#endif

/***************PINES ************/
#define PIN_BTN_ALARM 21
#define PIN_BTN_SET 12
#define PIN_BUZZER 4

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

button* btnAlarma;//(PIN_BTN_ALARM);
button* btnSet;//(PIN_BTN_SET);

bool botonPulsadoBT=false;
bool bPulsadoAlarmaMientrasSonaba=false;
bool bPulsadoAlarmaLongTime=false;
bool btnSetPulsado=false;

#ifdef MODULO_WIFI_PRESENTE
Timezone horaTZ;
#else
HoraLocal horaLoc(0,0,0);
Ticker ticksHora;
GestorConfig mngrCnfg(&horaLoc);
Preferences prefs;
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
void salvarHora();
void recuperarHora();
void playCancion();
/****************************************/
bool alarmaModoOn = false;

void setup(void)
{
     // put your setup code here, to run once:
  Serial.begin(9600);
  InitWifiMngr();
  ticksHora.attach(1,pulsoSeg);

  Serial.println("Inicializando Screens");
  InitScreens(); 

  /************************ Configuración  PINES  ************************/
  btnAlarma = new button(PIN_BTN_ALARM);
  btnSet = new button(PIN_BTN_SET);
  btnAlarma->setup();
  btnSet->setup();
  pinMode(PIN_BUZZER,OUTPUT);
  Serial.println("Init prefs");
  prefs.begin("mi-hora",false);

  #if DEBUG_MODE
    mngrCnfg.cf->AlarmaActiva=true;
    mngrCnfg.cf->horaAlarma = new HoraLocal(horaLoc.getHours(), horaLoc.getMinutes()+1, horaLoc.getSeconds());
    mngrCnfg.cf->textoMensajes = "LUCAS Y PABLO";
    mngrCnfg.cf->textoAlarma = "DESPIERTA!!!";
    mngrCnfg.cf->textoDibujos = " PABLO Y LUCAS ";
    mngrCnfg.cf->AutoCambiarScreens=true;
  #endif

  mngrCnfg.SetConfig(mngrDsp, &horaLoc);
  Serial.println("Fin SetCnf");

// #ifdef DEBUG_MODE
//    mngrDsp.NextDisplay();
//  // mngrDsp.NextDisplay();
// #endif

  dspActiva = mngrDsp.GetActiveDisplay();

  recuperarHora();

}
//bool unaYnomas=true;

//int veces=0;
void loop(void)
{

  if(botonPulsadoBT)
  {
    EncenderBT();
    LeerConfigNueva();
  }

  if(btnAlarma->isPushedAndReleased())
  {
    // prefs.putUShort("h1",horaLoc.seconds);
    // Serial.println("Guardando: "+String(horaLoc.seconds));
    //salvarHora();
    ApagarAlarma();
  }
  if(btnSet->isPushedAndReleased())
  {
    // u_int16_t r = prefs.getUShort("h1");
    // Serial.println("Recuperando: "+String(r));
    // horaLoc.seconds=r;
   // recuperarHora();
    CambiarDisplay();
  }

    dspActiva->Pintar(&pantalla);

  if(alarmaModoOn)
  {
    playCancion();
  }

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
    mngrDsp.GetDisplay(i)->Init(&pantalla);
  }

  pantalla.setIntensity(mngrCnfg.getBrillo());
  Serial.print("Brillo: ");
  Serial.println(mngrCnfg.getBrillo());
  dspActiva = mngrDsp.GetActiveDisplay(); 

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

long milisAnt;
long milsAnteriores;
void pulsoSeg()
{
  if(horaLoc.tick())
  {
    // Cambio de minuto así que guardamos hora
    salvarHora();
  }
  if(mngrCnfg.cf->AlarmaActiva)
  {
//    Serial.println(mngrCnfg.cf->horaAlarma->getFormattedTime());
    if(mngrCnfg.cf->horaAlarma->getHours()==horaLoc.getHours() &&
        mngrCnfg.cf->horaAlarma->getMinutes()==horaLoc.getMinutes() )
        {
          if(!alarmaModoOn && !bPulsadoAlarmaMientrasSonaba)
          {
              milisAnt = millis();
              Serial.println("ALARMA ALARMA ALARMA");
              alarmaModoOn = (true);
          }
        }
    else if(bPulsadoAlarmaMientrasSonaba&&millis()-milisAnt>6000)
    {
        bPulsadoAlarmaMientrasSonaba=false;
    }    
  }

  if(millis()-milsAnteriores>300000) // 5 minutos y cambio display
  {
    CambiarDisplay();
    Serial.println("cambio Display");
    milsAnteriores = millis();
  }

}

void EncenderBT(){}
void LeerConfigNueva()
{
  mngrCnfg.cf->textoMensajes="PABLO ";
  //mngrCnfg.cf->AlarmaActiva=false;
  mngrCnfg.SetConfig(mngrDsp,&horaLoc);
  //mngrCnfg.cf->
}
void ApagarAlarma()
{
  if(alarmaModoOn)
  {
    Serial.println("APAGAR ALARMA");
    alarmaModoOn = false;
    bPulsadoAlarmaMientrasSonaba = true;
  }
  else
   {
    Serial.println("NADA QUE APAGAR");

   }
  //bPulsadoAlarma=false;
   //noTone(PIN_BUZZER);

}
void CambiarDisplay()
{
  Serial.print(String(dspActiva->getNombre().c_str())+"] Next Display [");
  dspActiva = mngrDsp.NextDisplay();
  Serial.println(String(dspActiva->getNombre().c_str()));
  LeerConfigNueva();
  milisAnt = millis();


}

void playCancion()
{
  Serial.println("Play CANCION");
  //return;
  // tone(PIN_BUZZER, NOTE_E5, 4);
  // delay(100);
  // tone(PIN_BUZZER, NOTE_B4, 8);
  // delay(100);
    int size = sizeof(durations) / sizeof(int);
    for (int note = 0; note < size; note++) {
      //to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int duration = 1000 / durations[note];
      tone(PIN_BUZZER, melody[note], duration);

      //to distinguish the notes, set a minimum time between them.
      //the note's duration + 30% seems to work well:
      int pauseBetweenNotes = duration * 1.30;
      delay(pauseBetweenNotes);
      
      //stop the tone playing:
      noTone(PIN_BUZZER);
      if(btnAlarma->isPushedAndReleased())
      {
        ApagarAlarma();
        break;
      }
  }
}

void recuperarHora()
{
    Serial.print("RECUPERAR hora en mem no volatil: ");
    horaLoc.hours=prefs.getUShort("ho",0);
    horaLoc.minutes=prefs.getUShort("mi",0);
    horaLoc.seconds=prefs.getUShort("se",0);
       Serial.println(horaLoc.getFormattedTime());
}

void salvarHora()
{
    Serial.println("Salvar hora en mem no volatil: "+String(horaLoc.minutes));
    prefs.putUShort("ho",horaLoc.hours);
    prefs.putUShort("mi",horaLoc.minutes);
    prefs.putUShort("se",horaLoc.seconds);
   // prefs.end();

}



