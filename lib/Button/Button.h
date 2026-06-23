#pragma once
#include <Arduino.h>

class Button{
public:
    Button(int pin);
    void begin();
    bool wasPressed();
private:
    int _pin;
    bool _lastState;
};