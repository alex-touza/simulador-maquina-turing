//
// Created by backo on 19/5/2024.
//

#ifndef SIMULADOR_MAQUINA_TURING_TAPE_H
#define SIMULADOR_MAQUINA_TURING_TAPE_H

#include "LEDArray.h"
#include "common/Head.h"

#define TAPE_LENGTH 128
#define VIEW_LENGTH 15

namespace Computer {

    class Tape {
    public:
        Tape();

        void begin();


        void write(Cell);

        void update();

        void update(int, int);

        bool move(Direction);

        Cell& read();

        int head = 7;

    private:
        LEDArray blanks{22, 37};
        LEDArray ones{38, 52};

        Cell buffer[TAPE_LENGTH]{};
    };
}

#endif //SIMULADOR_MAQUINA_TURING_TAPE_H
