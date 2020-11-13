#include "motor.h"
#include "pid.h"

Motor motor;

void funcA(){
  motor.encoderA();
}

void setup() {
  Serial.begin(115200);

  attachInterrupt(digitalPinToInterrupt(motor.encA), funcA, RISING);
  delay(1000);
}

void loop() {

  PID(360.0, motor);
   
}
