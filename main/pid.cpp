// **** PID FUNCTION ****

#include <arduino.h>
#include "motor.h"

bool firstScan = true;
// Gains
double k_p = 0.5; // proportional gain
double k_i = 10; // integral gain
double k_d = 1; // derivative gain

// Variables
double u_p, u_i, u_d;
double error = 0; 
double errorSum = 0;
double errorPrev = 0;
double u = 0;
int maxSpeed = 150;
int minSpeed = 8;
double toleratedError = 0.4;

// Time variables
double t = 0;
double t0 = 0;
double dt = 0;
double sst = 0;

void initPid() {
  // Gains
  k_p = 0.5; // proportional gain
  k_i = 100; // integral gain
  k_d = 1; // derivative gain
  
  // Variables
  u_p, u_i, u_d;
  error = 0; 
  errorSum = 0;
  errorPrev = 0;
  u = 0;
  maxSpeed = 150;
  minSpeed = 8;
  toleratedError = 0.4;
  
  // Time variables
  t = 0;
  t0 = 0;
  dt = 0;
  sst = 0;
}

void PID(double sp, Motor& motor) {

  if (firstScan) {
    initPid();
    firstScan = false;
  }
  
  t = millis();
  dt = t - t0; // calculate change in time since last loop
  
  error = sp - motor.getPos();
  u_p = error*k_p; // proportional gain
  u_i = (errorSum + error*dt)*(1/k_i); // integral gain
  u_d = ((error-errorPrev)/dt)*k_d; // differential gain
  u = u_p + u_i; // u_d; 

  if (error >= toleratedError || error <= -toleratedError) {
    sst = millis();
  }

  if ( (millis()-sst) > 500) {
    motor.stop();
    firstScan = true;
  } else if (u > 0) {
    if (u > maxSpeed) {
      u = maxSpeed;
    } else if (u < minSpeed) {
      u = minSpeed;
    }
    motor.up(u);
  } else if (u < 0) {
    if (u < -maxSpeed) {
      u = maxSpeed;
    } else if (u > -minSpeed) {
      u = minSpeed;
    }
    motor.down(abs(u));
  }

  Serial.print("U: ");
  Serial.print(u);
  Serial.print("|  Position: ");
  Serial.print(motor.getPos());
  Serial.print(" | error: ");
  Serial.println(error);
  
  t0 = t;
}
