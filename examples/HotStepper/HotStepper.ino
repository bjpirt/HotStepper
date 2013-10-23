#include <HotStepper.h>

HotStepper stepper1(&PORTC, 0);
HotStepper stepper2(&PORTD, 4);

byte dir1;
byte dir2;

void setup(){
  dir1 = FORWARD;
  dir2 = FORWARD;
  Serial.begin(115200);
  Serial.println("stepper test!");
  HotStepper::setup();
  stepper1.turn(10, dir1);
  stepper2.turn(20, dir2);
}


void loop(){
  if(stepper1.ready()){
    dir1 = !dir1;
    stepper1.turn(10, dir1);
  }
  if(stepper2.ready()){
    dir2 = !dir2;
    stepper2.turn(20, dir2);
  }
}
