// **** Screen class ****

#include <arduino.h>

class Screen {
public:
  void begin(void);
  void clear(void);
  void showCurrentFloor(int& currentFloor);
  void showWantedFloor(int& wantedFloor);
  void closingDoor(void);
  void openingDoor(void);
  void promptFloor(void);
};
