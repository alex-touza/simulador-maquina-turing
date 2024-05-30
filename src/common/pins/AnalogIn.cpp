//
// Created by backo on 18/2/2024.
//

#include "AnalogIn.h"
#include "Arduino.h"

void TMPins::AnalogIn::begin() {
    pinMode(this->pin, INPUT);
}

unsigned int TMPins::AnalogIn::read() {
    return this->value = analogRead(this->pin);
}
