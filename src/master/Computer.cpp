//
// Created by backo on 28/5/2024.
//

#include "Computer.h"

using namespace Computer;

Instruction::Instruction(Direction dir, State* nextState, bool write) : write(write), dir(dir), nextState(nextState) {}

State* State::operator()(Communication& communication) {
    communication.sendCode(Codes::QUERY);

    while (!communication.received());

    Codes cell = communication.readCode();

    Instruction* instruction;

    switch (cell) {
        case Codes::BLANK:
            instruction = &ifBlank;
            break;
        case Codes::ZERO:
            instruction = &ifZero;
            break;
        case Codes::ONE:
            instruction = &ifOne;
            break;
        default:
            Serial.println("Wrong code received.");
            return nullptr;
    }

    communication.sendCode(static_cast<Codes>(static_cast<int>(instruction->write)));
    delay(100);

    communication.sendCode(static_cast<Codes>(static_cast<int>(instruction->dir)));
    delay(100);

    return instruction->nextState;
}

State::State(const Instruction& ifZero, const Instruction& ifOne, const Instruction& ifBlank) : ifZero(ifZero),
                                                                                                ifOne(ifOne),
                                                                                                ifBlank(ifBlank) {}

const Instruction* State::operator[](int ind) const {
    switch (ind) {
        case 0:
            return &this->ifZero;
        case 1:
            return &this->ifOne;
        case 2:
            return &this->ifBlank;
        default:
            return nullptr;

    }
}

template<int n>
Program<n>::Program(State* _states[n]) : states(_states) {}

template<int n>
void Program<n>::compute(Communication& communication) {
    State* currentState = *this->states;
    while ((currentState = (*currentState)(communication)));
}

template<int n>
int Program<n>::countStates() {
    int count = 0;
    for (State* s : this->states) {
        if (!s) break;

        ++count;
    }
    return count;
}

template<int n>
int Program<n>::encode(bool* buffer, int bufferSize) {
    bool* start = buffer;

    int count = 0;
    int idCount = 1;

    int bitCount = 0;


    for (int i = 0; i < n; ++i) {
        State* s = this->states[i];

        if (!s) break;
        if ((count + 1) * stateSize > bufferSize) return -1;

        if (s->id == -1)
            s->id = idCount++; // retornar id i després sumar

        for (int j = 0; j < 3; ++j) {
            const Instruction* ins = (*s)[j];

            *(buffer++) = ins->write;
            *(buffer++) = directionToBool(ins->dir);


            if (ins->nextState) {
                if (ins->nextState->id == -1)
                    ins->nextState->id = idCount++;

                int nextId = ins->nextState->id;

                int pow = 1; // valor del bit més significatiu
                for (int k = 1; k < STATE_ADDRESS_SIZE; ++k) {
                    pow *= 2;
                }

                // iterar des de més significatiu a menys
                int ind = 0;
                for (int k = STATE_ADDRESS_SIZE - 1; k >= 0; --k) {
                    buffer[ind] = nextId >= pow;
                    if (nextId >= pow)
                        nextId -= pow;

                    pow /= 2;

                    ++ind;
                }

                if (nextId != 0) {
                    Serial.println("Program encode overflow!");
                    return -1;
                }

                buffer += STATE_ADDRESS_SIZE;
            } else {
                for (int k = 0; k < 3; ++k) {
                    *(buffer++) = false;
                }
            }

        }
        bitCount += 15;

        ++count;
    }
    return bitCount;

}

