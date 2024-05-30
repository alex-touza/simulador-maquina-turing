//
// Created by backo on 18/2/2024.
//

#ifndef CASA_DOMOTICA_ENTRADAANALOGICA_H
#define CASA_DOMOTICA_ENTRADAANALOGICA_H

#include "Arduino.h"
#include "Pin.h"

namespace TMPins {
    class AnalogIn : public InputPin {
    public:
        using InputPin::InputPin;

        void begin() override;

        unsigned int read() override;
    };
}



#endif //CASA_DOMOTICA_ENTRADAANALOGICA_H
