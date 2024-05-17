#include "EntradaDigital.h"
#include "Arduino.h"


void CDPins::EntradaDigital::begin() {
    pinMode(this->pin, INPUT);
    this->active = false;
}

unsigned int CDPins::EntradaDigital::read(bool debounce, bool invert) {

    unsigned int _value = digitalRead(this->pin);
    if (invert) _value = !_value;

    if (debounce) {
        if (_value) {
            _value = 0;
            this->active = true;

        } else if (this->active) {
            _value = 1;
            this->active = false;
        }

    }

    return this->value = _value;
}

unsigned long CDPins::EntradaDigital::pulseIn() {
    this->value = 0;
    return ::pulseIn(this->pin, HIGH);
}

/*
void CDPins::EntradaDigital::attachInterrupt(InterruptModes mode, void (* callback)()) {
    ::attachInterrupt(digitalPinToInterrupt(this->pin), callback, mode);
}

template<typename T>
void CDPins::EntradaDigital::attachInterrupt(InterruptModes mode, void (* callback)(T), T* arg) {
    ::attachInterruptArg(digitalPinToInterrupt(this->pin), callback, arg, mode);
}*/
