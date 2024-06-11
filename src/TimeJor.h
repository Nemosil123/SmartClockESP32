#ifndef TIMEJOR_H
#define TIMEJOR_H
#include <Arduino.h>

class HoraLocal 
{
private:
public:
    HoraLocal(u_int16_t h, u_int16_t m, u_int16_t s);
    u_int16_t hours;
    u_int16_t minutes;
    u_int16_t seconds;
    bool tick();
    u_int16_t getHours();
    u_int16_t getMinutes();
    u_int16_t getSeconds();
    String getFormattedTime();
    //bool isHoraBtwIniFin(u_int16_t hIni, u_int16_t hFin);

};
#endif
