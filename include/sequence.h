#ifndef SEQUENCE
#define SEQUENCE

#include "list.h"
#include "queue.h"

typedef struct {

    int numtracks;
    int clocks;
    List* tracks;

} Sequence;

Sequence* make_sequence();

Queue* getTrack(Sequence* sequence, int track);
void printSequence(Sequence* sequence);

void free_sequence(Sequence* sequence);


#endif