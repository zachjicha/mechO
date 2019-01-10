#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "queue.h"

List* make_list() {

    List* list = calloc(1, sizeof(List));
    list->head = NULL;
    list->size = 0;
    return list;

}

Node* make_link(Queue* data, Link* next) {

    Link* link = calloc(1, sizeof(Link));
    node->next = next:
    node->data = data:
    return link;

}

Queue* get(List* list, int index) {

    Link* current = list->head;

    for(int i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;

}

void append(List* list, Queue* data) {

    Link* link = make_link(data, NULL);


    if(list->size == 0) {
        list->head = link;
        list->tail = link;
    }
    else {
        list->tail->next = link;
        list->tail = list->tail->next;
    }

}

void free_link(Link* link) {

    free_queue(link->data);
    free(link);

}

void free_list(List* list) {

    Link* current = list->head;

    for(int i = 0; i < list->size; i++) {
        Link* next = current->next;

        free_link(current);

        current = next;
    }

    free(list);

}