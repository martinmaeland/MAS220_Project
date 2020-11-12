
import processing.serial.*;

Serial myPort;

int x, y;
int xlast = 0;
int ylast = 360;

void setup() {
  
  size(640, 360);
  background(255);
  
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 152000);
  
}

void draw() {
  
  if (myPort.available() > 0) {
    String info = myPort.readString();
    String[] data = info.split(",");
    x = parseInt(data[0]);
    y = parseInt(data[1]);
  }
  
  point(x, y);
  line(xlast, ylast, x, y);
  
  xlast = x;
  ylast = y;
 
}
