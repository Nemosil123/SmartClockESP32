#ifndef DISPLAYCONFIG_H
#define DISPLAYCONFIG_H

#include "IDisplay.h"
#include "ConfigGeneral.h"

class DisplayConfig : public IDisplay
{
private:
    ConfigGeneral *cnfPpal;
    HoraLocal *horaAlarma;
public:
    DisplayConfig(/* args */);
    ~DisplayConfig();
    char* getTexto() override;
    void Init(MD_Parola* pantalla) override;

   // uint32_t  getMilliseconsSleep() override;
    std::string getNombre() override;
    void setCnf(ConfigGeneral cnf) override;
    void Pintar(MD_Parola* pantalla) override;
};

#endif
