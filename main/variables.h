// **** DEFINING VARIABLES ****

#include "arduino.h"
#include <LiquidCrystal.h>

// Pins
const int ledPin[] = {42, 43, 44, 45, 46, 47, 48, 49};
const int buttonPin[] = {22, 23, 24, 25, 26, 27, 28, 29}; // {0 ... 8}
const int mechEncButton = 2;

// Floor variables
int currentFloor = 0;
int newFloor = 0;
int customerFloor = 0;
bool service = false; // elevator service state
bool* servicePnt = &service;

// Motor variables
volatile double theta = 0.0; // DC motor position
//bool motorDir; // false is down, true is up

// Door setup
enum elvDoor {OPEN, HALF, CLOSED};
elvDoor door = CLOSED;

// Lcd setup
const int rs = 41, en = 40, d4 = 37, d5 = 36, d6 = 35, d7 = 34;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
