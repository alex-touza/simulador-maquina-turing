//
// Created by backo on 19/5/2024.
//

#ifndef SIMULADOR_MAQUINA_TURING_LEDARRAY_H
#define SIMULADOR_MAQUINA_TURING_LEDARRAY_H

#include "Arduino.h"

struct LEDArray {
    LEDArray(int, int);

    void begin() const;

    void set(int, bool) const;

    void setAll(bool) const;

    int pinStart;
    int pinEnd;
};


#endif //SIMULADOR_MAQUINA_TURING_LEDARRAY_H
