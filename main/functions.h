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

// Variables
long int arrivalTime = 50000;
bool service = false;


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

int checkCustomer() {
  int potmeter = map(analogRead(A0), 0, 1000, 0, 7);
  int joyDir = joyDirection(analogRead(A2));

  for (int i=8; i>0; i--) {
    digitalWrite(ledPin[i-1], 0);
  }

  digitalWrite(ledPin[potmeter], 1);

  if (joyDir != 0) {
    service = true;
    return 7-potmeter;
  } 
} 
