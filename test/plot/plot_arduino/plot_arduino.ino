#include "motor.h"
#include "pid.h"

<<<<<<< HEAD
Motor motor;

void funcA(){
  motor.encoderA();
}

void setup() {
  Serial.begin(115200);

  attachInterrupt(digitalPinToInterrupt(motor.encA), funcA, RISING);
=======
int x = 1;

void setup() {
  Serial.begin(115200);
>>>>>>> 2e2035a315bab1b2c04474f0884e4364172e93a0
  delay(1000);
}

void loop() {

<<<<<<< HEAD
  PID(360.0, motor);
=======
  delay(200);
  
  Serial.print(x);
  Serial.print(",");
  Serial.println(x*x);
  
  x++;    
>>>>>>> 2e2035a315bab1b2c04474f0884e4364172e93a0
   
}
