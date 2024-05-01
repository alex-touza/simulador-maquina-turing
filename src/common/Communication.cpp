//
// Created by backo on 1/5/2024.
//

#include "Communication.h"
#include "Arduino.h"

Communication::Communication(int _rxPin, int _txPin) : SoftwareSerial(_rxPin, _txPin), rxPin(_rxPin), txPin(_txPin) {

}

void Communication::begin(long speed) {
    pinMode(this->rxPin, OUTPUT);
    pinMode(this->txPin, INPUT);

    SoftwareSerial::begin(speed);

}

