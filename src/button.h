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
    // unsigned long lastDebounceTime = 0;
    // unsigned long debounceDelay = 50; // Tiempo de retardo para el anti-rebote (en milisegundos)

public:

    button(int pin);
    void setup();
    // bool isPushed();
   // bool isReleased();
    bool isPushedAndReleased();
    // // bool isLongPushedAndReleased();
    // void check();

    ~button();
};

#endif
