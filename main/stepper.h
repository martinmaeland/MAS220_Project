// **** Stepmotor class ****

#include <dac.h>

 enum door_control{OPENDOOR, CLOSEDOOR};
 enum door_state{CLOSED, OPEN, HALF};

 class StepMotor{
  private:
    const int enableA = 69;
    const int enableB = 67;
    const int phaseA = 68;
    const int phaseB = 66 ;
    const int step_delay = 15;

  public:
    int current_pos = 0;
    door_control control_door;

  
    StepMotor();
    void cw(void);
    void ccw(void);

    door_state state_of_door(void);
    void door(door_control control_door);

};
  
  
