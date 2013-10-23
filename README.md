HotStepper
==========

An interrupt-driven stepper motor driver for Arduino.

This library has been designed with efficiency in mind and so has the requirement that your stepper pins are all on one port and consecutive. This means that you can set all pins in one operation, rather than having to toggle individual pins. It is interrupt-driven, which means that once you tell it to move a number of steps, it will continue to do this in the background using interrupts for timing. You can use the "ready()" function to check when you should give it more commands. It will currently drive 3 steppers, one per port (although if you don't want serial comms you can drive 4 in total) and at the moment it will use the same speed for all of them.

Example
-------

```c

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

```
