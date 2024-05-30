//
// Created by backo on 19/5/2024.
//

#include "Arduino.h"
#include "Tape.h"

using namespace Computer;




Tape::Tape() {
    for (Cell& c : buffer) {
        c = BLANK;
    }
}

void Tape::begin() {
    blanks.begin();
    ones.begin();

    blanks.on();
    ones.off();
}

void Tape::write(Cell c) {
    Serial.println("Write " + String(cellToChar(c)) + " to pos " + String(head));
    buffer[head] = c;
    update(head, VIEW_LENGTH / 2);
}

void Tape::update() {
    Serial.println("Visible tape");

    int j = 0;
    for (int i = head - VIEW_LENGTH / 2; i < head + VIEW_LENGTH / 2 + 1; ++i) {
        update(i, j);
        Serial.print(cellToChar(buffer[i]));
        ++j;
    }

    Serial.println("\nTape");
    for (auto c : buffer) Serial.print(cellToChar(c));
    Serial.println();
}

void Tape::update(int bufferInd, int ledInd) {
    Serial.println("Set led #" + String(ledInd) + " from pos " + String(bufferInd));
    Cell& c = this->buffer[bufferInd];

    this->ones.set(c == ONE, ledInd);
    this->blanks.set(c == BLANK, ledInd);


}

bool Tape::move(Direction d) {
    if (d == LEFT) {
        if (this->head == VIEW_LENGTH / 2) return false;

        --this->head;
    } else {
        if (this->head == TAPE_LENGTH - VIEW_LENGTH / 2 - 1) return false;

        ++this->head;
    }

    Serial.println("Head pos " + String(this->head));

    update();
    return true;
}

Cell& Tape::read() {
    return buffer[this->head];
}
