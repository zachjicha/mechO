#ifndef STEPPER
#define STEPPER

#include "queue.h"


typedef struct {

    int done;
    int enPin;
    int stepPin;
    int modePin;
    int eventStartTime;
    int pulseEndTime;
    Event* currentEvent;
    Event* nextEvent;
    Queue* track;

} Stepper;

Stepper* make_stepper(int enPin, int stepPin, int modePin, Queue* track);
void free_stepper(Stepper* stepper);

int stepperDone(Stepper* stepper);
void stepperInitTimes(Stepper* stepper);
void stepperAdvance(Stepper* stepper, float *microsPerTick, float clocks);
void stepperEnable(Stepper* stepper);
void stepperPlay(Stepper* stepper);
void stepperIdle(Stepper* stepper);


#endif
