#include "variables.h"
#include "functions.h"

void setup() {

  TCCR4B = TCCR4B & 0b11111000 | 0x01; // increase pwm frequency from 490 Hz to 32 kHz

  // INIT DC MOTOR PINMODES
  for (int i = 0; i < 3; i++)
  {
    pinMode(dcMotor[i], OUTPUT);
  }

  digitalWrite(dcMotor[0], LOW);

  // Dc motor encoder pinmodes
  pinMode(EncA, INPUT);
  pinMode(EncB, INPUT);

  // Button pinmodes
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);

  Serial.begin(9600);
}

void loop() {

  t = millis();
  dt = t - t0; // calculate change in time since last loop

  if (digitalRead(b1) == 1) {
    digitalWrite(dcMotor[1], HIGH);
    analogWrite(dcMotor[2], 100);
  } else if (digitalRead(b2) == 1) {
    digitalWrite(dcMotor[1], LOW);
    analogWrite(dcMotor[2], 100);
  } else {
    analogWrite(dcMotor[2], 0);
  }

  PID(1, 1, 1, 20, 10);

  t0 = t;
}
