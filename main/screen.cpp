// **** Functions for screen ****

#include "screen.h"
#include <LiquidCrystal.h>

const int rs = 41, en = 40, d4 = 37, d5 = 36, d6 = 35, d7 = 34;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);




void Screen::begin(void) {
  lcd.begin(16, 2);
  analogWrite(4, 255);
}

void Screen::clear(void) {
  lcd.clear();
}

void Screen::showCurrentFloor(int& currentFloor) {
  lcd.setCursor(0, 0);
  lcd.print("At floor: ");
  lcd.print(currentFloor);
  lcd.print(" ");
}

void Screen::showWantedFloor(int& wantedFloor) {
  lcd.setCursor(0, 1);
  lcd.print("Going to: ");
  lcd.print(wantedFloor);
  lcd.print(" ");
}

void Screen::closingDoor(void) {
  lcd.setCursor(0, 0);
  lcd.print("Closing door     ");
}

void Screen::openingDoor(void) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Opening door");
}

void Screen::promptFloor(void){
  lcd.setCursor(0, 1);
  lcd.print("Choose floor");
}
