
// DECLARING PINS
const int buttonPin[] = {22, 23, 24, 25, 26, 27, 28, 29}; // {0 ... 8}
const int dcMotor[3] = {5, 6, 7}; // Decay, Phase, Enable
const int encA = 21;
const int encB = 22; 

// DEFINE VARIABLES
double theta = 0;
int state = 0;

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

  state = digitalRead(encB);
}

void loop() {

  int a = digitalRead(encA);
  int b = digitalRead(encB);

  digitalWrite(dcMotor[0], LOW);
  digitalWrite(dcMotor[1], HIGH);
  analogWrite(dcMotor[2], 30);
  
  if (state == 1 && b == 0) {
    state = 0;
  } else if (state == 0 && b == 1) {
    theta = theta + 22.5;
    state = 1;
  }
  
  Serial.print("Theta: ");
  Serial.println(theta);

}
