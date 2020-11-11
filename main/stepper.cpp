  //FUNCTIONS FOR STEPPER 

  #include "stepper.h"
  #include <arduino.h>
  
StepMotor::StepMotor(void){
  pinMode(phaseA, OUTPUT); 
  pinMode(enableA, OUTPUT);
  pinMode(phaseB, OUTPUT);
  pinMode(enableB, OUTPUT);

  dac_init();
  set_dac(4095,4095);
}

void  StepMotor::cw(void){ 
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(phaseA, LOW);
  digitalWrite(phaseB, LOW);
  delay(stepDelay); 
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(phaseA, LOW);
  digitalWrite(phaseB, HIGH);
  delay(stepDelay); 
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(phaseA, HIGH);
  digitalWrite(phaseB, HIGH);
  delay(stepDelay); 
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(phaseA, HIGH);
  digitalWrite(phaseB, LOW);
  delay(stepDelay); 

  currentPos++;
}


void StepMotor::ccw(void) {
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(phaseA, HIGH);
  digitalWrite(phaseB, LOW);
  delay(stepDelay);
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(phaseA, HIGH);
  digitalWrite(phaseB, HIGH);
  delay(stepDelay);  
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(phaseA, LOW);
  digitalWrite(phaseB, HIGH);
  delay(stepDelay); 
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(phaseA, LOW);
  digitalWrite(phaseB, LOW);
  delay(stepDelay); 

  currentPos--;

}



void StepMotor::door(drControl controlDoor){
  while (controlDoor == OPENDOOR && currentPos < 50){
    cw();
  }
  while(controlDoor == CLOSEDOOR && currentPos > 0){
    ccw();
  }
}



drState StepMotor::stateOfDoorFunc(void){
  if (currentPos == 50){
    return OPEN;
  }
  else if (currentPos == 0){
    return CLOSED;
  }
  else {
    return HALF;
  }
}
