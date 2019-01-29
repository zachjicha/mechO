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

//Create and destroy fucntions
Stepper* make_stepper(int enPin, int stepPin, int modePin, Queue* track);
void free_stepper(Stepper* stepper);

//Retuns 1 if stepper has reached EOT, else 0
int stepperDone(Stepper* stepper);
//Inits times to start of program
void stepperInitTimes(Stepper* stepper);
//Handles advancing to the next event
void stepperAdvance(Stepper* stepper, float *microsPerTick, float clocks);
//Handles turning the motor on and off based on the event type
void stepperEnable(Stepper* stepper);
//Handles pulsing the motor at correct frequency
void stepperPlay(Stepper* stepper);
//Disables motor
void stepperIdle(Stepper* stepper);


#endif
