//
// Created by backo on 1/5/2024.
//

#ifndef SIMULADOR_MAQUINA_TURING_COMMUNICATION_H
#define SIMULADOR_MAQUINA_TURING_COMMUNICATION_H


#include <SoftwareSerial.h>

class Communication : protected SoftwareSerial {
protected:
    int rxPin;
    int txPin;
public:
    Communication(int _rxPin, int _txPin);
    void begin(long speed);
};


#endif //SIMULADOR_MAQUINA_TURING_COMMUNICATION_H

