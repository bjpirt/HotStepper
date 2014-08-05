// Configure the library to use Timer 1
#define HOTSTEPPER_TIMER1
// Include the library
#include <HotStepper.h>

// Instatiate some stepper motors
HotStepper stepper1(&PORTB, 0b00011101);
HotStepper stepper2(&PORTD, 0b11110000);

byte dir1;
byte dir2;

void setup(){
  dir1 = FORWARD;
  dir2 = FORWARD;
  // Make sure the ports and timer are configured - tell it to use Timer 1
  HotStepper::setup(TIMER1INT);
  // Control our steppers
  stepper1.turn(10, dir1);
  stepper2.turn(20, dir2);
}


void loop(){
  // ready will return true when the stepper has moved the desired number of steps
  if(stepper1.ready()){
    dir1 = !dir1;
    stepper1.turn(1000, dir1);
  }
  if(stepper2.ready()){
    dir2 = !dir2;
    stepper2.turn(2000, dir2);
  }
}