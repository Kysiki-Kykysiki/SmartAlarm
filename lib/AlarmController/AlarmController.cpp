#include <AlarmController.h>

AlarmController::AlarmController() : log(MOTION_WINDOW_MS){
    reset();
}

void AlarmController::reset(){
    log.reset();
    prevMotion = false;
    lastMotionTime = 0;
    lastCountTime = 0;
    autoActive = false;
    manualUntil = 0;
    manualActive = false;
    lightOn = false;
    alerting = false;
    lastCount = 0;
}

void AlarmController::update(unsigned long now, bool motion, bool buttonPressed){
    bool motionRising = motion && !prevMotion;
    prevMotion = motion;

    bool countNow = false;
    if(motionRising){
        countNow = true;
    }
    else if(motion && (now - lastCountTime >= RETRIGGER_MS)){
        countNow = true;
    }
    if(countNow){
        log.add(now);
        lastCountTime = now;
    }

    lastCount = log.countWithin(now);
    alerting = (lastCount > ALERT_THRESHOLD);

    if(buttonPressed){
        manualUntil = now + MANUAL_DURATION_MS;
        manualActive = true;
    }
    if(manualActive && now >= manualUntil){
        manualActive = false;
    }

    if(motion){
        lastMotionTime = now;
        autoActive = true;
    }
    if(autoActive && (now - lastMotionTime > MOTION_TIMEOUT_MS)){
        autoActive = false;
    }

    lightOn = autoActive || manualActive;
}

bool AlarmController::isLightOn() const {return lightOn;}
bool AlarmController::isAlerting() const {return alerting;}
bool AlarmController::isManualMode() const {return manualActive;}
int AlarmController::motionCount() const {return lastCount;}