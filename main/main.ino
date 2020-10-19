// LIBRARIES
#include <LiquidCrystal.h>

// DEFINING PINS
int ledPin[] = {42, 43, 44, 45, 46, 47, 48, 49};
int buttonPin[] = {22, 23, 24, 25, 26, 27, 28, 29};
int dcMotor[3] = {5, 6, 7}; // Decay, Phase, Enable
int mechEncButton = 2;

// DECLARING GLOBAL VARIABLES
int currentFloor = 0;
int newFloor = 0;
int customerFloor = 0;
int joyDir = 0;
bool service = false;
bool* servicePnt = &service;

// DOOR SETUP
enum elvDoor {OPEN, HALF, CLOSED};
elvDoor door = CLOSED;

// LCD SETUP
const int rs = 41, en = 40, d4 = 37, d5 = 36, d6 = 35, d7 = 34;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  // INIT LEDS
  for (int i = 8; i > 0; i--){
    pinMode(ledPin[i-1], OUTPUT);
    }

  // INIT BUTTONS
  for (int i = 0; i < 8; i++){
    pinMode(buttonPin[i], INPUT);
    }

  // INIT DC MOTOR PINMODES
  for (int i=0; i<3; i++)
  {
    pinMode(dcMotor[i], OUTPUT);
  }
  
  // INIT ENCODER BUTTON
  pinMode(mechEncButton, INPUT);

  // INIT LCD
  pinMode(4, OUTPUT);
  analogWrite(4, 255);
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  lcd.print("Current floor ");
  lcd.print(currentFloor);
  
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

// FUNCTIONS

void moveElevator(int* currentFloor, int newFloor){
    Serial.print("Going to floor ");
    Serial.println(newFloor);
    digitalWrite(dcMotor[0], LOW);
    int elevatorSpeed = 1000; // ms from one floor to next
    int motorSpeed = 150;

    // SIMULATING ELEVATOR MOVING
    while (*currentFloor != newFloor) {
      if ( (newFloor - *currentFloor) > 0) {
        analogWrite(dcMotor[2], motorSpeed);
        digitalWrite(dcMotor[1], HIGH);
        delay(elevatorSpeed);
        *currentFloor = *currentFloor+1;
        analogWrite(dcMotor[2], 0);
        Serial.println("Winding");
        lcd.setCursor(14, 0);
        lcd.print(*currentFloor);
      } else if ( (newFloor - *currentFloor) < 0) {
        analogWrite(dcMotor[2], motorSpeed);
        digitalWrite(dcMotor[1], LOW);
        delay(elevatorSpeed);
        *currentFloor = *currentFloor - 1;
        analogWrite(dcMotor[2], 0);
        Serial.println("Unwinding");
        lcd.setCursor(14, 0);
        lcd.print(*currentFloor);
      }
    }

    Serial.print("Arrived at floor: ");
    Serial.println(*currentFloor);
}


void newFloorFunc(int* newFloorPnt){
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

void lcdPrint(String str, int* currentFloor) {
  
}
