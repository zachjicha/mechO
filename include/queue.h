#ifndef QUEUE
#define QUEUE

typedef struct event_type {

    struct event_type* next;
    int type;
    int time;
    int data;

} Event;

typedef struct {

    Event* front;
    Event* end;
    int size;

} Queue;

Event* make_event(int type, int dtime, int data, Event* next);
Queue* make_queue();

void free_event(Event* event);
void free_queue(Queue* queue);

void enqueue(Queue* queue, int type, int dtime, int data);
void* dequeue(Queue* queue);

#endif