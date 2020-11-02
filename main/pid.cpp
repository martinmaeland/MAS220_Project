// **** PID FUNCTION ****

#include <arduino.h>
#include "motor.h"

// Gains
double k_p = 10;
double k_i = 1;
double k_d = 0;

// Variables
double u_p, u_i, u_d;
double error = 0; 
double errorSum = 0;
double errorPrev = 0;
double u = 0;

// Time variables
double t = 0;
double t0 = 0;
double dt = 0;

void PID(double sp, Motor motor) {
  
  t = millis();
  dt = t - t0; // calculate change in time since last loop
  
  error = sp - motor.getPos();
  u_p = error*k_p; // proportional gain
  u_i = (errorSum + error*dt)*(1/k_i); // integral gain
  u_d = ((error-errorPrev)/dt)*k_d; // differential gain
  u = u_p; //u_i + u_d;
  
  if (u > 10) {
    u = 10;
  } else if (u < -10) {
    u = -10;
  }

  if (u > 0) {
    motor.up(u);
    motor.dir = true;
  } else if (u < 0) {
    motor.down(abs(u));
    motor.dir = false; 
  } else {
    motor.stop();
  }

  /*
  Serial.print("U: ");
  Serial.print(u);
  Serial.print("|  Position: ");
  Serial.print(motor.getPos());
  Serial.print(" | error: ");
  Serial.println(error);
  */
  t0 = t;
}
