/* 
 *  Project: MAS220 Elevator Project
 *  Authors: Jan-Henrik Skogstad, Martin Hermansen, Martin Mæland
 *  Date: Fall 2020
*/

// INCLUDES
#include "variables.h"
#include "functions.h"

void setup() {

  // DEFINE LEDS
  for (int i = 8; i > 0; i--){
    pinMode(ledPin[i-1], OUTPUT);
  }

  // DEFINE BUTTONS
  for (int i = 0; i < 8; i++){
    pinMode(buttonPin[i], INPUT);
  }

  // DEFINE DC MOTOR PINMODES
  for (int i=0; i<3; i++) {
    pinMode(dcMotor[i], OUTPUT);
  }
  
  // DEFINE ENCODER BUTTON
  pinMode(mechEncButton, INPUT);

  // DEFINE LCD
  pinMode(4, OUTPUT);
  analogWrite(4, 255);
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  lcd.print("Current floor ");
  lcd.print(currentFloor);

  // Begin serial communication
  Serial.begin(9600);
}


void loop() {

  // READING VALUES
  int potmeter = map(analogRead(A0), 0, 1000, 0, 7);
  int joystickY = analogRead(A2);

  // JOYSTICK MAPPING
  if (joystickY <= 350){
    joyDir = -1;
    }
  else if (joystickY >= 640){
    joyDir = 1;
    }
  else{
    joyDir = 0;
  }

  // CHOOSING CURRENT FLOOR LED
  for (int i = 8; i > 0; i--){
     digitalWrite(ledPin[i-1], 0);
  }
  digitalWrite(ledPin[potmeter], 1);


  // STARTING SERVICE
  if (joyDir != 0){
    customerFloor = 7-potmeter;
    service = true;
  }

  if (service == true){
    moveElevator(&currentFloor, customerFloor);
    lcd.setCursor(0,1);
    lcd.print("Choose floor");
    
    newFloorFunc(&newFloor);
    lcd.setCursor(0,1);
    lcd.print("Going to ");
    lcd.print(newFloor);
    
    moveElevator(&currentFloor, newFloor);
    lcd.setCursor(0,1);
    lcd.print("Arrived");
    delay(3000);
    lcd.setCursor(0,1);
    lcd.print("");

    service = false;
    }   
}
