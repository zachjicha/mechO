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

Event* getNextEvent(Sequence* sequence, int tracknum) {

    Queue* track = get(sequence->tracks, tracknum);
    Event* event = dequeue(track);
    return event;

}

void free_sequence(Sequence* sequence) {

    free_list(sequence->tracks);
    free(sequence);

}