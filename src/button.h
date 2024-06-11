#ifndef BUTTON_H
#define BUTTON_H

class button
{
private:
    int PIN;
    int lectOld = 0;

    // bool botonPulsadoYSoltado=false;
    // bool botonPulsadoYSoltadoLargaDuracion=false;
    // bool botonPulsado=false;
    // bool botonSoltado=false;
    unsigned long lastClickTime = 0;
    unsigned long longPushTime = 3000; // Tiempo que se considera pulsación larga en milisc

public:

    button(int pin);
    void setup();
    // bool isPushed();
   // bool isReleased();
    bool isPushedAndReleased();
    bool isPushedAndReleasedLongTime();
    // void check();

    ~button();
};

#endif
