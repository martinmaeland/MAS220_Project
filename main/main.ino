/* 
 *  Project: MAS220 Elevator Project
 *  Authors: Jan-Henrik Skogstad, Martin Hermansen, Martin Mæland
 *  Date: Fall 2020
*/

// INCLUDES
#include "functions.h"
#include "motor.h"
#include "stepper.h"
#include "pid.h"

// Create servo object
Motor servo;

// Create stepmotor object
StepMotor stepper;

void funcA(){
  servo.encoderA();
}

void setup() {
  
  // Set pinmodes
  setPinModes();

  // Begin serial communication
  Serial.begin(9600);

  // INTERRUPT
  attachInterrupt(digitalPinToInterrupt(servo.encA), funcA, RISING);
  delay(1000);
}


void loop() {

}
