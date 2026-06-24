#include <Arduino.h>
#include <AlarmController.h>
#include <MotionSensor.h>
#include <Button.h>
#include <Siren.h>
#include <StatusDisplay.h>

const int PIN_PIR = 2;
const int PIN_LED = 8;
const int PIN_BUTTON = 3;
const int PIN_BUZZER = 9;

const byte LCD_ADDR = 0x27;
const byte LCD_COLS = 16;
const byte LCD_ROWS = 2;

AlarmController controller;
MotionSensor pir(PIN_PIR);
Button button(PIN_BUTTON);
Siren siren(PIN_LED, PIN_BUZZER);
StatusDisplay display(LCD_ADDR, LCD_COLS, LCD_ROWS);

void setup(){
    Serial.begin(9600);

    pir.begin();
    button.begin();
    siren.begin();
    display.begin();
    display.showWelcome();

    delay(100);
}

void loop(){
    unsigned long now = millis();

    bool motion = pir.detected();
    bool pressed = button.wasPressed();

    controller.update(now, motion, pressed);

    siren.apply(controller.isLightOn(), controller.isAlerting(), now);

    display.update(now, controller.isLightOn(),controller.isAlerting(),
                    controller.isManualMode(), controller.motionCount());

}