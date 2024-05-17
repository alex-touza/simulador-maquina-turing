#ifndef EntradaDigital_h
#define EntradaDigital_h

#include <Arduino.h>
#include "Pin.h"
/*
enum InterruptModes {
    SIGNALRISING = RISING,
    SIGNALFALLING = FALLING,
};
*/

namespace CDPins {
    class EntradaDigital : public Pin {
    public:
        using Pin::Pin;

        void begin() override;
        bool active;

        unsigned int read(bool debounce = false, bool invert = false);

        /*
        Equivalent a la funció integrada corresponent amb un
        interval de 10 microsegons.
        */
        unsigned long pulseIn();

        /*
        void attachInterrupt(InterruptModes mode, void (*callback)());

        template<typename T>
        void attachInterrupt(InterruptModes mode, void (*callback)(T), T* arg);
        */
    };

}
#endif