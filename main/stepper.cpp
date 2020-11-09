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



void StepMotor::stepmotor(door_control control_door){
  if (control_door == opening && current_pos < 50){
    cw();
    if (current_pos == 50){
      control_door = still;
    }
  }
  else if(control_door == closing && current_pos > 0){
    ccw();
    if (current_pos == 0){
       control_door = still;
    }
  }
}



void StepMotor::state_of_door(door_state state_door){
  if (current_pos == 50){
    state_door = open;
  }
  else if (current_pos == 0){
    state_door = closed;
  }
  else {
    state_door = half;
  }
}
