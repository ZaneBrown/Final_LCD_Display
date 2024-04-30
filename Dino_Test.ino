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
int positions[2][16] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};//row, col
float velocity = 1;
float velocity_bound = 2;
int last_spawn = 0;
int updates_velocity = 0;
int spawn_time = 4000/velocity;

int last_update = 0;
int update_time = spawn_time/6;

int score_overall = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);//col, row
  lcd.createChar(0, dino);//lcd has max of 8 custom characters
  lcd.createChar(1, cacti);
}

void loop() {
  //lcd.print("1. Dinosaur Game");
  start_game();
  while(game == true) {
    update_game();
    
    if(joystick.was_pressed() == 1) {
      int start_time = millis();
      draw(dino_char, 0, 0);
      lcd.setCursor(0,1);
      positions[0][0] = 2;
      positions[1][0] = 0;
      lcd.print(" ");
      while(millis()-start_time <= update_time*2) {
        update_game();
      }
      draw(dino_char, 0, 1);
      lcd.setCursor(0,0);
      lcd.print(" ");
      positions[1][0] = 2;
      positions[0][0] = 0;//move dinosaur to the right by 1, create new file
    }
  }
}

void start_game() {
  draw(dino_char, 0, 1);
  positions[1][0] = 2;
  update_score();
}

void end_game() {
  lcd.clear();
  game = false;
  //lcd.setCursor
}

void update_score() {
  if(game == true) {
    score_overall = millis()/1000;
  }
  int length = numdigits(score_overall);
  lcd.setCursor(15-length, 0);
  lcd.print(score_overall);
  lcd.setCursor(15-length-6, 0);
  lcd.print("Score:");
}

void update_game() {
  if(millis() - last_spawn >= spawn_time){
    if(updates_velocity % 7 == 0 && velocity < velocity_bound) {
      velocity += 0.1;
    }
    last_spawn += spawn_time;
    spawn_time = 4000/velocity;
    updates_velocity += 1;
    cacti_spawn();
    }

    if(millis() - last_update >= update_time) {
      update_all_cacti();
      last_update+=update_time;
      update_time = spawn_time/6;
      update_score();
    }
}

void update_all_cacti(){
  for(int i = 1; i <= 15; i++) {
    if(positions[1][1] == 1 && positions[1][0] == 2) {
      end_game();
    }
    else if(positions[1][i] == 1) {
      draw(cacti_char, i-1, 1);
      lcd.setCursor(i, 1);
      lcd.print(" ");
      positions[1][i-1] = 1;
      positions[1][i] = 0;
    }
  }
}

void cacti_spawn() {
  draw(cacti_char, 15, 1);
  positions[1][15] = 1;
}









int numdigits(int i) {
    int digits;
    i = abs(i);
    if (i < 10)
      digits = 1;
    else
      digits = (int)(log10((double)i)) + 1;
    return digits;
}

void draw(byte char_name, int xPos, int yPos) {
  lcd.setCursor(xPos, yPos);
  lcd.write(char_name);
}
