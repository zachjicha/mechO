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

void readMidi(unsigned char* bytes);

Event* getNextEvent(Sequence* sequence, int tracknum) {

    Queue* track = get(sequence->tracks, tracknum);
    Event* event = dequeue(track);
    return event;

}

void free_sequence(Sequence* sequence) {

    Queue* current;

    for(int i = 0; i < sequence->numtracks; i++) {
        current = get(sequence->tracks, i);
        free_queue(current);
    }

    free(sequence);

}