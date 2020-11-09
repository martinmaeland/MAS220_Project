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

void StepMotor::go_to_pos(int new_pos){
   while (true){
    if (new_pos > current_pos){
      cw();
    }
    else if (new_pos < current_pos){
      ccw();
    }
    else if (new_pos == current_pos){
      break;
    }
    }
}

// Test if stepmotor can move to a position
void StepMotor::move_door(void){ 
  if (current_pos <= 50 && door_state == false){
    cw();
  }
  else if (current_pos  > 0){
    ccw();  
  }
  if (current_pos == 0){
    door_state = true;
  }
  else if(current_pos > 0){
    door_state = false;
  }
}
