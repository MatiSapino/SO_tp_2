#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

typedef struct node_list_t {
    void *data;
    struct node_list_t *next;
} node_list_t;

typedef struct list_t {
    struct node_list_t *start;
    struct node_list_t *end;
    struct node_list_t *current;
    // function that will compare node->data with argument "data" for deletion
    int (*comp_funct)(void *, void *);
    int size;
} list_t;

typedef struct node_list_t *node_list_ptr;
typedef struct list_t *list_ptr;

#endif