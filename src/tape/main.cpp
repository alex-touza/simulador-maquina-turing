#include <Arduino.h>
#include "common/Communication.h"
#include "Tape.h"
#include "common/pins/DigitalIn.h"

using TMPins::DigitalIn;
Computer::Tape tape;

Communication communication(nullptr, 38400);

constexpr int nButtons = 6;
int buttonsPins[nButtons] = {10, 11, 12, 13, 14, 15};

DigitalIn* buttons[nButtons];

void setup() {
    tape.begin();

    int* pinPtr = buttonsPins;
    for (auto& button : buttons) {
        button = new DigitalIn(*pinPtr);
        button->begin();

        ++pinPtr;
    }


    Serial.begin(115200);

    communication.serial = &Serial1;

    communication.begin();
}

void loop() {

    if (communication.received()) {
        Codes code = communication.readCode();

        Serial.println("Read instruction " + getCode(code));

        if (code == Codes::LEFT || code == Codes::RIGHT) {
            Serial.println("Direction");
            auto d = static_cast<Computer::Direction>(static_cast<int>(code));

            if (!tape.move(d)) {
                communication.sendCode(Codes::ERROR_INVALID_CHARACTER);
            }

        } else if (code == Codes::QUERY) {
            Serial.println("Query");

            // woah
            communication.sendCode(static_cast<Codes>(static_cast<int>(tape.read())));

        } else if (code == Codes::WRITE) {
            Serial.println("Write");
            Codes cell = communication.readCode();

            // woah woah
            tape.write(static_cast<Computer::Cell>(static_cast<int>(cell)));
        }
    } else if (true) {
        Serial.println("Buttons");

        for (const auto& button : buttons) {
            Serial.print(button->read(true));
        }

        Serial.println();
    }

}
