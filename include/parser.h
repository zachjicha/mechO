#ifndef PARSER
#define PARSER

#include "sequence.h"

// This struct hold data about variable length values, 
// specifically the value itself and the number of bytes used to store that data
typedef struct {

    int numbytes;
    int value;

} VariableLengthValue;

//Create and destroy functions for VariableLengthValue
VariableLengthValue* make_variablelengthvalue();
void free_variablelengthvalue(VariableLengthValue* v);

//Reads an array of bytes starting at index first ending at last, and interprets it as one number (little endian)
int byteArrayToUnsignedInt(unsigned char* bytes, int first, int last);
//Reads a variable length value and returns a struct that represents it
VariableLengthValue* readVariableLengthValue(unsigned char* bytes, int first);

//Reads a midi file and populates a sequence with its data
void populateSequence(Sequence* sequence, unsigned char* bytes);

#endif