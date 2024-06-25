#ifndef DISPLAYTEXTO_H
#define DISPLAYTEXTO_H
//#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "IDisplay.h"
#include "../MngrDisplays.h"

class DisplayTexto : public IDisplay
{
    private:
        u_int16_t idxFraseMotiv=0;
         String Texto;
         String Texto2;

    public:

        DisplayTexto( char* txt);
         char* getTexto(bool &esMotiv);
         char* getTexto() override;
        void setTexto( char* );
        void Init(MD_Parola* pantalla) override;
      //  uint32_t getMilliseconsSleep() const override;
        std::string getNombre() override;
        void setCnf(ConfigGeneral cnf) override;
        void Pintar(MD_Parola *pantalla) override;
};
#endif