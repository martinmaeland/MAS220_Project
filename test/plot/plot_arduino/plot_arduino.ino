
int x = 1;

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {

  delay(200);
  
  Serial.print(x);
  Serial.print(",");
  Serial.println(x*x);
  
  x++;    
   
}
