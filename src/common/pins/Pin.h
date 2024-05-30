#ifndef CASA_DOMOTICA_PIN_H
#define CASA_DOMOTICA_PIN_H

namespace TMPins {
    // Classe abstracta per als pins d'entrada i sortida
    class Pin {
    protected:
        const int pin;
    public:
        explicit Pin(int _pin);

        virtual void begin() = 0;

        unsigned int value;
    };

    class OutputPin : public Pin {
    public:
        using Pin::Pin;

        virtual void set(unsigned int state) = 0;

        virtual void on() = 0;

        virtual void off() = 0;
    };

    class InputPin : public Pin {
    public:
        using Pin::Pin;
        virtual unsigned int read() = 0;
    };


}


#endif
