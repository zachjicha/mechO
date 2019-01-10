#ifndef LIST
#define LIST

typedef link_type {

    struct link_type* next;
    Queue* data;

} Link;

typedef {

    Link* head;
    Link* tail;
    int size;

} List;

List* make_list();
Node* make_link(Queue* data, Link* next);

Queue* get(List* list, int index);
void append(List* list, Queue* data);

void free_link(Link* link);
void free_list(List* list);


#endif