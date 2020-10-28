// **** VARIABLES HEADER FILE ****

// Variables for time measuring
unsigned long t0, t, dt, t0_m, t_m, dt_m ;

// Variables for velocity and position
double omega = 0; // angular velocity
double theta = 0; // angular position
double thetaSum = 0; // angular position sum for integral
int p_count = 1; // count pulses in time period

// DC motor encoder
int EncA = 20;
int EncB = 21;
int EncA_value, EncB_value;

// DC motor inputs
int dcMotor[3] = {5, 6, 7}; // Decay, Phase, Enable

// Buttons
int b1 = 22;
int b2 = 23;
