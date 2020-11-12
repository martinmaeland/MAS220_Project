
uint8_t x = 1;
String data;
String test = "0,1";

void setup() {
  Serial.begin(152000);
  delay(1000);
}

void loop() {

  delay(1000);

  data = String(x);
  data += String(",");
  data += String(1/x);
  
  Serial.print(data);
  
  x++;    
   
}
