#ifndef _CIRCULAR_LINKED_LIST_H_
#define _CIRCULAR_LINKED_LIST_H_

typedef struct list_t *circular_list_t;
typedef struct iterator_t *circular_list_iterator_t;

circular_list_t new_circular_linked_list(int (*comp_funct)(void *, void *));
circular_list_iterator_t new_circular_list_iterator(circular_list_t l);

void cl_add(circular_list_t list, void *data);
void *cl_remove(circular_list_t list, void *data);
void *cl_find(circular_list_t list, void *data, int (*comp_funct)(void *, void *));
void cl_to_begin(circular_list_t list, circular_list_iterator_t i);
int cl_has_next(circular_list_iterator_t i);
void *cl_next(circular_list_iterator_t i);
void cl_free_list(circular_list_t list);
void cl_free_iterator(circular_list_iterator_t i);
int cl_size(circular_list_t l);
void cl_subscribe_iterator(circular_list_t l, circular_list_iterator_t i);
void cl_unsubscribe_iterator(circular_list_t l, circular_list_iterator_t i);

#endif