// Include the library
#include <HotStepper.h>

// Instatiate some stepper motors
HotStepper stepper1(&PORTC, 0);
HotStepper stepper2(&PORTD, 4);

byte dir1;
byte dir2;

void setup(){
  dir1 = FORWARD;
  dir2 = FORWARD;
  // Make sure the ports and timer are configured
  HotStepper::setup();
  // Control our steppers
  stepper1.turn(10, dir1);
  stepper2.turn(20, dir2);
}


void loop(){
  // ready will return true when the stepper has moved the desired number of steps
  if(stepper1.ready()){
    dir1 = !dir1;
    stepper1.turn(10, dir1);
  }
  if(stepper2.ready()){
    dir2 = !dir2;
    stepper2.turn(20, dir2);
  }
}