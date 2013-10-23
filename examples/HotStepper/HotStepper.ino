#include <HotStepper.h>

HotStepper stepper1(&PORTC, 0);
//HotStepper stepper2(PORTD, 4);

byte dir;

void setup(){
  dir = FORWARD;
  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);
  Serial.begin(115200);
  Serial.println("stepper test!");
  HotStepper::setup();
  stepper1.instanceSetup();
  DDRC |= (0x0F << 0);
  stepper1.turn(10, FORWARD);
}


void loop(){
  if(stepper1.ready()){
    digitalWrite(19, !digitalRead(19));
    dir = !dir;
    stepper1.turn(10, dir);
  }
  //stepper2.ready();
//  digitalWrite(2, 1);
}
