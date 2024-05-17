#include "DisplayTexto.h"

DisplayTexto::DisplayTexto(MD_Parola s) : screen(s)
{
}

void DisplayTexto::PintarPantalla()
{
    if (screen.displayAnimate())
        screen.displayText("SONSOLES BENITEZ DE SOTO", PA_CENTER, screen.getSpeed(), 1000, PA_SCROLL_LEFT, PA_SCROLL_LEFT);

}

    void DisplayTexto::Init()
{
    screen.begin();
    screen.setSpeed(50);
}

    uint32_t DisplayTexto::getMilliseconsEachLoop() const
{
    return 1000;
}

bool DisplayTexto::displayAnimate() 
{
    return screen.displayAnimate();
}

