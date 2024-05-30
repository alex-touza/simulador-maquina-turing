//
// Created by backo on 1/5/2024.
//

#ifndef SIMULADOR_MAQUINA_TURING_COMMUNICATION_H
#define SIMULADOR_MAQUINA_TURING_COMMUNICATION_H


#include <Arduino.h>
#include "common/utilities/Utilities.h"

#define INSTRUCTIONS 10

enum class Codes : int {
    NONE = -1,

    ZERO = 0, ONE = 1, BLANK = 2,

    LEFT = 3, RIGHT = 4, QUERY = 5, WRITE = 6, RESET = 7,

    BUTTONPRESSED = 8,

    ERROR_OUT_OF_RANGE = 9, ERROR_INVALID_CHARACTER = 10
};

String getCode(Codes);
Codes getCode(const String&);

class Communication {
public:
    /*
    class Codes {
    private:
        String* values;
        const int n;
    public:
        explicit Codes();

        String* decode(int);

        int encode(const String&);
    };
*/
    Communication(HardwareSerial*, long);

    void begin();


    void sendChar(char);

    void sendCode(Codes);


    char readChar();

    Codes readCode();

    String readString();

    int received();


    HardwareSerial* serial;
protected:
    long speed;
};


#endif //SIMULADOR_MAQUINA_TURING_COMMUNICATION_H

