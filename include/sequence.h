#ifndef SEQUENCE
#define SEQUENCE

#include "list.h"
#include "queue.h"

//Sequence
//tracks is a list of queues, each queue is a track
typedef struct {

    int numtracks;
    int clocks;
    List* tracks;

} Sequence;

//Create and destroy function
Sequence* make_sequence();
void free_sequence(Sequence* sequence);

//FUnction to get a track in the sequence
Queue* getTrack(Sequence* sequence, int track);
void printSequence(Sequence* sequence);


#endif