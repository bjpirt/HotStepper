#ifndef HotStepper_h
#define HotStepper_h
#include "Arduino.h"


#define FORWARD 1
#define BACKWARD 0

#define TIMER1INT 1
#define TIMER2INT 2

#ifndef HOTSTEPPER_TIMER1
  #define HOTSTEPPER_TIMER2
#endif


class HotStepper {
  public:
    HotStepper(volatile uint8_t* port, byte offset);
    static void setup();
    static void setup(char timer);
    void instanceSetup();
    void turn(long steps, byte direction);
    boolean ready();
    long remaining();
    void release();
    static void triggerTop();
    void pause();
    void resume();
    void stop();
  private:
    static HotStepper *firstInstance;
    HotStepper *nextInstance;
    void addNext(HotStepper *ref);
    boolean _paused;
    volatile uint8_t* _port;
    byte _offset;
    volatile long _remaining;
    byte _dir;
    byte nextStep(byte);
    void setStep(byte);
    void setNextStep();
    void trigger();
};

#ifndef FROM_LIB
#ifdef HOTSTEPPER_TIMER1
ISR(TIMER1_COMPA_vect)
{
  HotStepper::triggerTop();
}
#endif

#ifdef HOTSTEPPER_TIMER2
ISR(TIMER2_COMPA_vect)
{
  HotStepper::triggerTop();
}
#endif
#endif

#endif

