// **** DEFINING VARIABLES ****

#include "arduino.h"
#include <LiquidCrystal.h>

// PINS
const int ledPin[] = {42, 43, 44, 45, 46, 47, 48, 49};
const int buttonPin[] = {22, 23, 24, 25, 26, 27, 28, 29}; // {0 ... 8}
const int dcMotor[3] = {5, 6, 7}; // Decay, Phase, Enable
const int mechEncButton = 2;
const int encA = 20; // motor encoder a
const int encB = 21; // motor encoder b

// GLOBAL VARIABLES
int currentFloor = 0;
int newFloor = 0;
int customerFloor = 0;
int joyDir = 0;
bool service = false; // elevator service state
bool* servicePnt = &service;
volatile double theta = 0.0; // DC motor position
bool motorDir; // false is down, true is up

// DOOR SETUP
enum elvDoor {OPEN, HALF, CLOSED};
elvDoor door = CLOSED;

// LCD SETUP
const int rs = 41, en = 40, d4 = 37, d5 = 36, d6 = 35, d7 = 34;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
