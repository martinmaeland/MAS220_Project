// **** MOTOR FUNCTIONS ****

#include <arduino.h>

class Motor {

  private:
  const int dcMotor[3] = {5, 6, 7}; // Decay, Phase, Enable

  public:
  volatile double pos = 0; // position in degrees
  bool dir; // true is up, false is down
  Motor();
  void up(double); // speed input
  void down(double); // speed input
  void stop(void);
  double getPos(void);
  void printPos();
  
};
