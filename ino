// 28byj-uln2003 stepper test 

int pins[4] = {2,3,4,5}; // uno pins 2,3,4,5 connected to in1, in2, in3, in4 uln2003 board pins

int step_delay = 2000;  // delayMicroseconds(n);
int step_delay8 = 1000;

int seqN = -1;

void setup() {

  for (int pin=0; pin<4; pin++){
    pinMode(pins[pin], OUTPUT);
  }
  
  Serial.begin(9600); // set up Serial library at 9600 
  delay(1000);
  Serial.println("28byj/uln2003 Stepper Step Test");
}
void loop() {
  
  int i;
  
  Serial.println("Stepping 4096 Half Steps Forward");
  for (i=0; i<4096; i++){
    step8(1);
  }
  delay(2000);
  Serial.println("Stepping 4096 Half Steps Backward");
  for (i=0; i<4096; i++){
    step8(-1);
  }
  delay(2000);
  
  Serial.println("Stepping 2048 Full Steps Forward");
  for (i=0; i<2048; i++){
    step(1);
  }
  delay(2000);
  Serial.println("Stepping 2048 Full Steps Backward");
  for (i=0; i<2048; i++){
    step(-1);
  }
  delay(2000);
  
}

void step(int clockwise){
  if (clockwise > 0) seqCW();
  else seqCCW();
}

void seqCW (){
  seqN++;
  if (seqN > 3) seqN = 0; // roll over to 1-4 seq
  seq(seqN);
}

void seqCCW (){
  seqN--;
  if (seqN < 0) seqN = 3; // roll over to 4-1 seq
  seq(seqN);
}

void seq (int seqNum){

  int pattern[4];
  // HIGH/LOW pattern to write to driver board
  
  switch(seqNum){
    case 0:
    {
      pattern[0] = 1;
      pattern[1] = 1;
      pattern[2] = 0;
      pattern[3] = 0;
      break;
    }
    case 1:
    {
      pattern[0] = 0;
      pattern[1] = 1;
      pattern[2] = 1;
      pattern[3] = 0;
      break;
    }
    case 2:
    {
      pattern[0] = 0;
      pattern[1] = 0;
      pattern[2] = 1;
      pattern[3] = 1;
      break;
    }
    case 3:
    {
      pattern[0] = 1;
      pattern[1] = 0;
      pattern[2] = 0;
      pattern[3] = 1;
      break;
    }
    default:
    {
      pattern[0] = 0;
      pattern[1] = 0;
      pattern[2] = 0;
      pattern[3] = 0;
      break;
    }
  }

  // write pattern to pins
  for (int p=0; p<4; p++){
    digitalWrite(pins[p], pattern[p]);
  }
  delayMicroseconds(step_delay);
}

void step8(int clockwise){
  if (clockwise > 0) seqCW8();
  else seqCCW8();
}

void seqCW8 (){
  seqN++;
  if (seqN > 7) seqN = 0; // roll over to 1-8 seq
  seq8(seqN);
}

void seqCCW8 (){
  seqN--;
  if (seqN < 0) seqN = 7; // roll over to 8-1 seq
  seq8(seqN);
}

void seq8 (int seqNum){

  int pattern[4];
  // HIGH/LOW pattern to write to driver board
  
  switch(seqNum){
    case 0:
    {
      pattern[0] = 1;
      pattern[1] = 0;
      pattern[2] = 0;
      pattern[3] = 0;
      break;
    }
    case 1: 
    {
      pattern[0] = 1; // 0
      pattern[1] = 1;
      pattern[2] = 0;
      pattern[3] = 0;
      break;
    }
    case 2:
    {
      pattern[0] = 0;
      pattern[1] = 1;
      pattern[2] = 0;
      pattern[3] = 0;
      break;
    }
    case 3:
    {
      pattern[0] = 0; // 1
      pattern[1] = 1;
      pattern[2] = 0;
      pattern[3] = 1;
      break;
    } 
    case 4:
    {
      pattern[0] = 0;
      pattern[1] = 0;
      pattern[2] = 1;
      pattern[3] = 0;
      break;
    }
    case 5:
    {
      pattern[0] = 0; // 2
      pattern[1] = 0;
      pattern[2] = 1;
      pattern[3] = 1;
      break;
    }
    case 6:
    {
      pattern[0] = 0;
      pattern[1] = 0;
      pattern[2] = 0;
      pattern[3] = 1;
      break;
    }
    case 7:
    {
      pattern[0] = 1; // 3
      pattern[1] = 0;
      pattern[2] = 1;
      pattern[3] = 0;
      break;
    }
    default:
    {
      pattern[0] = 0;
      pattern[1] = 0;
      pattern[2] = 0;
      pattern[3] = 0;
      break;
    }
  }

  // write pattern to pins
  for (int p=0; p<4; p++){
    digitalWrite(pins[p], pattern[p]);
  }
  delayMicroseconds(step_delay8);
}
