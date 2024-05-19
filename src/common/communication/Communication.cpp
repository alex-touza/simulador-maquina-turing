//
// Created by backo on 1/5/2024.
//

#include "Communication.h"
#include "Arduino.h"

Communication::Codes::Codes(String _values[], int _n) : values(_values), n(_n) {
}

String* Communication::Codes::decode(int code) {
    if (code < 0 || code >= this->n) {
        return nullptr;
    }

    return this->values + code;
}

int Communication::Codes::encode(const String& value) {
    if (value == "" || value == " ") return -1;

    // TODO cerca binària?

    String* ptr = this->values;
    for (int i = 0; i < this->n; ++i, ++ptr) {
        if (value == *ptr) {
            return i;
        }
    }

    return -1;
}

Communication::Communication(const Codes& _codes, const HardwareSerial& _serial, long _speed) : codes(_codes),
                                                                                                serial(_serial),
                                                                                                speed(_speed) {
}

void Communication::begin() {
    this->serial.begin(speed);
}

int Communication::received() {
    return serial.available();
}


void Communication::sendChar(char c) {
    this->serial.write(c);
}


void Communication::sendCode(const String& value) {
    this->serial.write(this->codes.encode(value));
}

char Communication::readChar() {
    if (this->received()) {
        return static_cast<char>(this->serial.read());
    } else return '\0';
}

String* Communication::readCode() {
    return this->codes.decode(this->serial.read());
}


String codesArray[] = {
        "0",
        "1",
        "blank",

        // master --> tape
        "left",
        "right",
        "query",
        "write",
        "reset",

        // errors
        ERROR_OUT_OF_RANGE,
        ERROR_INVALID_CHARACTER
};

Communication::Codes codes(codesArray, 9);