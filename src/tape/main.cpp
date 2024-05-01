#include <Arduino.h>
#include <SoftwareSerial.h>
#include "../common/Communication.h"

Communication communication(10, 11);

void setup()  {
    communication.begin(115200);

    int a = 32767;

}

void loop() {
    while (!Serial) {
    }
}