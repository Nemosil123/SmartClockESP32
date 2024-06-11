/*
PARA EVITAR EFECTO REVOTE poner una resistencia 10K entre la salida digital y tierra así:
   3.3V ----+
            |
           [ ]
           [ ] BOTON
           [ ]
            |
            +-----> Pin de entrada digital (ej. GPIO12)
            |
           [ ]
           [ ] 10k Resistencia
           [ ]
            |
           GND
*/

#include "button.h"
#include "Arduino.h"

button::button(int pin) : PIN(pin){}

void button::setup()
{
    pinMode(PIN, INPUT);
}



bool button::isPushedAndReleasedLongTime()
{
    bool dev=false;
    int lectNew = digitalRead(PIN);
    if(lectNew==HIGH && lectOld==LOW)
    {
        Serial.println("PULSACIÓN");
        lastClickTime = millis();
        //dev = true;
    }
    if(lectNew==LOW && lectOld==HIGH)
    {
        Serial.println("RELEASE");
        if(millis()-lastClickTime>longPushTime)
        {
            dev = true;
        }
    }
    lectOld=lectNew;
   // delay(500);
    return dev;
}

bool button::isPushedAndReleased()
{
    //Serial.println("Pulsado");
    
    bool dev=false;
    int lectNew = digitalRead(PIN);
    //Serial.println("Pulsado");


    if(lectNew==HIGH && lectOld==LOW)
    {
        Serial.println("PULSACIÓN");
        dev = true;
    }
    lectOld=lectNew;
   // Serial.print(".");

    return dev;
}


button::~button()
{
}
