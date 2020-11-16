// **** Defining PID ****

#include <arduino.h>

// Bool for first scan
bool firstScan = true;

// Gains
double k_p = 0.5; // proportional gain
double k_i = 50; // integral gain
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


// This function resets variables for next job
void initPid() {
  // Gains
  double k_p = 0.5; // proportional gain
  double k_i = 50; // integral gain
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
}

void PID(double sp, Motor& motor) {

  // This only once, resetting all variables
  if (firstScan) {
    initPid();
    firstScan = false;
  }

  // Part 1: Calculating dt and error
  t = millis();
  dt = t - t0; // calculate change in time since last loop
  error = sp - motor.getPos();

  // Part 2: Calculating output
  u_p = error*k_p; // proportional gain
  u_i = (errorSum + error*dt)*(1/k_i); // integral gain
  u_d = ((error-errorPrev)/dt)*k_d; // differential gain
  u = u_p + u_i; // u_d;

  // Part 3: Logic to drive motor and stop
  if (error >= toleratedError || error <= -toleratedError) {
    sst = millis();
  }

  if ( (millis()-sst) > 500) {
    motor.stop();
    firstScan = true;
    u = 0;
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

  // Some serial outputs for easier tuning
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
