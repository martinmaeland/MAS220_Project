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

// Create stepmotor
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
  
  // test
  int potmeter = map(analogRead(A0), 0, 1000, 0, 7);
  PID(potmeter*50, servo);
  
  if (digitalRead(buttonPin[0]) == 1){
    stepper.control_door = opening;
    stepper.stepmotor(stepper.control_door);
  }
  else if (digitalRead(buttonPin[1]) == 1){
    stepper.control_door = closing;
    stepper.stepmotor(stepper.control_door); 
  }

}
