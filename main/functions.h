// **** Defining functions ****

#include <arduino.h>
#include <LiquidCrystal.h>

// Pins
const int ledPin[] = {42, 43, 44, 45, 46, 47, 48, 49};
const int buttonPin[] = {22, 23, 24, 25, 26, 27, 28, 29}; // {0 ... 8}
const int mechEncButton = 2;

// Lcd setup
const int rs = 41, en = 40, d4 = 37, d5 = 36, d6 = 35, d7 = 34;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setPinModes() {
  // DEFINE LEDS
  for (int i = 8; i > 0; i--){
    pinMode(ledPin[i-1], OUTPUT);
  }

  // DEFINE BUTTONS
  for (int i = 0; i < 8; i++){
    pinMode(buttonPin[i], INPUT);
  }
  
  // DEFINE ENCODER BUTTON
  pinMode(mechEncButton, INPUT);

  // DEFINE LCD
  pinMode(4, OUTPUT);
  analogWrite(4, 255);
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
}

int joyDirection(double joyRead) {
  if (joyRead <= 350){
    return -1;
    }
  else if (joyRead >= 640){
    return 1;
    }
  else{
    return 0;
  }
}

// Function that awaits new floor input
void newFloorFunc(int* newFloorPnt, const int buttonPin[]){
  int chosenFloor = 100;
  Serial.println("What floor do you desire?");
  while (chosenFloor == 100) {
    for (int i = 0; i <= 7; i++){
      if (digitalRead(buttonPin[i]) == 1){
        chosenFloor = i;
      }
    }
  }
  *newFloorPnt = chosenFloor;
}
