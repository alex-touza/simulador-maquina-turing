//
// Created by backo on 27/5/2024.
//

#ifndef SIMULADOR_MAQUINA_TURING_HEAD_H
#define SIMULADOR_MAQUINA_TURING_HEAD_H

namespace Computer {
    enum Cell : int {
        ZERO = 0,
        ONE = 1,
        BLANK = 2,
    };

    inline Cell boolToCell(bool b) {
        return b ? ONE : BLANK;
    }

    inline bool cellToBool(Cell c) {
        return c == ONE;
    }

    enum Direction : int {
        LEFT = 3,
        RIGHT = 4
    };

    inline Direction boolToDirection(bool b) {
        return b ? RIGHT : LEFT;
    }

    inline bool directionToBool(Direction c) {
        return c == RIGHT;
    }

    inline char cellToChar(Cell c) {
        switch (c) {
            case Cell::BLANK:
                return 'b';
            case Cell::ZERO:
                return '0';
            case Cell::ONE:
                return '1';
            default:
                return 'X';
        }
    }

    inline char directionToChar(Direction d) {
        switch (d) {
            case Direction::LEFT:
                return 'l';
            case Direction::RIGHT:
                return 'r';
        }
    }
}

#endif //SIMULADOR_MAQUINA_TURING_HEAD_H
