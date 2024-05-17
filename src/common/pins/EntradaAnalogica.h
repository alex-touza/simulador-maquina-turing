//
// Created by backo on 18/2/2024.
//

#ifndef CASA_DOMOTICA_ENTRADAANALOGICA_H
#define CASA_DOMOTICA_ENTRADAANALOGICA_H

#include "Arduino.h"
#include "Pin.h"

namespace CDPins {
    class EntradaAnalogica : public Pin {
    public:
        using Pin::Pin;

        void begin() override;

        unsigned int read();
    };
}



#endif //CASA_DOMOTICA_ENTRADAANALOGICA_H
