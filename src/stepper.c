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

//Handles advancing to next event
void stepperAdvance(Stepper* stepper, float *microsPerTick, float clocks) {
    int type = stepper->currentEvent->type;

    //Check type of current event
    if(type == 3) {
        //EOT, disable motor
        digitalWrite(stepper->enPin, HIGH);
        stepper->done = 1;
    }
    //If length of event has passed
    else if(micros() - stepper->eventStartTime >= (stepper->nextEvent->time * (*microsPerTick))) {
        if(type == 2) {
            *microsPerTick = (stepper->currentEvent->data)/clocks;
        }

        //Set motor to half step mode if note is especially high or low
        //Helps to combat weird noises and ugly sounds
        if(stepper->currentEvent->data < 2800 || stepper->currentEvent->data > 4200) {
            digitalWrite(stepper->modePin, HIGH);
        }
        else {
            digitalWrite(stepper->modePin, LOW);
        }

        //Advance the current event
        free_event(stepper->currentEvent);
        stepper->eventStartTime += (stepper->nextEvent->time * (*microsPerTick));
        stepper->currentEvent = stepper->nextEvent;
        stepper->nextEvent = dequeue(stepper->track);
        //If tempo event, update tempo
        if(stepper->currentEvent->type == 2) {
            *microsPerTick = (stepper->currentEvent->data)/clocks;
        }
        stepperEnable(stepper);
    }
    
}

//If current events type is 1, enable motor
void stepperEnable(Stepper* stepper) {
    if(stepper->currentEvent->type == 1) {
        digitalWrite(stepper->enPin, LOW);
    }
    else {
        digitalWrite(stepper->enPin, HIGH);
    }
}

//If the period of the note has passed, pulse the motor
void stepperPlay(Stepper* stepper) {
    if(micros() - stepper->pulseEndTime >= stepper->currentEvent->data) {
        stepper->pulseEndTime += stepper->currentEvent->data;
        digitalWrite(stepper->stepPin, HIGH);
        digitalWrite(stepper->stepPin, LOW);
    }
}

void stepperIdle(Stepper* stepper) {
    digitalWrite(stepper->enPin, HIGH);
}
