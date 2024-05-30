//
// Created by backo on 30/5/2024.
//

#ifndef SIMULADOR_MAQUINA_TURING_SCREEN_H
#define SIMULADOR_MAQUINA_TURING_SCREEN_H

#include <LiquidCrystal_I2C.h>
#include "common/utilities/Timer.h"

class Screen : LiquidCrystal_I2C {
private:
    Timer* timer = nullptr;
public:
    struct Lines {
        String upperLine;
        String lowerLine;

        bool operator==(const Lines& rhs) const;

        bool operator!=(const Lines& rhs) const;
    };

    Screen();

    void begin();

    void update(const String&, const String&, int id = -1);

    void update(const Lines&, int id = -1);

    int screenId = -1;

    Lines lines;
};


#endif //SIMULADOR_MAQUINA_TURING_SCREEN_H
