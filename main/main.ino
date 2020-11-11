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

// Create servo object
Motor servo;

// Create stepmotor object
StepMotor stepper;


void funcA(){
  servo.encoderA();
}

void setup() {
  
  // Set pinmodes
  setPinModes();

  // Begin serial communication
  Serial.begin(9600);

  // INTERRUPT
  attachInterrupt(digitalPinToInterrupt(servo.encA), funcA, RISING);
  delay(1000);
  
}

bool anotherCheckpoint = false;

void loop() {
  // Checking variables
  drState doorState = stepper.stateOfDoorFunc(); //Checking state of door. OPEN, HALF or CLOSED.
  stateOfServo servoState = servo.servoStateFunc(); //Checking state of servo motor. WINDING, UNWINDING or STOPPED.
  volatile int currentFloor = round(servo.getPos() / 360); //Checking current floor of elevator.
  int wantedFloor = checkCustomer(); //Checking if someone calls elevator to a floor.
  int travelToPos = wantedFloor*360; //Checking the position of called floor. 

  for (int i = 0; i < 8; i++){
    if (digitalRead(buttonPin[i]) == 1 && service == false){
      servingCustomer = true;
      desiredFloor = i;
      desiredFloorPos = i*360;
    }
  }
  
  if (servingCustomer == true){
    if (doorState == CLOSED){
      if (desiredFloor >= currentFloor && dirToGo != DOWN){
        PID(desiredFloorPos, servo);
        anotherCheckpoint = true;
      } else if(desiredFloor <= currentFloor && dirToGo != UP){
        PID(desiredFloorPos, servo);
        anotherCheckpoint = true;
      } 
      servoState = servo.servoStateFunc();
      if (servoState == STOPPED && anotherCheckpoint == true){
        arrivalTime = millis();
        servingCustomer = false;
        anotherCheckpoint = false;
      }
    } else if (doorState != CLOSED){
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
          service = false;
          dirToGo = NOTHING;
        }
      }
    } else if (doorState != CLOSED){
      stepper.door(CLOSEDOOR);
    }
  }
  
  if (service == false && servingCustomer == false){
    if (doorState != OPEN && millis() - arrivalTime < 6999 && millis() - arrivalTime > 0){
      stepper.door(OPENDOOR);
    } else if (doorState != CLOSED && millis() - arrivalTime > 7000){
      stepper.door(CLOSEDOOR);
    }
  }


  
  Serial.print("currentFloor: ");
  Serial.print(currentFloor);
  Serial.print("  servo state: ");
  Serial.print(servoState);
  Serial.print("  arrival time: ");
  Serial.print(arrivalTime);
  Serial.print("  door state: ");
  Serial.print(doorState);
  Serial.print("  joyDir: ");
  Serial.print(joyDir);
  Serial.print("  service: ");
  Serial.println(service);



}
