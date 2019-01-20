#ifndef STEPPER
#define STEPPER

#include "queue.h"


typedef struct {

    int enPin;
    int stepPin;
    long eventStartTime;
    long pulseEndTime;
    Event* currentEvent;
    Event* nextEvent;
    Queue* track;

} Stepper;

Stepper* make_stepper(int enPin, int stepPin, Queue* track);
void free_stepper(Stepper* stepper);

void stepperInitTimes(Stepper* stepper, long currtime);
void stepperAdvance(Stepper* stepper, long currtime, float *microsPerTick, float clocks);
void stepperEnable(Stepper* stepper);
void stepperPlay(Stepper* stepper, long currtime);


#endif