#include "SortidaAnalogica.h"
#include "Arduino.h"

void CDPins::SortidaAnalogica::begin() {
    pinMode(this->pin, OUTPUT);
}

void CDPins::SortidaAnalogica::set(unsigned int _value) {
    analogWrite(this->pin, (int) _value);
    this->value = _value;
}

void CDPins::SortidaAnalogica::set(int _value, int min, int max) {
    this->set(map(constrain(_value, min, max), min, max, 1023, 0));
}
