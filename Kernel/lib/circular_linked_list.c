#include <circular_linked_list.h>
#include <stdlib.h>

circular_list_ptr new_circular_linked_list(int (*comp_funct)(void *, void *)) {
    circular_list_ptr new_list = (circular_list_ptr)kmalloc(sizeof(list_t));
    new_list->start = NULL;
    new_list->end = NULL;
    new_list->current = NULL;
    new_list->comp_funct = comp_funct; 
    new_list->size = 0;

    for (size_t i = 0; i < MAX_ITERATORS; i++) {
        new_list->iterators[i] = NULL;
    }

    return new_list;
}

static node_ptr create_node(void *data) {
    node_ptr new_node = (node_ptr)kmalloc(sizeof(node_t));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

int cl_size(list_ptr l) {
    return l->size;
}

void cl_add(list_ptr list, void *data) {
    node_ptr new_node = create_node(data);

    if (list->start == NULL) {
        list->start = new_node;
    } else
        list->end->next = new_node;

    list->end = new_node;
    list->end->next = list->start;

    // Notify subscribed iterators
    for (size_t i = 0; i < MAX_ITERATORS; i++) {
        iterator_t *iterator = list->iterators[i];
        if (iterator != NULL) {
            iterator->start = list->start;
            iterator->end = list->end;

            if (iterator->current == NULL)
                iterator->current = list->start;
        }
    }

    list->size++;
}

static node_ptr find_node_before(list_ptr list, void *data) {
    node_ptr aux_node = list->start;

    do {
        if (list->comp_funct(aux_node->next->data, data))
            return aux_node;

        aux_node = aux_node->next;
    } while (aux_node != list->start);

    return NULL;
}

void *cl_remove(list_ptr list, void *data) {
    node_ptr node_before_target = find_node_before(list, data);

    if (node_before_target == NULL)
        return NULL;

    node_ptr target_node = node_before_target->next;

    node_before_target->next = target_node->next;

    if (list->end == target_node)
        list->end = node_before_target;

    if (list->start == target_node)
        list->start = target_node->next;

    // Notify subscribed iterators
    for (size_t i = 0; i < MAX_ITERATORS; i++) {
        iterator_ptr iterator = list->iterators[i];
        if (iterator != NULL) {
            iterator->start = list->start;
            iterator->end = list->end;

            if (iterator->current == target_node)
                iterator->current = target_node->next;
        }
    }

    kfree(target_node);
    list->size--;
    return target_node->data;
}

void *cl_find(list_ptr list, void *data, int (*comp_funct)(void *, void *)) {
    int (*funct)(void *, void *);
    if (comp_funct == NULL) {
        funct = list->comp_funct;
    } else {
        funct = comp_funct;
    }
    node_ptr node = list->start;
    do {
        if (funct(node->data, data))
            return node->data;

        node = node->next;
    } while (node != list->start);
    return NULL;
}

void cl_free_list(circular_list_ptr list) {
    node_ptr node = list->start;
    node_ptr tmp;
    do {
        tmp = node;
        node = node->next;
        kfree(tmp);
    } while (node != list->start);

    kfree(list);
}

circular_list_iterator_ptr new_circular_list_iterator(list_ptr l) {
    circular_list_iterator_ptr new_iterator = (circular_list_iterator_ptr)kmalloc(sizeof(iterator_t));
    new_iterator->start = l->start;
    new_iterator->current = l->start;
    new_iterator->end = l->end;
    new_iterator->visited = 0;
    return new_iterator;
}

void cl_free_iterator(iterator_ptr i) {
    kfree(i);
}

void cl_to_begin(list_ptr l, circular_list_iterator_ptr i) {
    i->start = l->start;
    i->current = l->start;
    i->end = l->end;
    i->visited = 0;
}

int cl_has_next(circular_list_iterator_ptr i) {
    if (i->current == i->start && i->visited) {
        return 0;
    }
    i->visited = 1;
    return 1;
}

void *cl_next(iterator_ptr i) {
    void *data = i->current->data;
    i->current = i->current->next;
    return data;
}

void cl_subscribe_iterator(list_ptr l, iterator_ptr iterator) {
    for (size_t i = 0; i < MAX_ITERATORS; i++) {
        if (l->iterators[i] == NULL)
            l->iterators[i] = iterator;
    }
}

void cl_unsubscribe_iterator(list_ptr l, iterator_ptr iterator) {
    for (size_t i = 0; i < MAX_ITERATORS; i++) {
        if (l->iterators[i] == iterator) {
            l->iterators[i] = NULL;
        }
    }
}