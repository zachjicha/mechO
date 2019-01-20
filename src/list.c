#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "queue.h"

List* make_list() {

    List* list = calloc(1, sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;

}

Node* make_node(Queue* data, Node* next) {

    Node* node = calloc(1, sizeof(Node));
    node->next = next;
    node->data = data;
    return node;

}

Queue* get(List* list, int index) {

    Node* current = list->head;

    for(int i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;

}

void append(List* list, Queue* data) {

    Node* node = make_node(data, NULL);


    if(list->size == 0) {
        list->head = node;
        list->tail = node;
    }
    else {
        list->tail->next = node;
        list->tail = list->tail->next;
    }

    list->size++;

}

void free_node(Node* node) {

    free_queue(node->data);

    if(node != NULL) {
        free(node);
    }
    
    node = NULL;

}

void free_list(List* list) {

    Node* current = list->head;

    for(int i = 0; i < list->size; i++) {
        Node* next = current->next;

        free_node(current);

        current = next;
    }

    if(list != NULL) {
        free(list);
    }

    list = NULL;

}