#ifndef TIMEJOR_H
#define TIMEJOR_H
#include <Arduino.h>
class HoraLocal 
{
private:

public:
    HoraLocal(u_int8_t h, u_int8_t m, u_int8_t s);
    u_int8_t hours;
    u_int8_t minutes;
    u_int8_t seconds;
    void tick();
    u_int8_t getHours();
    u_int8_t getMinutes();
    u_int8_t getSeconds();
    String getFormattedTime();
};
#endif
