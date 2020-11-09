/* 
 *  Project: MAS220 Elevator Project
 *  Authors: Jan-Henrik Skogstad, Martin Hermansen, Martin Mæland
 *  Date: Fall 2020
*/

// INCLUDES
#include "functions.h"
#include "motor.h"
#include "pid.h"
#include "stepper.h"

// Create servo object
Motor motor;

// Create stepmotor
StepMotor stepper;


void funcA(){
  motor.encoderA();
}

void setup() {
  
  // Set pinmodes
  setPinModes();

  // Begin serial communication
  Serial.begin(9600);

  // INTERRUPT
  attachInterrupt(digitalPinToInterrupt(motor.encA), funcA, RISING);
  delay(1000);
}


void loop() {

  // queueUp = []
  // queueDown = []

  int potmeter = 360;

  /*
  checkCustomers();

  if (queueDown.length() > 1) {
      
  } 
  */
  

  
  
  if (digitalRead(buttonPin[0]) == 1){
    stepper.control_door = opening;
    stepper.stepmotor(stepper.control_door);
  }
  else if (digitalRead(buttonPin[1]) == 1){
    stepper.control_door = closing;
    stepper.stepmotor(stepper.control_door); 
  }

 
  
  
}
