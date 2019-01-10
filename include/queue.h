#ifndef QUEUE
#define QUEUE

typedef struct node_type {

    struct node_type* next;
    int type;
    int time;
    int data;

} Node;

typedef struct {

    Node* front;
    Node* end;
    int size;

} Queue;

Node* node_event(int type, int dtime, int data, Node* next);
Queue* make_queue();

void free_node(Node* node);
void free_queue(Queue* queue);

void enqueue(Queue* queue, int type, int dtime, int data);
void* dequeue(Queue* queue);

#endif