#ifndef SEQUENCE
#define SEQUENCE

typedef struct {

    int numtracks;
    List* tracks;

} Sequence;

Sequence* make_sequence();

void readMidi(unsigned char* bytes);
Event* getNextEvent(Sequence* sequence, int tracknum);

void free_sequence(Sequence* sequence);


#endif