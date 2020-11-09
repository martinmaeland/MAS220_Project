// **** Stepmotor class ****

#include <dac.h>

class StepMotor{
  private:
    const int enableA = 69;
    const int enableB = 67;
    const int phaseA = 68;
    const int phaseB = 66 ;
    const int step_delay = 15;
    
  public:
    int current_pos = 0;
    
    // Door setup
    enum move_door {still, opening, closing};
    move_door door = still;
    
    enum dr_state{CLOSED, OPEN, HALF};
    dr_state door_state = CLOSED;
  
    StepMotor();
    void cw(void);
    void ccw(void);
    void state_of_door(dr_state* door_state);
    void stepmotor(move_door* state_of_door);
  

};
  
  
