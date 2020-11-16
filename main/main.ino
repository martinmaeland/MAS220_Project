/* 
 *  Project: MAS220 Elevator Project
 *  Authors: Jan-Henrik Skogstad, Martin Hermansen, Martin Mæland
 *  Date: Fall 2020
*/

// INCLUDES
#include "functions.h"
#include "motor.h"
#include "stepper.h"
#include "pid.h"
#include "screen.h"

// Create servo object
Motor servo;

// Create stepmotor object
StepMotor stepper;

// Create screen object
Screen screen;


void funcA(){
  servo.encoderA();
}

void setup() {
  //Init screen
  screen.begin();
  
  // Set pinmodes
  setPinModes();

  // Begin serial communication
  Serial.begin(9600);

  // INTERRUPT
  attachInterrupt(digitalPinToInterrupt(servo.encA), funcA, RISING);
  delay(1000);
  
}


void loop() {
  // Checking variables
  drState doorState = stepper.stateOfDoorFunc(); //Checking state of door. OPEN, HALF or CLOSED.
  stateOfServo servoState = servo.servoStateFunc(); //Checking state of servo motor. WINDING, UNWINDING or STOPPED.
  int currentFloor = round(servo.getPos() / 360); //Checking current floor of elevator.
  int wantedFloor = checkCustomer(); //Checking if someone calls elevator to a floor.
  int travelToPos = wantedFloor*360; //Checking the position of called floor. 

  //Screen prints
  screen.showCurrentFloor(currentFloor);

  //Checking if customer presses button inside elevator.
  for (int i = 0; i < 8; i++){
    if (digitalRead(buttonPin[i]) == 1 && service == false){
      servingCustomer = true;
      desiredFloor = i;
      desiredFloorPos = i*360;
    }
  }

  //If button inside elevator is pressed. Elevator will travel to desired floor and stop there if door is closed.
  //If the door is closed and direction is correct (direction cutomer decided when calling the floor) the elevator can travel.
  //If door is open or half, the door will close before traveling.
  //If direction is wrong. Nothing will happen. 
  if (servingCustomer == true){
    if (doorState == CLOSED){
      if (desiredFloor >= currentFloor && dirToGo == UP){
        PID(desiredFloorPos, servo);
        anotherCheckpoint = true;
        screen.showWantedFloor(desiredFloor);
      } else if(desiredFloor <= currentFloor && dirToGo == DOWN){
        PID(desiredFloorPos, servo);
        anotherCheckpoint = true;
        screen.showWantedFloor(desiredFloor);
      } 
      servoState = servo.servoStateFunc();
      if (servoState == STOPPED && anotherCheckpoint == true){
        arrivalTime = millis();
        servingCustomer = false;
        anotherCheckpoint = false;
      }
    } else if (doorState != CLOSED){
      screen.closingDoor();
      stepper.door(CLOSEDOOR);
    }
  }
    
  //If customer calls elevator to a floor this function will start.
  //Elevator must be called to floor 0-7. 
  //If elevator is allready running nothing will happen. 
  //Checking if door is closed, can't travel if door is open. If door is open. It will close.
  if (wantedFloor < 8 && wantedFloor >= 0 && service == true && servingCustomer == false && millis() - arrivalTime > 1000) {
    if (doorState == CLOSED){
      if (dirToGo != NOTHING){
        PID(travelToPos, servo);
        servoState = servo.servoStateFunc();
        if (servoState == STOPPED){
          arrivalTime = millis();
          anotherOneCheckPoint = true;
          service = false;
        }
      screen.showWantedFloor(wantedFloor);
      }
    } else if (doorState != CLOSED){
      screen.closingDoor();
      stepper.door(CLOSEDOOR);
    }
  }


  //If elevator reaches a floor from either of the functios above this function will start.
  //This function opens the door when elevator reaches the desired floor. 
  //Waits for 7 second, then closes. Can be closed earlier if button inside elevator is pressed.
  if (service == false && servingCustomer == false){
    if (doorState != OPEN && millis() - arrivalTime < 6999 && millis() - arrivalTime > 0){
      Serial.print("  Elevator state: ");
      Serial.print(servo.printServoStateFunc());
      Serial.print("   Door state: ");
      Serial.println("HALF");
      screen.openingDoor();
      stepper.door(OPENDOOR);
      if (anotherOneCheckPoint == true){
        screen.promptFloor();
        anotherOneCheckPoint = false;
      }
    } else if (doorState != CLOSED && millis() - arrivalTime > 7000){
      Serial.print("  Elevator state: ");
      Serial.print(servo.printServoStateFunc());
      Serial.print("   Door state: ");
      Serial.println("HALF");
      screen.closingDoor();
      stepper.door(CLOSEDOOR);
    }
  }


  //Prints door and elevator state.
  Serial.print("  Elevator state: ");
  Serial.print(servo.printServoStateFunc());
  Serial.print("   Door state: ");
  Serial.println(stepper.printStateOfDoor());

}
