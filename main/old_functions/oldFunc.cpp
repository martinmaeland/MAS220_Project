// **** OLD FUNCTIONS ****
// for backup purposes

// Function that moves elevator to new floor and updates current floor
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
