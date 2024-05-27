#include "TimeJor.h"

HoraLocal::HoraLocal(u_int8_t h, u_int8_t m, u_int8_t s): hours(h), minutes(m), seconds(s)
{
   // ticker.attach(1, std::bind(&&TimerJor::tick, this));
}

void HoraLocal::tick()
{
    seconds++;
    if (seconds >= 60) {
        seconds = 0;
        minutes++;
        if (minutes >= 60) {
            minutes = 0;
            hours++;
            if (hours >= 24) {
                hours = 0;
            }
        }
    }
}

// TimeJor::TimeJor(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
//         
// }



u_int8_t HoraLocal::getHours() {
    return hours;
}

u_int8_t HoraLocal::getMinutes() {
    return minutes;
}

u_int8_t HoraLocal::getSeconds() {
    return seconds;
}

String HoraLocal::getFormattedTime() {
    char buffer[7]; // HH:MM
    snprintf(buffer, sizeof(buffer), "%02d:%02d", hours, minutes);
    return String(buffer);
}