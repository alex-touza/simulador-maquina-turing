#include <Arduino.h>
#include "common/Communication.h"
#include "common/pins/DigitalOut.h"
#include "Computer.h"

TMPins::DigitalOut d(4);

enum Screens {
    MAINMENU = 1,

};

using namespace Computer;
/*
State A({
                Direction::RIGHT, &A, Cell::ONE
        }, {
                Direction::RIGHT, &A, Cell::ONE
        }, {
                Direction::RIGHT, &A, Cell::ONE
        });

State* state[10] = {&A, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

Program programA(state, 10);
*/

int id = 1;
State* state[10] = {
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
};

Program program(state, 10);

bool buffer[50];


//Communication communication(nullptr, 38400);

void setup() {
    Serial.begin(38400);


    //communication.serial = &Serial1;
    //communication.begin();
    delay(200);

    Serial.println("a");
}

void loop() {
    /*
      if (Serial.available()) {
          String str = Serial.readString();
          str.trim();
          communication.sendCode(getCode(str));
      }
      if (communication.received()) {
          Serial.println(getCode(communication.readCode()));

      }
      */
    /*
    while (!Serial.available())
        ;

    String str = Serial.readString();
    str.trim();
    Serial.println(str);

    if (str == "encode") {
        Serial.print("Length: ");
        Serial.println(program.encode(buffer, 50));

        for (auto& b : buffer) Serial.print(b);
        Serial.println();
    } else if (str == "decode") {
        Serial.println("Enter bitset");
        while (!Serial.available())
            ;
        String str = Serial.readString();
        str.trim();

        for (int i = 0; i < str.length(); ++i) {
            buffer[i] = str[i] == '1';
        }

        program = Program::decode(buffer, 50);
    } else if (str == "newState") {
        State* s = new State();
        s->id = id++;

        Serial.println("id:" + String(s->id));

        for (int i = 0; i < 3; ++i) {
            Serial.println("Instruction" + String(i));
            Serial.println("write 1/0");
            while
                    (*s)[i]->write = Serial.readString() == "1";
            Serial.println("move l/r");
            (*s)[i]->dir = boolToDirection(Serial.readString() == "r");
            (*s)[i]->nextState = nullptr;
        }

        state[s->id-1] = s;
    }
     */
}
