//inital lcd display
#include <LiquidCrystal.h>
#include "bitmaps.h"
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//initial joystick
#include "Joystick.h"
#define xPin A0
#define yPin A1
#define swPin 12
Joystick joystick(xPin, yPin, swPin);

//intial dino game
int y_dino = 0;
int y_lower = 0;
int y_upper = 3;
const byte dino_char = 0;
const byte cacti_char = 1;
bool game = true;//true if still playing, false if died


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);//col, row

  lcd.createChar(0, dino);//lcd has max of 8 custom characters
  lcd.createChar(1, cacti);
}

void loop() {
  start_game();
  while(game == true) {
    if(joystick.was_pressed() == 1) {
      jump();
    }
  }
  end_game();
}

void start_game() {
  draw(dino_char, 0, 1);
  update_score();
  //start timer?
}

void end_game() {
  //put score up, with game over
  //return to menu?
  //time spent in game?
}

void update_score() {
  //update and draw score
}

void jump(){
  draw(dino_char, 0, 0);
  lcd.setCursor(0,1);
  lcd.print(" ");
  delay(1000);
  draw(dino_char, 0, 1);
  lcd.setCursor(0,0);
  lcd.print(" ");
}

void draw(byte char_name, int xPos, int yPos) {
  lcd.setCursor(xPos, yPos);
  lcd.write(char_name);
}