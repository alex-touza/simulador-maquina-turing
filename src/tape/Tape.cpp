//
// Created by backo on 19/5/2024.
//

#include "Arduino.h"
#include "Tape.h"

using namespace Computer;

char Tape::encode(Cell c) {
    switch (c) {
        case Cell::BLANK:
            return 'b';
        case Cell::ZERO:
            return '0';
        case Cell::ONE:
            return '1';
    }
}

char Tape::encode(Direction c) {
    switch (c) {
        case Direction::LEFT:
            return 'l';
        case Direction::RIGHT:
            return 'r';
    }
}

Tape::Tape() {
    for (Cell& c : buffer) {
        c = BLANK;
    }
}

void Tape::begin() {
    blanks.begin();
    ones.begin();

    blanks.setAll(true);
    ones.setAll(false);
}

void Tape::write(Cell c) {
    Serial.println("Write " + String(Tape::encode(c)) + " to pos " + String(head));
    buffer[head] = c;
    update(head, VIEW_LENGTH / 2);
}

void Tape::update() {
    Serial.println("Visible tape");

    int j = 0;
    for (int i = head - VIEW_LENGTH / 2; i < head + VIEW_LENGTH / 2 + 1; ++i) {
        update(i, j);
        Serial.print(Tape::encode(buffer[i]));
        ++j;
    }

    Serial.println("\nTape");
    for (auto c : buffer) Serial.print(Tape::encode(c));
    Serial.println();
}

void Tape::update(int bufferInd, int ledInd) {
    Serial.println("Set led #" + String(ledInd) + " from pos " + String(bufferInd));
    Cell& c = buffer[bufferInd];

    ones.set(ledInd, c == ONE);
    blanks.set(ledInd, c == BLANK);


}

bool Tape::move(Direction d) {
    if (d == LEFT) {
        if (head == VIEW_LENGTH / 2) return false;

        --head;
    } else {
        if (head == TAPE_LENGTH - VIEW_LENGTH / 2 - 1) return false;

        ++head;
    }

    Serial.println("Head pos " + String(head));

    update();
    return true;
}

Cell& Tape::read() {
    return buffer[head];
}
