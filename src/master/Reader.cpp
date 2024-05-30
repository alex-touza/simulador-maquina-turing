#include "Reader.h"

Reader::Reader(int pinS0, int pinS1, int pinS2, int pinS3, int pinOut) : s0(pinS0), s1(pinS1), s2(pinS2), s3(pinS3), out(pinOut) {}

void Reader::begin() {
    s0.begin();
    s1.begin();
    s2.begin();
    s3.begin();
    out.begin();

    s0.on();
    s1.on();
}

Reader::Color Reader::readColor()
{
    Reader::Color color{};

    s2.off();
    s3.off();
    color.red = out.pulseIn(!out.read());

    s3.on();
    color.blue = out.pulseIn(!out.read());

    s2.on();
    color.green = out.pulseIn(!out.read());
    delay(50);
    
    return color;
}

Reader::Info Reader::readHold() {
    bool initial = this->readBlack();
    unsigned long start = millis();

    while (delay(100), this->readBlack() == initial);



}
