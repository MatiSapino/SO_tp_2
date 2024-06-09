#ifndef _CIRCULAR_LINKED_LIST_H_
#define _CIRCULAR_LINKED_LIST_H_
#include <pmm.h>
#include <process.h> 
#include <linked_list.h>

#define ERROR         -1
#define SUCCESS       0

typedef list_ptr circular_list_ptr;
typedef iterator_ptr circular_list_iterator_ptr;

circular_list_ptr new_circular_linked_list(int (*comp_funct)(void *, void *));
circular_list_iterator_ptr new_circular_list_iterator(circular_list_ptr l);

void cl_add(circular_list_ptr list, void *data);
void *cl_remove(circular_list_ptr list, void *data);
void *cl_find(circular_list_ptr list, void *data, int (*comp_funct)(void *, void *));
void cl_to_begin(circular_list_ptr list, circular_list_iterator_ptr i);
int cl_has_next(circular_list_iterator_ptr i);
void *cl_next(circular_list_iterator_ptr i);
void cl_free_list(circular_list_ptr list);
void cl_free_iterator(circular_list_iterator_ptr i);
int cl_size(circular_list_ptr l);
void cl_subscribe_iterator(circular_list_ptr l, circular_list_iterator_ptr i);
void cl_unsubscribe_iterator(circular_list_ptr l, circular_list_iterator_ptr i);

#endif