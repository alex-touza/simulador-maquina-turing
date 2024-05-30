#include "DigitalOut.h"
#include "Arduino.h"

void TMPins::DigitalOut::begin() {
    pinMode(this->pin, OUTPUT);
}

void TMPins::DigitalOut::on() {
    this->set(HIGH);
}

void TMPins::DigitalOut::off() {
    this->set(LOW);
}

void TMPins::DigitalOut::on(unsigned long t) {
    this->set(HIGH, t);
}

void TMPins::DigitalOut::off(unsigned long t) {
    this->set(LOW, t);
}

void TMPins::DigitalOut::set(unsigned int _value) {
    digitalWrite(this->pin, _value);
    this->value = _value;
}

void TMPins::DigitalOut::set(unsigned int _estat, unsigned long t) {
    this->set(_estat);
    delay(t);
    this->set(!_estat);
}

unsigned int TMPins::DigitalOut::toggle() {
    this->set(!this->value);
    return this->value;
}

void TMPins::DigitalOut::pulseOut() {
    this->on();
    delayMicroseconds(10);
    this->off();
}