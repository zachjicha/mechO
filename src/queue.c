#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

Event* make_event(int type, int dtime, int data, Event* next) {

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
    free(event);
}

void free_queue(Queue* queue) {
    Event* current = queue->front;

    while(current != NULL) {
        Event* next = current->next;

        free_event(current);
        current = next;
    }
    free(queue);
}

void enqueue(Queue* queue, int type, int dtime, int data) {

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