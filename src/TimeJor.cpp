#include "TimeJor.h"

HoraLocal::HoraLocal(u_int16_t h, u_int16_t m, u_int16_t s): hours(h), minutes(m), seconds(s)
{}

/// @brief Se debe invocar cada segundo para controlar el reloj
/// @return Devuelve true si ha cambiado el minuto
bool HoraLocal::tick()
{
    bool cambioMin = false;
    seconds++;
    if (seconds >= 60) {
        seconds = 0;
        cambioMin = true;
        minutes++;
        if (minutes >= 60) {
            minutes = 0;
            hours++;
            if (hours >= 24) {
                hours = 0;
            }
        }
    }
    return cambioMin;
}

// TimeJor::TimeJor(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
//         
// }



u_int16_t HoraLocal::getHours() {
    return hours;
}

u_int16_t HoraLocal::getMinutes() {
    return minutes;
}

u_int16_t HoraLocal::getSeconds() {
    return seconds;
}

String HoraLocal::getFormattedTime() {
    char buffer[7]; // HH:MM
    snprintf(buffer, sizeof(buffer), "%02d:%02d ", hours, minutes);
    return String(buffer);
}




