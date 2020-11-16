// **** Functions for screen ****

#include "screen.h"
#include <LiquidCrystal.h>

// Pins defined in documentation of "All-In-One Servolab"
const int rs = 41, en = 40, d4 = 37, d5 = 36, d6 = 35, d7 = 34;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Initiate screen by using Liquid Crystal library
void Screen::begin(void) {
  lcd.begin(16, 2);
  analogWrite(4, 255);
}

// Clear screen
void Screen::clear(void) {
  lcd.clear();
}

// Print current floor on screen
void Screen::showCurrentFloor(int& currentFloor) {
  lcd.setCursor(0, 0);
  lcd.print("At floor: ");
  lcd.print(currentFloor);
  lcd.print(" ");
}

// Show wanted floor on screen
void Screen::showWantedFloor(int& wantedFloor) {
  lcd.setCursor(0, 1);
  lcd.print("Going to: ");
  lcd.print(wantedFloor);
  lcd.print(" ");
}

// Show closing door text on screen
void Screen::closingDoor(void) {
  lcd.setCursor(0, 0);
  lcd.print("Closing door     ");
}

// Show opening door text on screen
void Screen::openingDoor(void) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Opening door");
}

// Show choose floor text on screen
void Screen::promptFloor(void){
  lcd.setCursor(0, 1);
  lcd.print("Choose floor");
}
