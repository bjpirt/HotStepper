#include "Arduino.h"
#include "HotStepper.h"

HotStepper *HotStepper::firstInstance;

HotStepper::HotStepper(volatile uint8_t* port, byte offset) {
  _port = port;
  _offset = offset;
  _remaining = 0;
  _paused = false;
  release();
  if(firstInstance){
    firstInstance->addNext(this);
  }else{
    firstInstance = this;
  }
}

void HotStepper::addNext(HotStepper *ref){
  if(nextInstance){
    nextInstance->addNext(ref);
  }else{
    nextInstance = ref;
  }
}

void HotStepper::instanceSetup(){
  if(_port == &PORTB){
    DDRB |= (0x0F << _offset);
  }else if(_port == &PORTC){
    DDRC |= (0x0F << _offset);
  }else if(_port == &PORTD){
    DDRD |= (0x0F << _offset);
  }
  if(nextInstance){
    nextInstance->instanceSetup();
  }
}

void HotStepper::setup(){
  if(firstInstance){
    firstInstance->instanceSetup();
  }

  // initialize Timer2 for a 3ms duty cycle
  cli();      // disable global interrupts

  TCCR2A = 0; // set entire TCCR2A register to 0
  TCCR2B = 0; // same for TCCR2B
	TCNT2  = 0; // initialize counter value to 0
  // set compare match register to desired timer count:
  OCR2A = 187;
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 bit for 256 prescaler
  TCCR2B |= (1 << CS21);   
  TCCR2B |= (1 << CS22);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  sei();      // ensable global interrupts
}

void HotStepper::pause(){
  _paused = true;
}

void HotStepper::resume(){
  _paused = false;
}

void HotStepper::turn(long steps, byte direction){
  _remaining = steps;
  _dir = direction;
}

boolean HotStepper::ready(){
  return (_remaining == 0);
}

long HotStepper::remaining(){
  return _remaining;
}

byte HotStepper::nextStep(byte currentStep){
  switch(currentStep){
    case B0000:
    case B0001:
      return (_dir == FORWARD ? B0010 : B1000);
    case B0010:
      return (_dir == FORWARD ? B0100 : B0001);
    case B0100:
      return (_dir == FORWARD ? B1000 : B0010);
    case B1000:
      return (_dir == FORWARD ? B0001 : B0100);
  }
}

void HotStepper::setNextStep(){
  if(_remaining > 0 && !_paused){
    digitalWrite(18, !digitalRead(18));
    _remaining--;
    setStep(nextStep(((byte)*_port >> _offset) & 0x0F));
  }else{
    release();
  }
}

void HotStepper::setStep(byte state){
  byte nextState = (byte)*_port;
  nextState &= ~(0x0F << _offset);
  nextState |= state << _offset;
  *_port = nextState;
}

void HotStepper::release(){
  if(((byte)*_port >> _offset) & 0x0F != 0){
    setStep(0);
  }
}

void HotStepper::trigger(){
  setNextStep();
  if(nextInstance){
    nextInstance->trigger();
  }
}

void HotStepper::triggerTop(){
  if(firstInstance){
    firstInstance->trigger();
  }
}

ISR(TIMER2_COMPA_vect)
{
  HotStepper::triggerTop();
}
