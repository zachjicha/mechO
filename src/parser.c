#include "queue.h"
#include "list.h"
#include "pitchvals.h"
#include "sequence.h"

//Most if not all of the following code is taken from Stepper-Music ConvertMidi.java

VariableLengthValue* make_variablelengthvalue() {

    VariableLengthValue* v = calloc(1, sizeof(VariableLengthValue));
    v->numbytes = 0;
    v->value = 0;
    return v;

}

void free_variablelengthvalue(VariableLengthValue* v) {

    free(v);

}

int byteArrayToUnsignedInt(unsigned char* bytes, int first, int last) {

    //If we start after we end, return -1 (error)
    if(first > last) {
        return -1;
    }
    
    //Sum all of the bytes in the given indices
    //multiply by 256 to account for moving place values
    int sum = 0;
    for(int i = first; i <= last; i++) {
        sum = (sum*256) + bytes[i];
    }

    return sum;
}

VariableLengthValue* readVariableLengthValue(unsigned char* bytes, int first) {

    VariableLengthValue* v = make_variablelengthvalue();

    //The length stored in variable length format
    int value = 0;
    //The amount of bytes the variable length value is
    int numbytes = 0;

    int i = first;

    do {
        //Multiply to adjust for place values, mask as first bit does not store data
        value = (value*128) + (bytes[i] & 0x7F);
        numbytes++;
    } while((bytes[i++] & 0x80) == 0x80);
    //Loop while first bit == 1

    v->numbytes = numbytes;
    v->value = value;

    return v;
}

int runningStatusCheck(bool b) {
    if(b) {
        return 1;
    }
    else {
        return 0;
    }
}

//Strap in, this takes a while
void populateSequence(Sequence* sequence, unsigned char* bytes) {

    //Get the number of tracks
    int tracks = byteArrayToUnsignedInt(bytes, 10, 11);
    //Get the pulses per quarter note
    int clocks = byteArrayToUnsignedInt(bytes, 12, 13);

    //Variable that tracks the index of the first byte of the current track
    //Starts at 14 since the header chunk is always 14 bytes long
    int trackStartIndex = 14;

    //Status is the type of Midi message event, seperate from meta and SYSEX events
    unsigned char status = 0;

    //Boolean to track whether we are in running status or not
    bool isRunningStatus = false;

    //Loop through each track
    for(int i = 0; i < tracks; i++) {

        //Check to make sure its a track chunk
        if(bytes[trackStartIndex] != 0x4D || bytes[trackStartIndex+1] != 0x54 || bytes[trackStartIndex+2] != 0x72 || bytes[trackStartIndex+3] != 0x6B) {
            //If not, continue
            i--;
            System.out.println("Found a non-track chunk, continuing...");
            trackStartIndex += 8 + byteArrayToUnsignedInt(bytes, trackStartIndex+4, trackStartIndex+7);
            continue;
        }

        //Make a queue that represents the current track
        Queue* currentTrack = make_queue();
        append(sequence->tracks, currentTrack);

        //Length of the data of the chunk
        int chunkLength = byteArrayToUnsignedInt(bytes, trackStartIndex+4, trackStartIndex+7);

        //MTrk chunks are split into three main parts: the MTrk tag, length, and data
        //The data contains the delta time event pairs

        //pairStartIndex is the index of the first byte of a delta time/event pair
        //it starts at the first byte of the data
        int pairStartIndex = trackStartIndex + 8;

        //chunkLength + trackStartIndex + 8 is the first byte of the next chunk
        //this is since the start of the chunk is s, the header is 8 bytes and the rest is chunkLength bytes
        //Loop through each dt/event pair
        while(pairStartIndex < chunkLength + trackStartIndex + 8) {

            //Here are the members of the event we will create
            int eventType = 0;
            int eventTime = 0;
            int eventData = 0;
            
            //Set the members of the event
            VariableLengthValue* deltaRead = readVariableLength(bytes, pairStartIndex);
            eventTime = deltaRead->value;

            //eventStartIndex is the index of the first byte of the event in the current delta time/event pair
            int eventStartIndex = pairStartIndex + deltaRead->numbytes;

            //We are done with delta read
            free_variablelengthvalue(deltaRead);

            //Index of the next event pair
            int nextPairStartIndex = 0;

            //If this condition is true, then it is a meta event
            if(bytes[eventStartIndex] == 0xFF) {

                //This byte holds the type of meta event
                //It is analogous to status
                unsigned char type = bytes[eventStartIndex + 1];

                //Check the type of meta event
                if(type < 0x21 || type == 0x7F || type == 0x54 || type == 0x58 || type == 0x59) {
                    //This is for events we dont care about
                    VariableLengthValue* variableLengthRead = readVariableLength(bytes, eventStartIndex + 2);
                    //The index of ther next event pair is the sum of (in order of adding):
                    //Length of the event data
                    //Length of the Length (how many bytes were used to store the length)
                    //The current eventStartIndex
                    //2 (1 is for the byte that marks the event as meta, 1 for the type of meta event)
                    nextPairStartIndex = variableLengthRead->value + variableLengthRead->numbytes + eventStartIndex + 2;
                    free_variablelengthvalue(variableLengthRead);
                    //Skip the rest of this loop
                    continue;
                }
                else if(type == 0x2F) {
                    //This is an EOT event
                    eventData = 0;
                    eventType = 3;
                    //Record the length of the dt/event pair
                    //EOT event is always 3 long
                    nextPairStartIndex = 3 + eventStartIndex;
                }
                else if(type == 0x51) {
                    //this is a tempo meta event
                    int tempo = byteArrayToUnsignedInt(bytes, eventStartIndex+2, eventStartIndex+4);
                    eventData = tempo;
                    eventType = 2;
                    //Record the length of the dt/event pair
                    //Tempo event is always 6 long
                    nextPairStartIndex = 6 + eventStartIndex;
                }
            }

            //This case is for system exclusive events, irrelevant
            else if(bytes[eventStartIndex] == 0xF0 || bytes[eventStartIndex] == 0xF7) {
                //Record the length of the dt/event pair
                VariableLengthValue* variableLengthRead = readVariableLength(bytes, eventStartIndex + 2);
                //The index of ther next event pair is the sum of (in order of adding):
                //Length of the event data
                //Length of the Length (how many bytes were used to store the length)
                //The current eventStartIndex
                //1 (for the byte that marks the event as SYSEX)
                nextPairStartIndex = variableLengthRead[0] + variableLengthRead[1] + eventStartIndex + 1;
                free_variablelengthvalue(variableLengthRead);
                //Skip the rest of this loop
                continue;
            }

            //If we got here, that means we have a regular midi event
            else {

                //Check if we are in running status
                if(bytes[eventStartIndex] > 0x7F) {
                    //If bytes[k] is greater than 0x7F, then it is a new status, so we record it
                    status = bytes[eventStartIndex];
                    isRunningStatus = false;
                }

                //If we skipped the prior if statement, then we are in running status, so keep using the previous status

                //Check which status we are in
                if((status & 0xF0) == 0xB0) {

                    //If we are here, then this is either a Channel Mode Message or Controller Change message
                    //None of these events are relevant
                    //All events in this grouping have a length of 3
                    nextPairStartIndex = 3 + eventStartIndex;
                    isRunningStatus = true;
                    continue;
                }

                //If we reach this condition, then the event is a Midi Voice Message
                //Finally the good stuff
                else {

                    //Check the status byte
                    if((status & 0xF0) == 0x80) {
                        //Note off message
                        eventData = 0;
                        eventType = 0;
                        //Record the length of the dt/event pair
                        nextPairStartIndex = 3 + eventStartIndex - runningStatusCheck(isRunningStatus);
                        isRunningStatus = true;
                    }
                    else if((status & 0xF0) == 0x90) {
                        //Note on message
                        int pitchIndex = bytes[eventStartIndex + 1 - runningStatusCheck(isRunningStatus)];

                        int velocity = bytes[eventStartIndex + 2 - runningStatusCheck(isRunningStatus)];
                            if(velocity == 0) {
                                //Velocity of zero is really a note off event to sustain running status
                                eventData = 0;
                                eventType = 0;
                            }
                            else {
                                //TODO PUT SPACE BETWEEN NOTES HERE
                                eventData = pitchVals[pitchIndex];
                                eventType = 1;
                            }
                        //Record the length of the dt/event pair
                        nextPairStartIndex = 3 + eventStartIndex - runningStatusCheck(isRunningStatus);
                        isRunningStatus = true;
                    }
                    else if((status & 0xF0) == 0xA0) {
                        //Polyphonic pressure
                        nextPairStartIndex = 3 + eventStartIndex;
                        isRunningStatus = true;
                        continue;
                    }
                    else if((status & 0xF0) == 0xC0) {
                        //Program Change
                        //Record the length of the dt/event pair
                        nextPairStartIndex = 2 + eventStartIndex;
                        isRunningStatus = true;
                        continue;
                    }
                    else if((status & 0xF0) == 0xD0) {
                        //Channel Key Pressure
                        //Record the length of the dt/event pair
                        nextPairStartIndex = 2 + eventStartIndex;
                        isRunningStatus = true;
                        continue;
                    }
                    else if((status & 0xF0) == 0xE0) {
                        //Pitch Bend
                        //TODO This one might actually be useful at some time
                        //Record the length of the dt/event pair
                        nextPairStartIndex = 3 + eventStartIndex;
                        isRunningStatus = true;
                        continue;
                    }
                }
            }
            //Finally! Bless your soul if you got here!

            //Now if we are here that means we got one of the handful of relevant events
            //So we can add it to our track
            enqueue(currentTrack, eventType, eventTime, eventData);
        }
    }
}