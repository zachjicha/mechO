#ifndef PARSER
#define PARSER

#include "sequence.h"

typedef struct {

    int numbytes;
    int val;

} VariableLengthValue;

VariableLengthValue* make_variablelengthvalue();
void free_variablelengthvalue(VariableLengthValue* v);

int byteArrayToUnsignedInt(unsigned char* bytes, int first, int last);
VariableLengthValue* readVariableLengthValue(unsigned char* bytes, int first);
int runningStatusCheck(bool b);

void populateSequence(Sequence* sequence, unsigned char* bytes);

#endif