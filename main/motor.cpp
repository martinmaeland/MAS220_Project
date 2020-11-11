// **** Functions for motor class ****

#include <arduino.h>
#include "motor.h"

Motor::Motor(void) {
  for (int i=0; i<3; i++) {
    pinMode(dcMotor[i], OUTPUT);
  }
  pinMode(encA, INPUT);
}

void Motor::up(double spd) {
  dir = 1;
  servoState = WINDING;
  digitalWrite(dcMotor[0], LOW);
  digitalWrite(dcMotor[1], HIGH);
  analogWrite(dcMotor[2], spd);
  //Serial.println("GOING UP");
}

void Motor::down(double spd) {
  dir = -1;
  digitalWrite(dcMotor[0], LOW);
  digitalWrite(dcMotor[1], LOW);
  analogWrite(dcMotor[2], spd);
}

void Motor::stop(void) {
  dir = 0;
  servoState = STOPPED;
  digitalWrite(dcMotor[0], LOW);
  digitalWrite(dcMotor[1], HIGH);
  analogWrite(dcMotor[2], 0);
}

double Motor::getPos(void) {
  return pos;
}

stateOfServo Motor::servoStateFunc(void){
  if (dir == -1){
    return UNWINDING;
  } else if (dir == 1){
    return WINDING;
  } else if (dir == 0){
    return STOPPED;
  }
}

void Motor::printPos(void) {
  Serial.println(pos);
}

void Motor::encoderA(void){
  if (dir == 1) {
    pos += (22.5/131.0);
  } else if (dir == -1) {
    pos -= (22.5/131.0);
  }
}

void Motor::encoderB(void) {
  // test
}
