// **** Stepmotor class ****

<<<<<<< HEAD
#include <dac.h>

class StepMotor{
=======
  #include <dac.h>


 enum door_control{still, opening, closing};
 enum door_state{closed, open, half};

 class StepMotor{
>>>>>>> b0284df41291816936708b7c1b10a5dc936ffe6a
  private:
    const int enableA = 69;
    const int enableB = 67;
    const int phaseA = 68;
    const int phaseB = 66 ;
    const int step_delay = 15;

  public:
    int current_pos = 0;
    door_control control_door;
    door_state state_door;

  
    StepMotor();
    void cw(void);
    void ccw(void);
<<<<<<< HEAD
    void state_of_door(dr_state* door_state);
    void stepmotor(move_door* state_of_door);
=======
    void state_of_door(door_state state_door);
    void stepmotor(door_control control_door);
>>>>>>> b0284df41291816936708b7c1b10a5dc936ffe6a
  

};
  
  
