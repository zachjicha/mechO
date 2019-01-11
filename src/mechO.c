#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "list.h"
#include "sequence.h"
#include "parser.h"

//https://stackoverflow.com/questions/22059189/read-a-file-as-byte-array
//Thanks SO for how to read file into a byte array

int main(int argc, char* argv[]) {

    if(argc != 2) {
        printf("PLEASE INPUT FILENAME\n");
        return 1;
    }

    FILE* file;
    unsigned char* bytes;
    long filelen;

    //Open the file in binary mode
    file = fopen(argv[1], "rb"); 
    //Jump to end of file
    fseek(file, 0, SEEK_END);
    //Get the length of the file (in bytes) by seeing the offset from first to last byte
    filelen = ftell(file);
    //Go back to beginning of file
    fseek(file, 0, SEEK_SET);

    //Make the array the right length
    //We don't need len+1 as in SO post because we dont need \0
    bytes = (unsigned char*)malloc((filelen)*sizeof(char));
    fread(bytes, 1, filelen, file);
    fclose(file);

    //The array bytes now contains all of the bytes from the midi file, so we can interpret it now
    
    Sequence* sequence = make_sequence();

    populateSequence(sequence, bytes);

    free_sequence(sequence);




    free(bytes);
    return 0;
}


