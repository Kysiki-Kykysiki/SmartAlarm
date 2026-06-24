#pragma once
#include <Arduino.h>

class MotionLog{
public:
    static const byte CAPACITY = 16;
    
    MotionLog(unsigned long windowMS = 60000);

    void add(unsigned long now);
    int countWithin(unsigned long now);
    void reset();
private:
    unsigned long times[CAPACITY];
    unsigned long windowMS;
    byte count;

    void purgeOld(unsigned long now);
};