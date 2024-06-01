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



// bool button::isLongPushedAndReleased()
// {
//     // Resetea el botón para volver a ser usado
//     bool dev=false;


//     return dev;
// }

bool button::isPushedAndReleased()
{
    
    bool dev=false;
    int lectNew = digitalRead(PIN);


    if(lectNew==HIGH && lectOld==LOW)
    {
        Serial.println("PULSACIÓN");
        dev = true;
    }
    lectOld=lectNew;
   // delay(500);
    return dev;
}


button::~button()
{
}
