#include <MotionLog.h>

MotionLog::MotionLog(unsigned long window){
    windowMS = window;
    reset();
}

void MotionLog::reset(){
    count = 0;
}
void MotionLog::purgeOld(unsigned long now){
    byte fresh = 0;
    for(byte i = 0; i < count; i++){
        if(now - times[i] <= windowMS){
            times[fresh++] = times[i];
        }
    }
    count = fresh;
}

void MotionLog::add(unsigned long now){
    purgeOld(now);
    if(count < CAPACITY){
        times[count++] = now;
    }
    else{
        for(byte i = 1; i < CAPACITY; i++) times[i-1] = times[i];
        times[CAPACITY - 1] = now;
    }
}

int MotionLog::countWithin(unsigned long now){
    purgeOld(now);
    return count;
}