#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "queue.h"
#include "sequence.h"

Sequence* make_sequence() {

    Sequence* sequence = calloc(1, sizeof(Sequence));
    sequence->numtracks = 0;
    sequence->tracks = make_list();
    return sequence;

}

Queue* getTrack(Sequence* sequence, int track) {
    return get(sequence->tracks, track);
}

void printSequence(Sequence* sequence) {

    printf("Tracks:%d\n", sequence->numtracks);

    for(int i = 0; i < sequence->numtracks; i++) {
        Queue* current = getTrack(sequence, i);
        printf("Track %d:\n", i);
        printQueue(current);
    }

}

void free_sequence(Sequence* sequence) {

    free_list(sequence->tracks);

    if(sequence != NULL) {
        free(sequence);
    }
    
    sequence = NULL;

}