#ifndef LIST
#define LIST

#include "queue.h"

typedef struct node_type {

    struct node_type* next;
    Queue* data;

} Node;

typedef struct {

    Node* head;
    Node* tail;
    int size;

} List;

List* make_list();
Node* make_node(Queue* data, Node* next);

Queue* get(List* list, int index);
void append(List* list, Queue* data);

void free_node(Node* node);
void free_list(List* list);


#endif