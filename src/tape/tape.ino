#include <Arduino.h>

constexpr int TAPE_LENGTH = 64;
constexpr int VIEW_LENGTH = 16;

class LEDArray {
public:
    LEDArray(int _pinStart, int _pinEnd) {
        this->pinStart = _pinStart;
        this->pinEnd = _pinEnd;
    };

    void begin() const {
        for (int i = pinStart; i <= pinEnd; ++i) {
            pinMode(i, OUTPUT);
        }
    }

    void set(int i, bool on) const {
        digitalWrite(pinStart + i, on);
    }

    void setAll(bool on) const {
        for (int i = pinStart; i <= pinEnd; ++i) {
            digitalWrite(i, on);
        }
    }

    int pinStart;
    int pinEnd;
};

class Tape {
public:
    enum Cell : int {
        BLANK = -1,
        ZERO = 0,
        ONE = 1,
    };

    enum Direction : int {
        LEFT,
        RIGHT
    };

    Tape() {
        for (Cell c : buffer) {
            c = BLANK;
        }
    }

    void begin() {
        blanks.begin();
        state.begin();

        blanks.setAll(true);
        state.setAll(false);
    }

    void test() {
        blanks.setAll(true);
        state.setAll(true);
        delay(1500);
        state.setAll(false);
    }

    void write(Cell c) {
        buffer[head] = c;
        update(head);
    }

    void update() {
        for (int i = head - 7; i < head + 8; ++i) {
            update(i);
        }
    }

    void update(int i) {
        Cell& c = buffer[i];

        state.set(i, c == ONE);
        blanks.set(i, c == BLANK);
    }

    bool move(Direction d) {
        if (d == LEFT) {
            if (head == VIEW_LENGTH / 2 - 1) return false;

            --head;
        } else {
            if (head == TAPE_LENGTH - VIEW_LENGTH / 2 - 1) return false;

            ++head;
        }

        update();
        return true;
    }

    Cell& read() {
        return buffer[head];
    }

    int head = 7;

private:
    LEDArray blanks{22, 37};
    LEDArray state{38, 52};

    Cell buffer[TAPE_LENGTH]{};
};

char encode(Tape::Cell c) {
    switch (c) {
        case Tape::BLANK:
            return 'b';
        case Tape::ZERO:
            return '0';
        case Tape::ONE:
            return '1';
    }
}

char encode(Tape::Direction c) {
    switch (c) {
        case Tape::LEFT:
            return 'l';
        case Tape::RIGHT:
            return 'r';
    }
}

Tape tape;

void setup() {
    tape.begin();


    // Open serial communications and wait for port to open:
    Serial.begin(115200);

    Serial1.begin(38400);
}

/*
 * errors:
 *  - ei: invalid character
 *  - er: out of range
 *
 */
void loop() {

    if (Serial1.available()) {
        char c = static_cast<char>(Serial1.read());
        Serial.println("Read char " + String(c));

        if (c == 'l' || c == 'r') {
            Tape::Direction d = c == 'r' ? Tape::Direction::RIGHT : Tape::Direction::LEFT;

            if (!tape.move(d)) {
                Serial1.write("er");
            }
        } else if (c == 'q') {
            String s = "c" + String(encode(tape.read()));
            Serial1.write(s.c_str()); // ??
        } else if (c == 'w') {
            char m = static_cast<char>(Serial1.read());

            switch (m) {
                case '0':
                    tape.write(Tape::ZERO);
                    break;
                case '1':
                    tape.write(Tape::ONE);
                    break;
                case 'b':
                    tape.write(Tape::BLANK);
                    break;
                default:
                    Serial1.write("ei");
            }
        }



        Serial1.write(10);
    }

}