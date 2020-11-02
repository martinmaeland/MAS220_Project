/* 
 *  Project: MAS220 Elevator Project
 *  Authors: Jan-Henrik Skogstad, Martin Hermansen, Martin Mæland
 *  Date: Fall 2020
*/

// INCLUDES
#include "variables.h"
#include "functions.h"
#include "motor.h"

// Create motor
Motor motor;

// Functions
void PID(double sp, Motor motor);

void funcA() {
  motor.encoderA();
}

void setup() {

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
  lcd.print("Current floor ");
  lcd.print(currentFloor);

  // Begin serial communication
  Serial.begin(9600);

  // INTERRUPT
  attachInterrupt(digitalPinToInterrupt(motor.encA), funcA, RISING);
}


void loop() {

  // READING VALUES
  int potmeter = map(analogRead(A0), 0, 1000, 0, 7);
  int joyDir = joyDirection(analogRead(A2));

  // CHOOSING CURRENT FLOOR LED
  for (int i = 8; i > 0; i--){
     digitalWrite(ledPin[i-1], 0);
  }
  digitalWrite(ledPin[potmeter], 1);

  // STARTING SERVICE
  if (joyDir != 0){
    customerFloor = 7-potmeter;
    service = true;
  }

  // TEST CODE

  while (true) {
    PID(50, motor);
  }

  /*
  while(true){
    if (digitalRead(buttonPin[0]) == true) {
      motor.up(10);
    } else if (digitalRead(buttonPin[1]) == true){
      motor.down(10);
    } else {
      motor.stop();
    }
  
    Serial.println(motor.getPos());
  }
  */
}
