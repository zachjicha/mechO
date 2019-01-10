#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "list.h"

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
    

    Queue* q = make_queue();
    enqueue(q, 1, 0, 3000);
    enqueue(q, 0, 500, 3000);
    enqueue(q, 3, 1, 0);

    Queue* e = make_queue();
    enqueue(e, 1, 0, 3000);
    enqueue(e, 0, 500, 3000);
    enqueue(e, 3, 1, 0);

    Queue* d = make_queue();
    enqueue(d, 1, 0, 3000);
    enqueue(d, 0, 500, 3000);
    enqueue(d, 3, 1, 0);

    List* l = make_list();
    append(l, q);
    append(l, e);
    append(l, d);

    for(int j = 0; j < 3; j++) {
        Queue* qu = get(l, j);
        for(int i = 0; i < 3; i++) {
            Event* e = dequeue(qu);
            printf("T:%d T:%d D:%d\n", e->type, e->time, e->data);
            free_event(e);
        }
    }

    free_list(l);



    free(bytes);
    return 0;
}


