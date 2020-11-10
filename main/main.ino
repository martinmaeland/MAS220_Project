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

bool arrived = false;
int previousWantedFloor = 0;
bool servingCustomer = false;
int desiredFloor = 0;
int desiredFloorPos = 0;

void loop() {
  // Checking variables
  door_state doorState = stepper.state_of_door(); //Checking state of door. OPEN, HALF or CLOSED.
  stateOfServo servoState = servo.servoState; //Checking state of servo motor. WINDING, UNWINDING or STOPPED
  volatile int currentFloor = round(servo.getPos() / 360);
  
  int wantedFloor = checkCustomer();
  int travelToPos = wantedFloor*360;

  for (int i = 0; i < 8; i++){
    if (digitalRead(buttonPin[i]) == 1 && service == false){
      servingCustomer = true;
      desiredFloor = i;
      desiredFloorPos = i*360;
    }
  }
  
  if (servingCustomer == true){
    if (doorState == CLOSED){
      PID(desiredFloorPos, servo);
      servoState = servo.servoState;
      if (servoState == STOPPED){
        arrivalTime = millis();
        servingCustomer = false;
      }
    }
  }
    

  if (wantedFloor < 8 && wantedFloor >= 0 && service == true && servingCustomer == false) {
    if (doorState == CLOSED){
      PID(travelToPos, servo);
      servoState = servo.servoState;
      if (servoState == STOPPED){
        arrivalTime = millis();
        service = false;
      }
    } else if (doorState != CLOSED){
      Serial.println("Please close the door"); 
    }
  }
  
  if (service == false || servingCustomer == false){
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
  Serial.println(arrivalTime);
  Serial.print("  door state: ");
  Serial.println(doorState);


}
