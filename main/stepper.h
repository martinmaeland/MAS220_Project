
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
  
  StepMotor();
  void cw(void);
  void ccw(void);
  void go_to_pos(int new_pos);

};
  
  
