#ifndef LIST
#define LIST

#include "queue.h"

//This is the node for the linked list
typedef struct node_type {

    struct node_type* next;
    Queue* data;

} Node;

//This is the list itself, with size and pointers to special nodes
typedef struct {

    Node* head;
    Node* tail;
    int size;

} List;

//CReate functions for list and node
List* make_list();
Node* make_node(Queue* data, Node* next);

//Function to get a node at an index
Queue* get(List* list, int index);
//Function to create a node and add it to the end of the list 
void append(List* list, Queue* data);

//Destroy functions for node and list
void free_node(Node* node);
void free_list(List* list);


#endif