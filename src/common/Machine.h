//
// Created by backo on 27/5/2024.
//

#ifndef SIMULADOR_MAQUINA_TURING_MACHINE_H
#define SIMULADOR_MAQUINA_TURING_MACHINE_H

namespace Computer {
    enum Cell : int {
        ZERO = 0,
        ONE = 1,
        BLANK = 2,
    };

    inline bool boolToCell(bool b) {
        return b ? ONE : BLANK;
    }

    inline bool cellToBool(Cell c) {
        return c == ONE;
    }

    enum Direction : int {
        LEFT = 3,
        RIGHT = 4
    };

    inline bool boolToDirection(bool b) {
        return b ? RIGHT : LEFT;
    }

    inline bool directionToBool(Direction c) {
        return c == RIGHT;
    }
}

#endif //SIMULADOR_MAQUINA_TURING_MACHINE_H
