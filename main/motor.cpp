// **** Functions for motor class ****

#include <arduino.h>
#include "motor.h"

// Define pinmodes for motor on object creation
Motor::Motor(void) {
  for (int i=0; i<3; i++) {
    pinMode(dcMotor[i], OUTPUT);
  }
  pinMode(encA, INPUT);
}

// Drive motor up (cw) with given speed
void Motor::up(double spd) {
  dir = 1;
  servoState = WINDING;
  digitalWrite(dcMotor[0], LOW);
  digitalWrite(dcMotor[1], HIGH);
  analogWrite(dcMotor[2], spd);
  //Serial.println("GOING UP");
}

// Drive motor down (ccw) with given speed
void Motor::down(double spd) {
  dir = -1;
  digitalWrite(dcMotor[0], LOW);
  digitalWrite(dcMotor[1], LOW);
  analogWrite(dcMotor[2], spd);
}

// Stop motor
void Motor::stop(void) {
  dir = 0;
  servoState = STOPPED;
  digitalWrite(dcMotor[0], LOW);
  digitalWrite(dcMotor[1], HIGH);
  analogWrite(dcMotor[2], 0);
}

// Return motor position
double Motor::getPos(void) {
  return pos;
}

// Return state of motor
stateOfServo Motor::servoStateFunc(void){
  if (dir == -1){
    return UNWINDING;
  } else if (dir == 1){
    return WINDING;
  } else if (dir == 0){
    return STOPPED;
  }
}

// Print state of motor
String Motor::printServoStateFunc(void){
  if (dir == -1){
    return "UNWINDING";
  } else if (dir == 1){
    return "WINDING";
  } else if (dir == 0){
    return "STOPPED";
  }
}

// Print position of motor
void Motor::printPos(void) {
  Serial.println(pos);
}

// Interrupt function to register position
void Motor::encoderA(void){
  if (dir == 1) {
    pos += (22.5/131.0);
  } else if (dir == -1) {
    pos -= (22.5/131.0);
  }
}
