#include "AnalogOut.h"
#include "Arduino.h"

void TMPins::AnalogOut::begin() {
    pinMode(this->pin, OUTPUT);
}

void TMPins::AnalogOut::set(unsigned int _value) {
    analogWrite(this->pin, (int) _value);
    this->value = _value;
}

void TMPins::AnalogOut::set(int _value, int min, int max) {
    this->set(map(constrain(_value, min, max), min, max, ANALOG_WRITE_MAX, 0));
}

void TMPins::AnalogOut::on() {
    this->set(1, 0, 1);

}

void TMPins::AnalogOut::off() {
    this->set(0, 0, 1);
}
