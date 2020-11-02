// **** DEFINING FUNCTIONS ****

#include <arduino.h>

int joyDirection(double joyRead) {
  if (joyRead <= 350){
    return -1;
    }
  else if (joyRead >= 640){
    return 1;
    }
  else{
    return 0;
  }
}


// Function that awaits new floor input
void newFloorFunc(int* newFloorPnt, const int buttonPin[]){
  int chosenFloor = 100;
  Serial.println("What floor do you desire?");
  while (chosenFloor == 100) {
    for (int i = 0; i <= 7; i++){
      if (digitalRead(buttonPin[i]) == 1){
        chosenFloor = i;
      }
    }
  }
  *newFloorPnt = chosenFloor;
}
