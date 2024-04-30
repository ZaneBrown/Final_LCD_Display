#include "Joystick.h"

Joystick::Joystick(int pinX, int pinY, int pinZ) {
    this->pinX = pinX;
    this->pinY = pinY;
    this->pinZ = pinZ;

    pinMode(pinZ, INPUT);
    digitalWrite(this->pinZ, HIGH);
}

int Joystick::get_xPos() {
    int rawValue = analogRead(this->pinX);
    int value = map(rawValue, 0, 1023, -100, 100);
    return value;
}

int Joystick::get_yPos() {
    int rawValue = analogRead(this->pinY);
    int value = map(rawValue, 0, 1023, 100, -100);//joystick is opposite for y, so I flipped the limits
    return value;
}

bool Joystick::was_pressed() {
    int value = digitalRead(this->pinZ);
    if(value == 1) {return false;}
    else{return true;}
}