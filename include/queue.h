#ifndef QUEUE
#define QUEUE

//Custom node of queue
typedef struct event_type {

    struct event_type* next;
    int type;
    int time;
    long data;

} Event;

//Queue itself
typedef struct {

    Event* front;
    Event* end;
    int size;

} Queue;

//Create and destroy functions
Event* make_event(int type, int dtime, long data, Event* next);
Queue* make_queue();
void free_event(Event* event);
void free_queue(Queue* queue);

//Queue functions (no dequeue necessary)
void enqueue(Queue* queue, int type, int dtime, long data);
Event* dequeue(Queue* queue);
//Prints contents of queue for debugging
void printQueue(Queue* queue);

#endif