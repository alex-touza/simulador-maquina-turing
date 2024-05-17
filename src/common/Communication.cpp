//
// Created by backo on 1/5/2024.
//

#include "Communication.h"
#include "Arduino.h"


Communication::Communication(const HardwareSerial& _serial, long _speed) : serial(_serial), speed(_speed) {
}

void Communication::begin() {
    this->serial.begin(speed);
}

int Communication::received() {
    return serial.available();
}


template<typename T>
void Communication::send(T value) {
    this->serial.write(value);
}

char Communication::readChar() {
    if (this->received()) {
        return static_cast<char>(this->serial.read());
    } else return '\0';
}

String Communication::readString() {
    return this->serial.readString();
}
