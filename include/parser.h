#ifndef PARSER
#define PARSER

#include <stdbool.h>
#include "sequence.h"

typedef struct {

    int numbytes;
    int value;

} VariableLengthValue;

VariableLengthValue* make_variablelengthvalue();
void free_variablelengthvalue(VariableLengthValue* v);

int byteArrayToUnsignedInt(unsigned char* bytes, int first, int last);
VariableLengthValue* readVariableLengthValue(unsigned char* bytes, int first);

void populateSequence(Sequence* sequence, unsigned char* bytes);

#endif