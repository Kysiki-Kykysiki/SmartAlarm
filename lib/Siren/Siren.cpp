#include <Siren.h>

Siren::Siren(int ledPin, int buzzerPin){
    _ledPin = ledPin;
    _buzzerPin = buzzerPin;
}

void Siren::begin(){
    pinMode(_ledPin, OUTPUT);
    pinMode(_buzzerPin,OUTPUT);
    digitalWrite(_ledPin, LOW);
    digitalWrite(_buzzerPin, LOW);
}

void Siren::apply(bool lightOn, bool alerting, unsigned long now){
    if(alerting){
        bool phase = (now / 120) % 2;
        digitalWrite(_ledPin, phase ? HIGH : LOW);
        digitalWrite(_buzzerPin, phase ? HIGH : LOW);
    }
    else {
        digitalWrite(_ledPin, lightOn ? HIGH : LOW);
        digitalWrite(_buzzerPin, LOW);
    }
}