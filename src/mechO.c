#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "list.h"
#include "sequence.h"
#include "parser.h"
#include "wiringPi.h"
#include "stepper.h"

//https://stackoverflow.com/questions/22059189/read-a-file-as-byte-array
//Thanks SO for how to read file into a byte array

int main(int argc, char* argv[]) {

    if(argc != 2) {
        printf("PLEASE INPUT FILENAME\n");
        return 1;
    }

    wiringPiSetup();
    piHiPri(99);
    

    FILE* file;
    unsigned char* bytes;
    long filelen;

    //Open the file in binary mode
    file = fopen(argv[1], "rb"); 
    //Jump to end of file
    fseek(file, 0, SEEK_END);
    //Get the length of the file (in bytes) by seeing the offset from first to last byte
    filelen = ftell(file);
    //Go back to beginning of file
    fseek(file, 0, SEEK_SET);

    //Make the array the right length
    //We don't need len+1 as in SO post because we dont need \0
    bytes = (unsigned char*)malloc((filelen)*sizeof(char));
    fread(bytes, 1, filelen, file);
    fclose(file);

    //The array bytes now contains all of the bytes from the midi file, so we can interpret it now
    
    Sequence* sequence = make_sequence();

    populateSequence(sequence, bytes);
    //printSequence(sequence);

    Stepper* s0 = make_stepper(16, 15, 8, getTrack(sequence, 0));
    Stepper* s1 = make_stepper(4, 1, 9, getTrack(sequence, 1));
    Stepper* s2 = make_stepper(6, 5, 7, getTrack(sequence, 2));
    Stepper* s3 = make_stepper(11, 10, 0, getTrack(sequence, 3));

    int startTime = micros();

    stepperInitTimes(s0);
    stepperInitTimes(s1);
    stepperInitTimes(s2);
    stepperInitTimes(s3);

    int clocks = sequence->clocks;
    float tempo = 500000;
    float microsPerTick = tempo/clocks;

    int end = 4;

    while(end != 0) {

        end = 4 - stepperDone(s0) - stepperDone(s1) - stepperDone(s2) - stepperDone(s3);

        stepperAdvance(s0, &microsPerTick, clocks);
        stepperAdvance(s1, &microsPerTick, clocks);
        stepperAdvance(s2, &microsPerTick, clocks);
        stepperAdvance(s3, &microsPerTick, clocks);
        
        stepperPlay(s0);
        stepperPlay(s1);
        stepperPlay(s2);
        stepperPlay(s3);
        
    }

    free_sequence(sequence);

    free_stepper(s0);
    free_stepper(s1);
    free_stepper(s2);
    free_stepper(s3);

    free(bytes);
    return 0;
}



