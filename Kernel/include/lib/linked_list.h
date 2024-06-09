#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#define MAX_ITERATORS 2


typedef struct node {
    void *data;
    struct node * next;
} node_t;
typedef node_t * node_ptr;

typedef struct iterator {
    node_ptr start;
    node_ptr end;
    node_ptr current;
    int visited;
} iterator_t;
typedef iterator_t * iterator_ptr;


typedef struct list {
    node_ptr start;
    node_ptr end;
    node_ptr current;
    int (*comp_funct)(void *, void *); // function that will compare node->data with argument "data" for deletion
    int size;
    iterator_ptr iterators[MAX_ITERATORS]; // one iterator can subscribe to the list and be notified with changes
} list_t;
typedef list_t * list_ptr;

list_ptr new_linked_list(int (*comp_funct)(void *, void *));

void add(list_ptr list, void * data);
int remove(list_ptr list, void * data);
void * find(list_ptr list, void * data, int (*comp_funct)(void *, void *));
void to_begin(list_ptr l);
int hasNext(list_ptr l);
void * next(list_ptr l);
void free_list(list_ptr list);
int size(list_ptr l);

#endif 