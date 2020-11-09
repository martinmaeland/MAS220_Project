
  #include "lift.h"
  #include <arduino.h>

  Lift::Lift(void){

  }

  void Lift::check_door_state(StepMotor& stepper){
    if (stepper.current_pos == 0){
      door_state = closed;
    }
    else if (stepper.current_pos == 50){
      door_state = open;
    }
    else {
      door_state = half;
    }
  }

  void Lift::door(StepMotor& stepper){
    check_door_state(stepper);
    if (door_state == closed){
      while (stepper.current_pos != 50){
        stepper.cw();
        door_state = half;
        Serial.println(door_state);
      }
      door_state = open;
    }
    else if (door_state == open){
      while (stepper.current_pos != 0){
        stepper.ccw();
        door_state = half;
        Serial.println(door_state);
      }
      door_state = closed;
    }
    Serial.println(door_state);
  }
  
