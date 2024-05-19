//
// Created by backo on 1/5/2024.
//

#ifndef SIMULADOR_MAQUINA_TURING_COMMUNICATION_H
#define SIMULADOR_MAQUINA_TURING_COMMUNICATION_H


#include <Arduino.h>
#include "../Utilities.h"


class Communication {
public:
    class Codes {
    private:
        String* values;
        int n;
    public:
        explicit Codes(String[], int);

        String* decode(int);

        int encode(const String&);
    };

    Communication(const Codes&, const HardwareSerial&, long);

    void begin();


    void sendChar(char);

    void sendCode(const String&);


    char readChar();

    String* readCode();

    int received();


protected:
    Codes codes;
    HardwareSerial serial;
    long speed;
};

const String ERROR_OUT_OF_RANGE = "error: out of range";
const String ERROR_INVALID_CHARACTER = "error: invalid character";


#endif //SIMULADOR_MAQUINA_TURING_COMMUNICATION_H

