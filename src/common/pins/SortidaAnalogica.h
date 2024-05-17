#ifndef CASA_DOMOTICA_SORTIDAANALOGICA_H
#define CASA_DOMOTICA_SORTIDAANALOGICA_H

#include <Arduino.h>
#include "Pin.h"

namespace CDPins {
    class SortidaAnalogica : public Pin {
    public:
        using Pin::Pin;

        void begin() override;

        void set(unsigned int _value);

        void set(int _value, int min, int max);
    };
}


#endif