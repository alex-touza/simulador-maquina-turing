#include <Arduino.h>
#include "common/Communication.h"

#include "Computer.h"

using namespace Computer;

State A({
                Direction::RIGHT, &A, Cell::ONE
        }, {
                Direction::RIGHT, &A, Cell::ONE
        }, {
                Direction::RIGHT, &A, Cell::ONE
        });

State* state[10] = {&A, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

Program<10> programA(state);


Communication communication(nullptr, 38400);

void setup() {
    Serial.begin(115200);

    communication.serial = &Serial1;
    communication.begin();
    delay(200);

}

void loop() {
    if (Serial.available()) {
        String str = Serial.readString();
        str.trim();
        communication.sendCode(getCode(str));
    }
    if (communication.received()) {
        Serial.println(getCode(communication.readCode()));

    }
}