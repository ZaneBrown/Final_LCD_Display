#include "Arduino.h"

class Joystick {
  public:
    Joystick(int, int, int);
    int get_xPos();
    int get_yPos();
    bool was_pressed();
  private:
    int pinX;
    int pinY;
    int pinZ;
};