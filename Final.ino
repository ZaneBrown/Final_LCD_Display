/*

//inital lcd display
#include <LiquidCrystal.h>
#include "bitmaps.h"
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//initial joystick
#include "Joystick.h"
#define xPin A0
#define yPin A1
#define swPin 13
Joystick joystick(xPin, yPin, swPin);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);//col, row
}

void loop() {


  //timeout();
}


void timeout() {
  while(1==1) {
  }
}
*/