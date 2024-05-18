#include "Displays/IDisplay.h"
#include "Displays/DisplayTexto.h"
#include <MD_Parola.h>

#define NUM_SCREENS 1

class MngrDisplays
{
private:
    IDisplay* LstDisplays[NUM_SCREENS];
    u_int8_t idxDisplayActivo;
    u_int8_t brillo =5;

   // MD_Parola screenLED;
public:
    MngrDisplays();//MD_Parola pantalla);
    ~MngrDisplays();
    void AddDisplay(IDisplay* dsp, u_int8_t idx);
    u_int8_t getNumDisplays();
    void Init();
    IDisplay* GetActiveDisplay();
    IDisplay* NextDisplay();
    void setBrillo(u_int8_t b);
    u_int8_t getBrillo();
};


