//
// Created by backo on 19/5/2024.
//

#include "LEDArray.h"

LEDArray::LEDArray(int _pinStart, int _pinEnd) {
    this->pinStart = _pinStart;
    this->pinEnd = _pinEnd;
};

void LEDArray::begin() const {
    for (int i = this->pinStart; i <= this->pinEnd; ++i) {
        pinMode(i, OUTPUT);
    }
}

void LEDArray::set(int i, bool on) const {
    digitalWrite(this->pinStart + i, on);
}

void LEDArray::setAll(bool on) const {
    for (int i = this->pinStart; i <= this->pinEnd; ++i) {
        digitalWrite(i, on);
    }
}
