
// Variables for time measuring
unsigned long t0, t, dt, t0_m, t_m, dt_m ; 

// Variables for velocity and position
double omega = 0; // angular velocity
double theta = 0; // angular position
double thetaSum = 0; // angular position sum for integral
int p_count = 1; // count pulses in time period

// DC motor encoder
int EncA = 21;
int EncB = 22;
int EncA_value, EncB_value;

// DC motor inputs
int dcMotor[3] = {5, 6, 7}; // Decay, Phase, Enable

// Buttons
int b1 = 22;
int b2 = 23;

void setup() {

  TCCR4B = TCCR4B & 0b11111000 | 0x01; // increase pwm frequency from 490 Hz to 32 kHz
  
  // INIT DC MOTOR PINMODES
  for (int i=0; i<3; i++)
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
  dt = t-t0; // calculate change in time since last loop
  
  if (digitalRead(b1) == 1) {
    digitalWrite(dcMotor[1], HIGH);
    analogWrite(dcMotor[2], 100);
  } else if (digitalRead(b2) == 1) {
    digitalWrite(dcMotor[1], LOW);
    analogWrite(dcMotor[2], 100);
  } else {
    analogWrite(dcMotor[2], 0);
  }

  // Find motor angular velocity
  EncA_value = digitalRead(EncA);
  t_m = millis();
  dt_m = (t_m - t0_m)*1000;
  if ((int)dt_m >= 2) {
    omega = (PI/8)*dt_m/p_count; // calculating angular velocity 
    t0_m = millis();
    p_count = 0;
  } else {
    if (EncA_value == 1) {
      p_count++;
    }
  }

  

  Serial.println(omega);
  t0 = t;
  
}


void PID(int k_p, int k_i, int k_d, double sp, double pos) {

  // Variables
  double error = 0; 
  double u_p = 0;
  double u_i = 0;
  double u_d = 0;
  double u = 0;
  double errorSum = 0;
  double errorPrev = 0;

  // Motor 
  digitalWrite(dcMotor[0], LOW);
  digitalWrite(dcMotor[1], HIGH);
  
  while (pos != sp) {
    error = sp - pos;
    u_p = error*k_p; // proportional gain
    u_i = (errorSum + error*dt)*k_i; // integral gain
    u_d = ((error-errorPrev)/dt)*k_d; // differential gain
    u = u_p + u_i + u_d;
    
    analogWrite(dcMotor[2], u); // make motor move
  }
  
}
