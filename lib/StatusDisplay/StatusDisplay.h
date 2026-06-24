#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class StatusDisplay{
public:
    StatusDisplay(byte address, byte cols, byte rows);
    void begin();
    void showWelcome();
    void update(unsigned long now, bool lightOn, bool alerting, bool manual, int motionCount);
private:
    static const unsigned long REFRESH_MS = 250;

    LiquidCrystal_I2C lcd;
    byte _cols;
    byte _rows;

    unsigned long _lastDraw;

    bool _hasPrev;
    bool _pLight, _pAlert, _pManual;
    int _pCount;

    void printPadded(const char* text);
};