#include <linkedList.h>
#include <memory_manager.h>
#include <process.h>

list_ptr new_linked_list(int (*comp_funct)(void *, void *)) {
    list_ptr my_list = (list_ptr) mem_alloc(sizeof(list_t));
    my_list->start = NULL;
    my_list->end = NULL;
    my_list->size = 0; 
    my_list->comp_funct = comp_funct;
    return my_list;
}

void *find(list_t *list, void *data, int (*comp_funct)(void *, void *)) {
    int (*funct)(void *, void *);
    if (comp_funct == NULL) {
        funct = list->comp_funct;
    }
    else {
        funct = comp_funct;
    }
    node_ptr node = list->start;
    while (node != NULL) {
        if (funct(node->data, data))
            return node->data;
        node = node->next;
    }
    return NULL;
}

void *remove_node(list_ptr list, node_ptr node) {
	if (list == NULL || node == NULL)
		return NULL;

	if (list->start == node) list->start = node->next;
	else node->prev->next = node->next;

	if (list->end == node)
		list->end = node->prev;
	else
		node->next->prev = node->prev;

	list->size--;
	void *data = node->data;
	node->next = NULL;
	node->prev = NULL;
	free(node);
	return data;
}

node_ptr append_node(list_ptr list, node_ptr node) {
	if (list == NULL)
		return NULL;
	node->next = NULL;
	if (list->size > 0)
		list->end->next = node;
	else
		list->start = node;
	node->prev = list->end;
	list->end = node;
	list->size++;
	return node;
}

node_ptr prepend_node(list_ptr list, node_ptr node) {
	if (list == NULL)
		return NULL;
	node->prev = NULL;
	if (list->size > 0)
		list->start->prev = node;
	else
		list->end = node;
	node->next = list->start;
	list->start = node;
	list->size++;
	return node;
}

static node_ptr create_node(void *data, node_ptr prev_node) {
    node_ptr new_node = (node_ptr)mem_alloc(sizeof(node_t));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = prev_node;
    return new_node;
}

void to_begin(list_ptr l) {
    l->current = l->start;
}

int has_next(list_ptr l) {
    return l->current != NULL;
}

int size_list(list_ptr l) {
    return l->size;
}

void *next(list_ptr l) {
    if (!has_next(l)) return NULL;
    void *element = l->current->data;
    l->current = l->current->next;
    return element;
}

node_ptr add(list_ptr list, void *data) {
    node_ptr new_node = create_node(data, list->end);

    if (list->start == NULL) {
        list->start = new_node;
        list->end = new_node;
    }
    else {
        list->end->next = new_node;
        list->end = list->end->next;
    }

    list->size++;
    return new_node;
}

static void free_list_helper(node_ptr node) {
    if (node == NULL) {
        return;
    }
    free_list_helper(node->next);
    free(node);
}

void free_list(list_ptr list) {
    free_list_helper(list->start);
    free(list);
}

node_ptr get_first(list_ptr list) {
	if (list == NULL)
		return NULL;
	return list->start;
}

int is_empty(list_ptr list) {
	if (list == NULL)
		return -1;
	return !list->size;
}

int get_length(list_ptr list) {
	if (list == NULL)
		return -1;
	return list->size;
}