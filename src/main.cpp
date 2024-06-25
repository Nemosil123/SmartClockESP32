#include <MD_Parola.h>
#include <MD_MAX72xx.h>
//#include <SPI.h>
#include "Displays/DisplayTexto.h"
#include "MngrDisplays.h"
#include "GestorConfig.h"
#include "Preferences.h"
#include "songs.h"
#include "button.h"
#include "BluetoothSerial.h"

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
#define PIN_LED_MODO_BT 2
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
BluetoothSerial BT;
bool modoNoche=false;

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
void recuperarCnfg();
void playCancion();
//bool leerInterrBT();
void callback_function(esp_spp_cb_event_t event, esp_spp_cb_param_t *param);
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
  pinMode(PIN_LED_MODO_BT, OUTPUT);
  pinMode(PIN_BUZZER,OUTPUT);
  btnAlarma->setup();
  btnSet->setup();
  Serial.println("Init prefs");
  prefs.begin("mi-hora",false);

  #if DEBUG_MODE
  //  mngrCnfg.cf->AlarmaActiva=true;
    Serial.println("Hora: "+horaLoc.getFormattedTime());
  // // mngrCnfg.cf->horaAlarma = new HoraLocal(horaLoc.getHours(), horaLoc.getMinutes()+1, horaLoc.getSeconds());
   // Serial.println("Hora alarma: "+mngrCnfg.cf->horaAlarma->getFormattedTime());

    // mngrCnfg.cf->textoMensajes = "PABLO";
    // mngrCnfg.cf->textoMensajes2 = "LUCAS";
    // mngrCnfg.cf->textoAlarma = "DESPIERTA!!!";
    // mngrCnfg.cf->textoDibujos = " PABLO Y LUCAS ";
    // mngrCnfg.cf->diaActual = 1;
    // mngrCnfg.cf->AutoCambiarScreens=true;
  #endif


  recuperarCnfg();

    Serial.println(mngrCnfg.cf->textoMensajes);

  mngrCnfg.SetConfig(mngrDsp, &horaLoc);


  dspActiva = mngrDsp.GetActiveDisplay();

  

}
bool BTOn=false;
bool BTemparejado=false;

bool ledOn=false;
unsigned long  BTtimeInit=0;

void loop(void)
{

  if(btnAlarma->isPushedAndReleasedLongTime()||BTOn)//leerInterrBT())
  {
    Serial.println("ENCENDER BLUETOOOOOTH");
    if(BTtimeInit==0)
        BTtimeInit = millis();
    EncenderBT();
    delay(1000);
    if(!BTemparejado)
    {
      digitalWrite(PIN_LED_MODO_BT,ledOn ? LOW : HIGH);
      ledOn=!ledOn;
    }
    else
    {
      digitalWrite(PIN_LED_MODO_BT, HIGH);
      BTemparejado = false;
    }
    if(millis()-BTtimeInit>360000) // 6 mins se apaga el BT
    {
      BTOn=false;
      BTtimeInit=0;
      digitalWrite(PIN_LED_MODO_BT,LOW);
    }
  }

  if(btnAlarma->isPushedAndReleased())
  {
    ApagarAlarma();
  }

  // if(btnSet->isPushedAndReleasedLongTime())
  // {

  //   // Activamos o desactivamos alarma
  //   mngrCnfg.cf->AlarmaActiva = !mngrCnfg.cf->AlarmaActiva;
  //    Serial.print("Alarma modo: ");
  //   Serial.println(mngrCnfg.cf->AlarmaActiva);
  // }

  if(btnSet->isPushedAndReleased())
  {
    CambiarDisplay();
    Serial.println("cambiar disp end");
  }

  if(!modoNoche)
  {
      dspActiva->Pintar(&pantalla);
  }
  else
  {
      if(horaLoc.getSeconds()<6&&horaLoc.getSeconds()>0)
      {
          dspActiva->Pintar(&pantalla);
      }
      else
      {
          dspActiva = mngrDsp.SetDisplayHora();
          pantalla.displayClear();
      }
  }

  if(alarmaModoOn)
  {
    dspActiva->Pintar(&pantalla);
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
 // Serial.print(horaLoc.getFormattedTime());
#endif
}

unsigned long  milisAnt;
unsigned long  milsAnteriores;
void pulsoSeg()
{
  if(horaLoc.tick())
  {
    Serial.println("salvar hora");

    // Cambio de minuto así que guardamos hora
    salvarHora();
  }
  if(mngrCnfg.cf->AlarmaActiva)
  {
    if(mngrCnfg.cf->horaAlarma->getHours()==horaLoc.getHours() &&
        mngrCnfg.cf->horaAlarma->getMinutes()==horaLoc.getMinutes() )
    {
      if(!alarmaModoOn && !bPulsadoAlarmaMientrasSonaba)
      {
          milisAnt = millis();
          dspActiva= mngrDsp.SetDisplayHora();
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
    if(mngrDsp.getIdxActive()==3) // Nos saltamos el de config
    {
      CambiarDisplay();
    }
    milsAnteriores = millis();
  }

  if(horaLoc.minutes==0 && horaLoc.seconds==0 ) // Chequeamos cada hora en punto si estamos en modo noche
  {
    if(horaLoc.isHoraBtwIniFin(mngrCnfg.cf->HoraIniNoche,mngrCnfg.cf->HoraFinNoche))
    {
      Serial.println("Modo noche");
        // Modo Noche
        modoNoche=true;
        pantalla.setIntensity(0);
        pantalla.displayReset();
        dspActiva = mngrDsp.SetDisplayHora();
    }
    else
    {
      modoNoche=false;
    }
  }


}

// bool leerInterrBT()
// {
//   //Serial.println("leerInterrbt");
//   int v = digitalRead(PIN_LED_MODO_BT);
//   return (v==HIGH);
// }

void EncenderBT()
{
  if(!BTOn)
  {
    Serial.println("ENCENDER BLUETOOTH");
    BT.begin("SMART DESPERTADOR"); // Nombre de tu Dispositivo Bluetooth y en modo esclavo
    BTOn = true;
    Serial.println("El dispositivo Bluetooth está listo para emparejar");
    BT.register_callback(callback_function); // Registramos la función "callback_function" como función callback.
  }
}

void LeerConfigNueva()
{
  mngrCnfg.SetConfig(mngrDsp,&horaLoc);
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

//  Serial.print(String(dspActiva->getNombre().c_str())+"] Next Display [");
  dspActiva = mngrDsp.NextDisplay();
  //Serial.println(String(dspActiva->getNombre().c_str()));
    //  Serial.println("cmb display 2");

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

void recuperarCnfg()
{

   Serial.println("recuperando info de config");
 //   char cad[427];
 //   if(prefs.getString("cnf",cad,427)>1)
  //  {
  //      mngrCnfg.CargarConfig(cad);
   // }
    mngrCnfg.cf->AlarmaActiva =  prefs.getBool("alOn",false);
    Serial.print("Alarma: ");
    Serial.println(mngrCnfg.cf->AlarmaActiva);
    mngrCnfg.cf->diaActual=prefs.getUInt("diaA",1);
        Serial.print("Dia: ");
    Serial.println(mngrCnfg.cf->diaActual);

    uint16_t h= prefs.getUInt("horaA",0);
    uint16_t m= prefs.getUInt("MinA",0);
    mngrCnfg.cf->horaAlarma=new HoraLocal(h,m,0);

    Serial.print("Hora Al: ");
    Serial.println(mngrCnfg.cf->horaAlarma->getFormattedTime());

    mngrCnfg.cf->textoDibujos=prefs.getString("txtD","HAPPY FAMILY");
    Serial.print("textoDibujos: ");
        Serial.println(mngrCnfg.cf->textoDibujos);
    mngrCnfg.cf->textoMensajes=prefs.getString("txtMsg","LUCAS");
    Serial.print("txtMsg: ");
        Serial.println(mngrCnfg.cf->textoMensajes);
  
    mngrCnfg.cf->textoMensajes2=prefs.getString("txt2","PABLO");
    Serial.print("textomensaje2: ");
    Serial.println(mngrCnfg.cf->textoMensajes2);

   Serial.println("Recuperada y cargada info de config");

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
    Serial.println("Salvada");

}

void callback_function(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_START_EVT) {
    Serial.println("Inicializado bluetooth");
  }
  else if (event == ESP_SPP_SRV_OPEN_EVT ) {
    Serial.println("Cliente BT conectado");
    BTemparejado = true;

  }
  else if (event == ESP_SPP_CLOSE_EVT  ) {
    Serial.println("Cliente BT desconectado");
    digitalWrite(PIN_LED_MODO_BT,LOW);
  }
  else if (event == ESP_SPP_DATA_IND_EVT ) {
    Serial.println("Datos recibidos por BT");
    if(BT.available())
    {
          char cad[427];
          int idx=0;
        while (BT.available()) { // Mientras haya datos por recibir
          int incoming = BT.read(); // Lee un byte de los datos recibidos
         // Serial.print("Recibido: ");
         // Serial.print(incoming);
          //Serial.println((char)incoming);

          cad[idx++]=(char)incoming;

        }
       // prefs.freeEntries();
        Serial.println(cad);
        Serial.println("Guardada en mem permanente conf");
        

        mngrCnfg.CargarConfig(cad);

        prefs.putBool("alOn",mngrCnfg.cf->AlarmaActiva);
        prefs.putUInt("diaA",mngrCnfg.cf->diaActual);
        prefs.putUInt("horaA",mngrCnfg.cf->horaAlarma->hours);
        prefs.putUInt("MinA",mngrCnfg.cf->horaAlarma->minutes);
        prefs.putString("txtD",mngrCnfg.cf->textoDibujos);
        prefs.putString("txtMsg",mngrCnfg.cf->textoMensajes);
        prefs.putString("txt2",mngrCnfg.cf->textoMensajes2);
        
        Serial.println("Guardado en memoria la configuracion");
        Serial.print("Hora ACtual cargada: ");
        Serial.println(horaLoc.getFormattedTime());
        LeerConfigNueva();
        BTOn=false;
        digitalWrite(PIN_LED_MODO_BT, LOW );

        BT.end();
    }
  }
}

