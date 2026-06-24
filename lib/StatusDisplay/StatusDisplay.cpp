#include <StatusDisplay.h>

StatusDisplay::StatusDisplay(byte address, byte cols, byte rows) : lcd(address, cols, rows) {
    _cols = cols;
    _rows = rows;
    _lastDraw = 0;
    _hasPrev = false;
}

void StatusDisplay::begin(){
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void StatusDisplay::showWelcome() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Smart Alarm");
    lcd.setCursor(0, 1);
    lcd.print("Guard ready");
}

void StatusDisplay::printPadded(const char* text){
    byte i = 0;
    while(text[i] != '\0' && i < _cols) {
        lcd.print(text[i]);
        i++;
    }
    while(i<_cols){
        lcd.print(' ');
        i++;
    }
}



void StatusDisplay::update(unsigned long now, bool lightOn, bool alerting, bool manual, int motionCount){
    if(_hasPrev && (now - _lastDraw < REFRESH_MS)){
        return;
    }

    if(_hasPrev && lightOn == _pLight && alerting == _pAlert && 
        manual == _pManual && motionCount == _pCount){
        return;
    }
    _pLight = lightOn; _pAlert = alerting; 
    _pManual = manual; _pCount = motionCount;

    _hasPrev = true;
    _lastDraw = now;

    lcd.setCursor(0,0);
    if(alerting){
        printPadded("!!!ALARM!!!");
    }
    else if(manual){
        printPadded("Manual Mode");
    }
    else if(lightOn){
        printPadded("Motion Mode");
    }
    else{
        printPadded("Guard Mode");
    }

    char line2[17];
    snprintf(line2, sizeof(line2), "%s M:%d", lightOn ? "LIGHT:ON" : "LIGHT:OFF", motionCount);
    lcd.setCursor(0,1);
    printPadded(line2);
}