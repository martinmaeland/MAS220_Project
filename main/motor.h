// **** Servo class ****

#include <arduino.h>

enum stateOfServo{WINDING, UNWINDING, STOPPED};

class Motor {

  private:
  const int dcMotor[3] = {5, 6, 7}; // Decay, Phase, Enable

  public:
  const int encA = 20; // motor encoder a
  volatile double pos = 0; // position in degrees
  int dir = 0; // true is up, false is down
  stateOfServo servoState = STOPPED;

  Motor();
  void up(double); // speed input
  void down(double); // speed input
  void stop(void);
  double getPos(void);
  stateOfServo servoStateFunc(void);
  String printServoStateFunc(void);
  void printPos(void);
  void encoderA(void);
  void encoderB(void);
};
