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

namespace TMPins {
    class DigitalIn : public InputPin {
    public:
        using InputPin::InputPin;

        void begin() override;
        bool active;

        unsigned int read() override;

        unsigned int read(bool debounce /* = false */, bool invert = false);

        /*
        Equivalent a la funció integrada corresponent amb un
        interval de 10 microsegons.
        */
        unsigned long pulseIn(bool state = HIGH);

        /*
        void attachInterrupt(InterruptModes mode, void (*callback)());

        template<typename T>
        void attachInterrupt(InterruptModes mode, void (*callback)(T), T* arg);
        */
    };

}
#endif