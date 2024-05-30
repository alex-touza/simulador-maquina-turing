//
// Created by backo on 30/5/2024.
//

#ifndef SIMULADOR_MAQUINA_TURING_TIMER_H
#define SIMULADOR_MAQUINA_TURING_TIMER_H


class Timer {
private:
    unsigned long start;
    unsigned long duration;
    bool finished;
public:
    explicit Timer(unsigned long);

    void reset();

    bool hasFinished();
};


#endif //SIMULADOR_MAQUINA_TURING_TIMER_H
