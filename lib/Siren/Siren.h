#pragma once
#include <Arduino.h>

class Siren {
public:
    Siren(int ledPin, int buzzerPin);
    void begin();

    void apply(bool lightOn, bool alerting, unsigned long now);
private:
    int _ledPin;
    int _buzzerPin;
};