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

bool anotherOneCheckPoint = false;

void loop() {
  // Checking variables
  drState doorState = stepper.stateOfDoorFunc(); //Checking state of door. OPEN, HALF or CLOSED.
  stateOfServo servoState = servo.servoStateFunc(); //Checking state of servo motor. WINDING, UNWINDING or STOPPED.
  int currentFloor = round(servo.getPos() / 360); //Checking current floor of elevator.
  int wantedFloor = checkCustomer(); //Checking if someone calls elevator to a floor.
  int travelToPos = wantedFloor*360; //Checking the position of called floor. 

  //Screen prints
  //screen.clear();
  screen.showCurrentFloor(currentFloor);


  for (int i = 0; i < 8; i++){
    if (digitalRead(buttonPin[i]) == 1 && service == false){
      servingCustomer = true;
      desiredFloor = i;
      desiredFloorPos = i*360;
    }
  }
  
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



  Serial.print("  Elevator state: ");
  Serial.print(servo.printServoStateFunc());
  Serial.print("   Door state: ");
  Serial.println(stepper.printStateOfDoor());

}
