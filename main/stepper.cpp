// *** *Functions for stepmotor  ****

  #include "stepper.h"
  #include <arduino.h>

//Declaring stepmotor and inputs for stepmotor.   
StepMotor::StepMotor(void){
  pinMode(phaseA, OUTPUT); 
  pinMode(enableA, OUTPUT);
  pinMode(phaseB, OUTPUT);
  pinMode(enableB, OUTPUT);

  //Initializing DAC and setting 
  dac_init();
  //Allowing 1A per motor phase
  set_dac(4095,4095);
}

//Running the stepmotor clockwise when seeing "Servolab" from front. 
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

//Running the stepmotor counter-clockwise when seeing "Servolab" from front. 
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


//Opening and closing door.
//Had to use while loops instead of if statements because code was to slow...
void StepMotor::door(drControl controlDoor){
  while (controlDoor == OPENDOOR && currentPos < 50){
    cw();
  }
  while(controlDoor == CLOSEDOOR && currentPos > 0){
    ccw();
  }
}


//Returning state of the door.
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

//Returning a string of the state of the door (Using this to monitor the state).
String StepMotor::printStateOfDoor(void){
  if (currentPos == 50){
    return "OPEN";
  }
  else if (currentPos == 0){
    return "CLOSED";
  }
  else {
    return "HALF";
  }
}
