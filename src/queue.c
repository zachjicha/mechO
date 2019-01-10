#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

Event* make_node(int type, int dtime, int data, Node* next) {

    Node* node = calloc(1, sizeof(Node));
    node->type = type;
    node->time = dtime;
    node->data = data;
    node->next = next;
    return node;
}

Queue* make_queue() {

    Queue* queue = calloc(1, sizeof(Queue));
    queue->front = NULL;
    queue->end = NULL;
    queue->size = 0;
    return queue;

}

void free_node(Node* node) {
    free(node);
}

void free_queue(Queue* queue) {
    Node* current = queue->front;

    while(current != NULL) {
        Node* next = current->next;

        free_node(current);
        current = next;
    }
    free(queue);
}

void enqueue(Queue* queue, int type, int dtime, int data) {

    Node* node = make_node(type, dtime, data, NULL);

    if(queue->size == 0) {
        queue->front = node;
        queue->end = node;
    }
    else {
        queue->end->next = node;
        queue->end = node;
    }

    queue->size++;
    return;
}

void* dequeue(Queue* queue) {

    if(queue->size == 0) {
        return NULL;
    }

    Node* toReturn = queue->front;
    queue->front = queue->front->next;

    if(queue->size == 1) {
        queue->end = NULL;
    }

    queue->size--;

    return toReturn;
}