#ifndef HotStepper_h
#define HotStepper_h

#include "Arduino.h"

#define FORWARD 1
#define BACKWARD 0

class HotStepper {
  public:
    HotStepper(volatile uint8_t* port, byte offset);
    static void setup();
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


#endif

