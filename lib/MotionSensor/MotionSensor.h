#pragma once
#include <Arduino.h>

class MotionSensor{
public:
    MotionSensor(int pin);
    void begin();
    bool detected();
private:
    int _pin;
};