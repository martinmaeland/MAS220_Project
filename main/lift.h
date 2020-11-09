#include "stepper.h"
#include "motor.h"

class Lift {
  private:
  enum dr_state{closed, open, half};
  dr_state door_state = closed;
    
  public:
  
  

  Lift();
  void check_door_state(StepMotor& stepper);
  void door(StepMotor& stepper);

};
