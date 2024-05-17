#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    Serial1.begin(38400);

}

void loop() // run over and over
{
    if (Serial.available())
        Serial1.write(Serial.read());
}