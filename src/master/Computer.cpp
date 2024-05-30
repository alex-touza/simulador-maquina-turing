//
// Created by backo on 28/5/2024.
//

#include "Computer.h"

using namespace Computer;

Instruction* State::operator[](int ind) {
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

PartialState::PartialState(
        const PartialInstruction& _ifZeroPartial, const PartialInstruction& _ifOnePartial,
        const PartialInstruction& _ifBlankPartial) :
        ifZeroPartial(_ifZeroPartial),
        ifOnePartial(_ifOnePartial),
        ifBlankPartial(_ifBlankPartial) {}

PartialInstruction* PartialState::operator[](int ind) {
    switch (ind) {
        case 0:
            return &this->ifZeroPartial;
        case 1:
            return &this->ifOnePartial;
        case 2:
            return &this->ifBlankPartial;
        default:
            return nullptr;

    }
}

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
    delay(200);

    communication.sendCode(static_cast<Codes>(static_cast<int>(instruction->dir)));
    delay(200);

    return instruction->nextState;
}

State::State(const Instruction& ifZero, const Instruction& ifOne, const Instruction& ifBlank) : ifZero(ifZero),
                                                                                                ifOne(ifOne),
                                                                                                ifBlank(ifBlank) {}


Program::Program(State** _states, int _n) : states(_states), n(_n) {}

void Program::compute(Communication& communication) {
    State* currentState = *this->states;
    while ((currentState = (*currentState)(communication)));
}

int Program::encode(bool* buffer, int bufferSize) {
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

Program Program::decode(bool* buffer, int bufferSize) {
    PartialState* partialStates[DECODE_STATE_SIZE];

    PartialState** partialStateBuffer = partialStates;

    int id = 1;

    int statesCount = 0;

    for (int i = 0; i < bufferSize; ++i) {
        PartialInstruction* instructions[3];
        for (auto& instruction : instructions) {
            instruction = new PartialInstruction;
            instruction->write = *(buffer++);
            instruction->dir = boolToDirection(*(buffer++));

            instruction->nextStateId = 0;
            int pow = 1;
            for (int j = STATE_ADDRESS_SIZE-1; j >= 0; --j) {
                instruction->nextStateId += pow * buffer[j];
                pow *= 2;
            }


            buffer += STATE_ADDRESS_SIZE;
        }

        auto* thisState = new PartialState(*instructions[0], *instructions[1], *instructions[2]);
        thisState->id = id++;

        *partialStateBuffer = thisState;

        ++statesCount;
        ++partialStateBuffer;
        i += stateSize;
    }

    for (int i = statesCount; i < DECODE_STATE_SIZE; ++i) {
        partialStates[i] = nullptr;
    }

    auto** states = new State* [statesCount];


    // copiar partialStates a states
    auto** stateBuffer = states;
    for (PartialState* statePtr : partialStates) {
        if (!statePtr) break;

        *stateBuffer = new State;
        (*stateBuffer)->ifZero = static_cast<Instruction>(statePtr->ifZeroPartial);
        (*stateBuffer)->ifOne = static_cast<Instruction>(statePtr->ifOnePartial);
        (*stateBuffer)->ifBlank = static_cast<Instruction>(statePtr->ifBlankPartial);
        (*stateBuffer)->id = statePtr->id;

        ++stateBuffer;
    }

    // assignar els ids a states a partir de partialStates
    int i = 0;
    for (PartialState* statePtr : partialStates) {
        if (!statePtr) break;
        for (int j = 0; j < 3; ++j) {
            PartialInstruction* ptrIns = (*statePtr)[j];
            const int& nextStateId = ptrIns->nextStateId;
            if (nextStateId == 0)
                ptrIns->nextState = nullptr;
            else
                for (int k = 0; k < STATE_ADDRESS_SIZE; ++k)
                    if (states[k]->id == nextStateId) {
                        (*states[i])[j]->nextState = states[k];
                        break;
                    }


        }

        ++i;

    }
    return {states, DECODE_STATE_SIZE};
}
