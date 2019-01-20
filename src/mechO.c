#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "list.h"
#include "sequence.h"
#include "parser.h"
#include "wiringPi.h"
#include "stepper.h"
#include <sys/time.h>

//Curtesy of https://gist.github.com/sevko/d23646ba07c77c15fde9
long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

//https://stackoverflow.com/questions/22059189/read-a-file-as-byte-array
//Thanks SO for how to read file into a byte array

int main(int argc, char* argv[]) {

    if(argc != 2) {
        printf("PLEASE INPUT FILENAME\n");
        return 1;
    }

    wiringPiSetup();

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

    Stepper* s0 = make_stepper(16, 15, getTrack(sequence, 0));
    Stepper* s1 = make_stepper(4, 1, getTrack(sequence, 1));

    long startTime = getMicrotime();

    stepperInitTimes(s0, startTime);
    stepperInitTimes(s1, startTime);

    float tempo = 500000;
    float microsPerTick = tempo/sequence->clocks;

    //printSequence(sequence);

    int end = 2;

    while(end != 0) {

        end = 2 - stepperDone(s0) - stepperDone(s1);

        long currentTime = getMicrotime();

        stepperAdvance(s0, currentTime, &microsPerTick, sequence->clocks);
        stepperAdvance(s1, currentTime, &microsPerTick, sequence->clocks);

        stepperEnable(s0);
        stepperEnable(s1);

        stepperPlay(s0, currentTime);
        stepperPlay(s1, currentTime);
    }

    free_sequence(sequence);



    free(bytes);
    return 0;
}



