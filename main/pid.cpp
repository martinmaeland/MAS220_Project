// **** PID FUNCTION ****

#include <arduino.h>
#include "motor.h"

void PID(double sp, Motor motor) {

  // Motor speed
  int speedMax = 50;

  // Gains
  double k_p = 100;
  double k_i = 0;
  double k_d = 0;

  // Variables
  double u_p, u_i, u_d;
  double error = 0; 
  double errorSum = 0;
  double errorPrev = 0;
  double u = 0;

  // Time variables
  double t, t0, dt;
  
  while (motor.getPos() != sp) {
    t = millis();
    dt = t - t0; // calculate change in time since last loop
    
    error = sp - motor.getPos();
    u_p = error*k_p; // proportional gain
    u_i = (errorSum + error*dt)*(1/k_i); // integral gain
    u_d = ((error-errorPrev)/dt)*k_d; // differential gain
    u = u_p + u_i + u_d;
    if (u > 100) {
      u = 100;
    } else if (u < 0){
      u = 0;
    }
    
    if (u > 0) {
      motor.up(u);
    } else if (u < 0) {
      motor.down(u);
    } else {
      motor.stop();
    }

    Serial.print("Position: ");
    Serial.print(motor.getPos());
    Serial.print(" | error: ");
    Serial.println(error); 
  
    t0 = t;
  }
}
