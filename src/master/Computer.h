//
// Created by backo on 28/5/2024.
//

#ifndef SIMULADOR_MAQUINA_TURING_COMPUTER_H
#define SIMULADOR_MAQUINA_TURING_COMPUTER_H


#include "common/Machine.h"
#include "common/Communication.h"

#define STATE_ADDRESS_SIZE 3

constexpr int stateSize = (2 + STATE_ADDRESS_SIZE) * 3;

namespace Computer {
    struct State; // forward declaration per permetre ús mutu State-Instruction


    struct Instruction {

        bool write;
        Direction dir;
        State* nextState; // pot ser nullptr

        Instruction(Direction dir, State* nextState, bool write);
    };

    struct State {
        int id = -1; // assignat durant la codificació
        Instruction ifZero;
        Instruction ifOne;
        Instruction ifBlank;

        const Instruction* operator[](int) const;

        State* operator()(Communication&); // pot retornar nullptr
        State(const Instruction& ifZero, const Instruction& ifOne, const Instruction& ifBlank);
    };

    template<int n>
    class Program {
    protected:
        State* states[n]; // array de punters perquè es pugui posar nullptr als llocs buits

    public:
        void compute(Communication&);

        int countStates(); // comptar els que no són nullptr

        bool encode(bool*, int);

        explicit Program(State*[n]);
    };



    template
    class Program<10>;


} // Machine

#endif //SIMULADOR_MAQUINA_TURING_COMPUTER_H
