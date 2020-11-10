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
  delay(step_delay); 
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(phaseA, LOW);
  digitalWrite(phaseB, HIGH);
  delay(step_delay); 
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(phaseA, HIGH);
  digitalWrite(phaseB, HIGH);
  delay(step_delay); 
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(phaseA, HIGH);
  digitalWrite(phaseB, LOW);
  delay(step_delay); 

  current_pos++;
}


void StepMotor::ccw(void) {
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(phaseA, HIGH);
  digitalWrite(phaseB, LOW);
  delay(step_delay);
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(phaseA, HIGH);
  digitalWrite(phaseB, HIGH);
  delay(step_delay);  
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(phaseA, LOW);
  digitalWrite(phaseB, HIGH);
  delay(step_delay); 
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH);
  digitalWrite(phaseA, LOW);
  digitalWrite(phaseB, LOW);
  delay(step_delay); 

  current_pos--;

}



void StepMotor::door(door_control control_door){
  if (control_door == OPENDOOR && current_pos < 50){
    cw();
  }
  else if(control_door == CLOSEDOOR && current_pos > 0){
    ccw();
  }
}



door_state StepMotor::state_of_door(void){
  if (current_pos == 50){
    return OPEN;
  }
  else if (current_pos == 0){
    return CLOSED;
  }
  else {
    return HALF;
  }
}
