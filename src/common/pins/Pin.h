#ifndef CASA_DOMOTICA_PIN_H
#define CASA_DOMOTICA_PIN_H

namespace CDPins {
    // Classe abstracta per als pins d'entrada i sortida
    class Pin {
    protected:
        const int pin;
    public:
        explicit Pin(int _pin);
        virtual void begin()=0; // virtual => obliga a ser redefinit en la classe filla

        unsigned int value;
    };
}


#endif
