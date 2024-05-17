//
// Created by backo on 18/2/2024.
//

#include "EntradaAnalogica.h"
#include "Arduino.h"

void CDPins::EntradaAnalogica::begin() {
    pinMode(this->pin, INPUT);
}

unsigned int CDPins::EntradaAnalogica::read() {
    return this->value = analogRead(this->pin);
}
