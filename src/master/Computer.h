//
// Created by backo on 28/5/2024.
//

#ifndef SIMULADOR_MAQUINA_TURING_COMPUTER_H
#define SIMULADOR_MAQUINA_TURING_COMPUTER_H


#include "common/Head.h"
#include "common/Communication.h"

#define STATE_ADDRESS_SIZE 3
#define DECODE_STATE_SIZE 10

constexpr int stateSize = (2 + STATE_ADDRESS_SIZE) * 3;

namespace Computer {
    struct State; // forward declaration per permetre ús mutu State-Instruction


    struct Instruction {
        bool write;
        Direction dir;
        State* nextState; // pot ser nullptr
    };

    struct PartialInstruction : Instruction {
        int nextStateId;
    };

    struct State {
        int id = -1; // assignat durant la codificació
        Instruction ifZero = {ZERO, RIGHT, nullptr};
        Instruction ifOne = {ONE, RIGHT, nullptr};
        Instruction ifBlank = {ZERO, RIGHT, nullptr};

        State* operator()(Communication& communication);

        virtual Instruction* operator[](int);

        State(const Instruction& ifZero, const Instruction& ifOne, const Instruction& ifBlank);

        State() = default;
    };

    struct PartialState : State {
        PartialInstruction ifZeroPartial;
        PartialInstruction ifOnePartial;
        PartialInstruction ifBlankPartial;

        PartialState(
                const PartialInstruction& ifZeroPartial, const PartialInstruction& ifOnePartial,
                const PartialInstruction& ifBlankPartial);

        PartialInstruction* operator[](int) override;

    };

    class Program {
    protected:
        State** states; // array de punters perquè es pugui posar nullptr als llocs buits
        int n;

    public:
        Program(State**, int);

        void compute(Communication&);

        int encode(bool*, int);

        static Program decode(bool*, int);

    };


} // Machine

#endif //SIMULADOR_MAQUINA_TURING_COMPUTER_H
