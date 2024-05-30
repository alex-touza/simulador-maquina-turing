#ifndef SIMULADOR_MAQUINA_TURING_READER_H
#define SIMULADOR_MAQUINA_TURING_READER_H

#include <Arduino.h>
#include "common/pins/DigitalOut.h"
#include "common/pins/DigitalIn.h"

using namespace TMPins;

class Reader {
private:
    DigitalOut s0;
    DigitalOut s1;
    DigitalOut s2;
    DigitalOut s3;
    DigitalIn out;
public:
    struct Color {
        byte red;
        byte green;
        byte blue;
    };

    struct Info {
        bool black;
        unsigned long length;
    };

    Reader(int pinS0, int pinS1, int pinS2, int pinS3, int pinOut);
    
    void begin();

    Color readColor();

    bool readBlack() {return false;};

    Info readHold();
};

#endif