#ifndef SEQUENCE
#define SEQUENCE

typedef {

    int numtracks;
    List* tracks;

} Sequence;

void make_sequence();

void readMidi(unsigned char* bytes);
Event* getNextEvent(int track);

void free_sequence(Sequence* sequence);


#endif