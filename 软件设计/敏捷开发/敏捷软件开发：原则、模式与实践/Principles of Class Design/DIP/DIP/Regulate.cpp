#include "Regulate.h"

#define TERMOMETER 0x86
#define FURNACE 0x87
#define ENGAGE 1
#define DISENGAGE 0

void Regulate(double minTemp, double maxTemp)
{
    for (;;)
    {
        while (in(TERMOMETER) > minTemp)
            wait(1);
        out(FURNACE, ENGAGE);

        while (in(TERMOMETER) < minTemp)
            wait(1);
        out(FURNACE, DISENGAGE);
    }
}

void Regulate(Thermometer& t, Heater& h, double minTemp, double maxTemp)
{
    for (;;)
    {
        while (t.Read() > minTemp)
            wait(1);
        h.Engage();

        while (t.Read() < minTemp)
            wait(1);
        h.Disengage();
    }
}

template <typename Thermometer, typename Heater>
void Regulate(Thermometer& t, Heater& h, double minTemp, double maxTemp)
{
    for (;;)
    {
        while (t.Read() > minTemp)
            wait(1);
        h.Engage();

        while (t.Read() < minTemp)
            wait(1);
        h.Disengage();
    }
}