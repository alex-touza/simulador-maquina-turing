//
// Created by backo on 30/5/2024.
//

#include "Screen.h"

Screen::Screen() : LiquidCrystal_I2C(0x27, 16, 2) {}

bool Screen::Lines::operator==(const Screen::Lines& rhs) const {
    return upperLine == rhs.upperLine &&
           lowerLine == rhs.lowerLine;
}

bool Screen::Lines::operator!=(const Screen::Lines& rhs) const {
    return !(rhs == *this);
}

void Screen::begin() {
    this->init();
    this->backlight();
}

void Screen::update(const Screen::Lines& _lines, int id) {
    if (this->lines == _lines) return;

    this->update(_lines.upperLine, _lines.lowerLine, id);
}

void Screen::update(const String& upperLine, const String& lowerLine, int id) {
    if (this->lines == Lines{upperLine, lowerLine}) return;

    this->screenId = id;

    this->lines.lowerLine = lowerLine;
    this->lines.upperLine = upperLine;

    this->clear();
    this->setCursor(0, 0);
    this->print(upperLine);
    this->setCursor(0, 1);
    this->print(lowerLine);
}
