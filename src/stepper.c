#include "stepper.h"
#include "queue.h"
#include "wiringPi.h"
#include <stdlib.h>

Stepper* make_stepper(int enPin, int stepPin, int modePin, Queue* track) {

    Stepper* stepper = calloc(1, sizeof(Stepper));
    stepper->done = 0;
    stepper->enPin = enPin;
    stepper->stepPin = stepPin;
    stepper->modePin = modePin;
    pinMode(enPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    digitalWrite(enPin, HIGH);
    stepper->eventStartTime = 0;
    stepper->pulseEndTime = 0;
    stepper->track = track;
    stepper->currentEvent = dequeue(stepper->track);
    stepper->nextEvent = dequeue(stepper->track);
    return stepper;

}

void free_stepper(Stepper* stepper) {

    free_event(stepper->currentEvent);
    free_event(stepper->nextEvent);

    if(stepper != NULL) {
        free(stepper);
    }

    stepper = NULL;
    
}

int stepperDone(Stepper* stepper) {
    return stepper->done;
}

void stepperInitTimes(Stepper* stepper) {
    stepper->eventStartTime = micros();
    stepper->pulseEndTime = micros();
}

void stepperAdvance(Stepper* stepper, float *microsPerTick, float clocks) {
    int type = stepper->currentEvent->type;

    if(type == 3) {
        digitalWrite(stepper->enPin, HIGH);
        stepper->done = 1;
    }
    else if(micros() - stepper->eventStartTime >= (stepper->nextEvent->time * (*microsPerTick))) {
        if(type == 2) {
            *microsPerTick = (stepper->currentEvent->data)/clocks;
        }

        if(stepper->currentEvent->data < 2800 || stepper->currentEvent->data > 4200) {
            digitalWrite(stepper->modePin, HIGH);
        }
        else {
            digitalWrite(stepper->modePin, LOW);
        }


        free_event(stepper->currentEvent);
        stepper->eventStartTime += (stepper->nextEvent->time * (*microsPerTick));
        stepper->currentEvent = stepper->nextEvent;
        stepper->nextEvent = dequeue(stepper->track);
        stepperEnable(stepper);
    }
    
}

void stepperEnable(Stepper* stepper) {
    if(stepper->currentEvent->type == 1) {
        digitalWrite(stepper->enPin, LOW);
    }
    else {
        digitalWrite(stepper->enPin, HIGH);
    }
}

void stepperPlay(Stepper* stepper) {
    if(micros() - stepper->pulseEndTime >= stepper->currentEvent->data) {
        stepper->pulseEndTime += stepper->currentEvent->data;
        digitalWrite(stepper->stepPin, HIGH);
        digitalWrite(stepper->stepPin, LOW);
    }
}
