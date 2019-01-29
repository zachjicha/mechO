#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

//THis is just a queue with a custom node

Event* make_event(int type, int dtime, long data, Event* next) {

    Event* event = calloc(1, sizeof(Event));
    event->type = type;
    event->time = dtime;
    event->data = data;
    event->next = next;
    return event;
}

Queue* make_queue() {

    Queue* queue = calloc(1, sizeof(Queue));
    queue->front = NULL;
    queue->end = NULL;
    queue->size = 0;
    return queue;

}

void free_event(Event* event) {

    if(event != NULL) {
        free(event);
    }

    event = NULL;
    
}

void free_queue(Queue* queue) {
    Event* current = queue->front;

    while(current != NULL) {
        Event* next = current->next;

        free_event(current);
        current = next;
    }

    if(queue != NULL) {
        free(queue);
    }

    queue = NULL;
    
}

void enqueue(Queue* queue, int type, int dtime, long data) {

    Event* event = make_event(type, dtime, data, NULL);

    if(queue->size == 0) {
        queue->front = event;
        queue->end = event;
    }
    else {
        queue->end->next = event;
        queue->end = queue->end->next;
    }

    queue->size++;
    return;
}

Event* dequeue(Queue* queue) {

    if(queue->size == 0) {
        return NULL;
    }

    Event* toReturn = queue->front;
    queue->front = queue->front->next;

    if(queue->size == 1) {
        queue->end = NULL;
    }

    queue->size--;

    return toReturn;
}

void printQueue(Queue* queue) {

    Event* current = queue->front;

    while(current != NULL) {
        printf("Type: %d  Time: %d  Data: %d\n", current->type, current->time, current->data);
        current = current->next;
    }

}