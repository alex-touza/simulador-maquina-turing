//
// Created by backo on 1/5/2024.
//

#ifndef SIMULADOR_MAQUINA_TURING_COMMUNICATION_H
#define SIMULADOR_MAQUINA_TURING_COMMUNICATION_H


#include <Arduino.h>

class Communication {
protected:

    HardwareSerial serial;
    long speed;
public:
    Communication(const HardwareSerial&, long);
    void begin();


    template<typename T>
    void send(T value);


    int received();
    char readChar();
    String readString();
};


#endif //SIMULADOR_MAQUINA_TURING_COMMUNICATION_H

