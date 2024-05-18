#include "DisplayTexto.h"

DisplayTexto::DisplayTexto(char * msg):Texto(msg){}

char* DisplayTexto::getTexto()
{
   return Texto;
}

void DisplayTexto::Init()
{
    // screen.begin();
    // screen.displayReset();
    // screen.setSpeed(50);
}

uint32_t DisplayTexto::getMilliseconsSleep() const
{
    return 2000;
}

// bool DisplayTexto::displayAnimate() 
// {
//     return screen.displayAnimate();
// }

