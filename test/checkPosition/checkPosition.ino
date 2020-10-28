
// DECLARING PINS
const int buttonPin[] = {22, 23, 24, 25, 26, 27, 28, 29}; // {0 ... 8}
const int dcMotor[3] = {5, 6, 7}; // Decay, Phase, Enable
const int encA = 20;
const int encB = 21; 

// DEFINE VARIABLES
volatile double theta = 0.0;
bool motorDir; // false is down, true is up

void setup() {

  // INIT BUTTONS
  for (int i = 0; i < 8; i++){
    pinMode(buttonPin[i], INPUT);
    }

    // INIT DC MOTOR PINMODES
  for (int i=0; i<3; i++)
  {
    pinMode(dcMotor[i], OUTPUT);
  }

  pinMode(encA, INPUT);
  pinMode(encB, INPUT);

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(encA), encA_func, RISING);
  attachInterrupt(digitalPinToInterrupt(encB), encB_func, RISING);

}

void loop() {

  int a = digitalRead(encA);
  int b = digitalRead(encB);
  int btnUpPressed = digitalRead(buttonPin[0]);
  int btnDownPressed = digitalRead(buttonPin[7]);

  digitalWrite(dcMotor[0], LOW);
  
  if (btnUpPressed == 1) {
    motorDir = true;
    digitalWrite(dcMotor[1], HIGH);
    analogWrite(dcMotor[2], 50);
  } else if (btnDownPressed == 1) {
    motorDir = false;
    digitalWrite(dcMotor[1], LOW);
    analogWrite(dcMotor[2], 50);
  } else {
    analogWrite(dcMotor[2], 0);
  }
  
  Serial.print("Theta: ");
  Serial.println(theta);

}


void encA_func(){
  if (motorDir == true) {
    theta += (22.5/131.0);
  } else if (motorDir == false) {
    theta -= (22.5/131.0);
  }
}
void encB_func() {
  // something else
}
