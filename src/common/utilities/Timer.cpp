//
// Created by backo on 30/5/2024.
//

#include <Arduino.h>
#include "Timer.h"

Timer::Timer(unsigned long _duration) : start(0), duration(_duration), finished(false) {

}

void Timer::reset() {
    this->start = millis();
    this->finished = false;
}

bool Timer::hasFinished() {
    return finished || (finished = (millis() - start > duration));
}
