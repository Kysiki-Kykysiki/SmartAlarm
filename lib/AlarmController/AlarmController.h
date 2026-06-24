#pragma once
#include <Arduino.h>
#include <MotionLog.h>

class AlarmController{
public:
    static const unsigned long MOTION_TIMEOUT_MS  = 10000; 
    static const unsigned long MANUAL_DURATION_MS = 15000; 
    static const unsigned long MOTION_WINDOW_MS = 60000; 
    static const int ALERT_THRESHOLD = 5;       
    static const unsigned long RETRIGGER_MS = 2000;

    AlarmController();
    void update(unsigned long now, bool motion, bool buttonPressed);
    
    bool isLightOn() const;
    bool isAlerting() const;
    bool isManualMode() const;
    int motionCount() const;
    void reset();

private:
    MotionLog log;

    bool prevMotion;
    unsigned long lastMotionTime;
    unsigned long lastCountTime;
    bool autoActive;

    unsigned long manualUntil;
    bool manualActive;

    bool lightOn;
    bool alerting;
    int lastCount;
};
