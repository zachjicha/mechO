#ifndef SEQUENCE
#define SEQUENCE

typedef struct {

    int numtracks;
    int clocks;
    List* tracks;

} Sequence;

Sequence* make_sequence();

Event* getNextEvent(Sequence* sequence, int tracknum);

void free_sequence(Sequence* sequence);


#endif