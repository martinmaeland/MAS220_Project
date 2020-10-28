// **** FUNCTIONS **** 

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
