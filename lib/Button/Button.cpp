#include <Button.h>

Button::Button(int pin){
    _pin = pin;
    _lastState = false;
}

void Button::begin(){
    pinMode(_pin, INPUT_PULLUP);
}

bool Button::wasPressed(){
    bool pressed = (digitalRead(_pin) == LOW);
    bool edge = pressed && !_lastState;
    _lastState = pressed;
    return edge;
}