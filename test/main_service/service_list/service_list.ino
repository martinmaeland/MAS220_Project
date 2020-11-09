
enum elevator_state{WINDING, UNWINDING, STOPPED};
elevator_state elevator_state = STOPPED;

enum call_direction{UP, DOWN, NOTHING};
call_direction floor_state[] = {NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING};

bool service = false; //Checking if elevator is being serviced.

int current_floor = 0;

int queue[] = {0, 0, 0, 0, 0, 0, 0, 0};



void setup() {

  Serial.begin(9600);
}

void loop() {

  checkCustomers();
  
}

void interrUPtFunction(){
  if (joy = UP){
    floor_state[analogRead(potmeter)] = UP;
    wanted_floor = analogRead(potmeter);
  } else{
    floor_state[analogRead(potmeter)] = DOWN;
  }
}

void checkCustomers(){
  
  for (int i = 0; i < 8; i++){

    if (elevator_state == STOPPED){
      if (floor_state[i] != NOTHING){
        queue[0] = i;
        break;
      }
    }else if (elevator_state == WINDING){
      if (floor_state[i] == UP && current_floor < i){
        for (x = 0; x < 8; x++){
          if (queue[x] < 1){
            queue[x] = i;
            break;
          } 
        }  
       } 
      }else if (elevator_state == UNWINDING){
        if (floor_state[i] == DOWN && current_floor > i){
          for (x = 0; x < 8; x++){
              if (queue[x] < 1){
                queue[x] = i;
                break;
            }
        }
      }
    }
  }
}
