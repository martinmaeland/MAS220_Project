// **** Stepmotor class ****

#include <dac.h>

 enum drControl{OPENDOOR, CLOSEDOOR}; //Creating a enum to control the door
 enum drState{CLOSED, OPEN, HALF};    //Creating a enum to monitor state of door.

 class StepMotor{
  private:
    //Pins to controll servomotor.
    const int enableA = 69;
    const int enableB = 67;
    const int phaseA = 68;
    const int phaseB = 66 ;
    const int stepDelay = 15;

  public:
    int currentPos = 0;
    drControl controlDoor;

  
    StepMotor();
    void cw(void);
    void ccw(void);
    drState stateOfDoorFunc(void);
    void door(drControl controlDoor);
    String printStateOfDoor(void);

};
  
  
