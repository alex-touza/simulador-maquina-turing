#ifndef CASA_DOMOTICA_SORTIDAANALOGICA_H
#define CASA_DOMOTICA_SORTIDAANALOGICA_H

#include <Arduino.h>
#include "Pin.h"

#define ANALOG_WRITE_MAX 255

namespace TMPins {
    class AnalogOut : public OutputPin {
    public:
        using OutputPin::OutputPin;

        void begin() override;

        void set(unsigned int _value) override;

        void set(int _value, int min, int max);

        void on() override;

        void off() override;
    };
}


#endif