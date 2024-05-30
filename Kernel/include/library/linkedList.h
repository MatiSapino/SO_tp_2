#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#define ERROR -1
#define SUCCESS 0

// struct node_t;
// struct list_t;

// typedef struct node_t *node_ptr;
// typedef struct list_t * list_ptr;

typedef struct node {
    void *data;
    node_ptr next;
    node_ptr prev;
} node_t, *node_ptr;

typedef struct list {
    node_ptr start;
    node_ptr end;
    node_ptr current;
    int (*comp_funct)(void *, void *);
    int size;
} list_t, *list_ptr;

list_ptr new_linked_list(int (*comp_funct)(void *, void *));

node_ptr add(list_ptr list, void *data);

void *remove_node(list_ptr list, node_ptr node);

static node_ptr create_node(void *data, node_ptr prev_node);

/**
 * @brief   Moves the iterator to the first node of the list
 * @param  l: The list
 * @retval None
 */

void to_begin(list_ptr l);

/**
 * @brief  Checks whether the iterator has a next node or not
 * @param  l: The list
 * @retval 0 if there is not other node. != 0 if there is other node
 */

int has_next(list_ptr l);

/**
 * @brief   Gets the current node element and moves to the next node
 * @param  l: The list
 * @note    Use hasNext function before using next. If current node is NULL the behaviur is undefined
 * @retval The element of the currrent node
 */

void *next(list_ptr l);

void free_list(list_ptr list);

int get_length(list_ptr list);

int is_empty(list_ptr list);

node_ptr get_first(list_ptr list);

node_ptr prepend_node(list_ptr list, node_ptr node);

node_ptr append_node(list_ptr list, node_ptr node);

void *find(list_t *list, void *data, int (*comp_funct)(void *, void *));

#endif