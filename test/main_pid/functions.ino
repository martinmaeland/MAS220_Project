// **** FUNCTIONS **** 

void PID(double sp, ) {

  // Gains
  double u_p = 1;
  double u_i = 1;
  double u_d = 1;

  // Variables
  double error = 0; 
  double errorSum = 0;
  double errorPrev = 0;
  double u = 0;

  // Motor 
  digitalWrite(dcMotor[0], LOW);
  digitalWrite(dcMotor[1], HIGH);
  
  while (pos != sp) {
    t = millis();
    dt = t - t0; // calculate change in time since last loop
    
    error = sp - pos;
    u_p = error*k_p; // proportional gain
    u_i = (errorSum + error*dt)*(1/k_i); // integral gain
    u_d = ((error-errorPrev)/dt)*k_d; // differential gain
    u = u_p + u_i + u_d;
    analogWrite(dcMotor[2], u); // make motor move

    t0 = t;
  }  
}
