#include "screen.h"

Screen screen;

int currentFloor = 0;
int wantedFloor = 7;

void setup() {
  screen.begin();
}

void loop() {
  
  delay(1000);
  screen.clear();
  screen.showCurrentFloor(currentFloor);
  screen.showWantedFloor(wantedFloor);

  if (currentFloor < wantedFloor) {
     currentFloor++;
  } else {
    wantedFloor = 0;
  }

  if (currentFloor > wantedFloor) {
    currentFloor --;
  } else {
    wantedFloor = 7;
  }
  
}
