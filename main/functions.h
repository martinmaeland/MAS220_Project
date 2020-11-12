// **** Defining functions ****

#include <arduino.h>

// Pins
const int ledPin[] = {42, 43, 44, 45, 46, 47, 48, 49};
const int buttonPin[] = {22, 23, 24, 25, 26, 27, 28, 29}; // {0 ... 8}
const int mechEncButton = 2;

// Variables
long int arrivalTime = -50000;
bool service = false;
bool arrived = false;
bool servingCustomer = false;
int desiredFloor = 0;
int desiredFloorPos = 0;
int joyDir = 0;
bool anotherCheckpoint = false;
enum mustGoDir{NOTHING, UP, DOWN};
mustGoDir dirToGo = NOTHING;
bool anotherOneCheckPoint = false;


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
  int _joyDir = joyDirection(analogRead(A2));

  for (int i=8; i>0; i--) {
    digitalWrite(ledPin[i-1], 0);
  }

  digitalWrite(ledPin[potmeter], 1);

  if (_joyDir != 0) {
    if (_joyDir == 1 && 7-potmeter < 7){
      dirToGo = UP;
      service = true;
    } else if(_joyDir == - 1 && 7-potmeter > 0){
      dirToGo = DOWN;
      service = true;
    }
    if (service == true){
      return 7-potmeter;
    }
  }
}
