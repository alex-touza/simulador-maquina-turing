#include "SortidaDigital.h"
#include "Arduino.h"

void CDPins::SortidaDigital::begin() {
    pinMode(this->pin, OUTPUT);
}

void CDPins::SortidaDigital::on() {
    this->set(HIGH);
}

void CDPins::SortidaDigital::off() {
    this->set(LOW);
}

void CDPins::SortidaDigital::on(unsigned long t) {
    this->set(HIGH, t);
}

void CDPins::SortidaDigital::off(unsigned long t) {
    this->set(LOW, t);
}

void CDPins::SortidaDigital::set(unsigned int _value) {
    digitalWrite(this->pin, _value);
    this->value = _value;
}

void CDPins::SortidaDigital::set(unsigned int _estat, unsigned long t) {
    this->set(_estat);
    delay(t);
    this->set(!_estat);
}

unsigned int CDPins::SortidaDigital::toggle() {
    this->set(!this->value);
    return this->value;
}

void CDPins::SortidaDigital::pulseOut() {
    this->on();
    delayMicroseconds(10);
    this->off();
}