//
// Created by backo on 1/5/2024.
//

#include "Communication.h"
#include "Arduino.h"

/*
Communication::Codes::Codes() : n(INSTRUCTIONS) {

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
*/

String getCode(Codes code) {
    switch (code) {
        case Codes::ZERO:
            return "ZERO";
        case Codes::ONE:
            return "ONE";
        case Codes::BLANK:
            return "BLANK";
        case Codes::LEFT:
            return "LEFT";
        case Codes::RIGHT:
            return "RIGHT";
        case Codes::QUERY:
            return "QUERY";
        case Codes::WRITE:
            return "WRITE";
        case Codes::RESET:
            return "RESET";
        case Codes::ERROR_OUT_OF_RANGE:
            return "ERROR_OUT_OF_RANGE";
        case Codes::ERROR_INVALID_CHARACTER:
            return "ERROR_INVALID_CHARACTER";
        case Codes::BUTTONPRESSED:
            return "BUTTONPRESSED";
        default:
            return "";
    }
}

Codes getCode(const String& code) {
    if (code == "ZERO")
        return Codes::ZERO;
    else if (code == "ONE")
        return Codes::ONE;
    else if (code == "BLANK")
        return Codes::BLANK;
    else if (code == "LEFT")
        return Codes::LEFT;
    else if (code == "RIGHT")
        return Codes::RIGHT;
    else if (code == "QUERY")
        return Codes::QUERY;
    else if (code == "WRITE")
        return Codes::WRITE;
    else if (code == "RESET")
        return Codes::RESET;
    else if (code == "ERROR_OUT_OF_RANGE")
        return Codes::ERROR_OUT_OF_RANGE;
    else if (code == "ERROR_INVALID_CHARACTER")
        return Codes::ERROR_INVALID_CHARACTER;
    else if (code == "BUTTONPRESSED")
        return Codes::BUTTONPRESSED;
    else return Codes::NONE;

}

Communication::Communication(HardwareSerial* _serial, long _speed) :
        serial(_serial),
        speed(_speed) {
}

void Communication::begin() {
    this->serial->begin(speed);
}

int Communication::received() {
    return serial->available();
}


void Communication::sendChar(char c) {
    this->serial->write(c);
}


void Communication::sendCode(Codes code) {
    Serial.println("send " + getCode(code));
    this->serial->write(static_cast<int>(code));
}

char Communication::readChar() {
    if (this->received()) {
        return static_cast<char>(this->serial->read());
    } else return '\0';
}

Codes Communication::readCode() {
    auto code = static_cast<Codes>(this->serial->read());

    Serial.println("read " + getCode(code));

    return code;
}

String Communication::readString() {
    return this->serial->readString();
}



