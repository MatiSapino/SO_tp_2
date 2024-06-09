#include <linked_list.h>
#include <pmm.h>

#define ERROR -1
#define SUCCESS 0

list_ptr new_linked_list(int (*comp_funct)(void *, void *)) {
    list_ptr new_list = kmalloc(sizeof(list_t));
    new_list->start = NULL;
    new_list->end = NULL;
    new_list->comp_funct = comp_funct;
    new_list->size = 0;
    return new_list;
}

static node_ptr delete_helper(list_ptr list, node_ptr node, void *data) {
    if (node == NULL) {
        return NULL;
    }
    if (list->comp_funct(node->data, data)) {
        node_ptr ret_node = node->next;
        kfree(node);
        return ret_node;
    }
    node->next = delete_helper(list, node->next, data);
    if (node->next == NULL) {
        list->end = node;
    }
    return node;
}

static node_ptr create_node(void *data) {
    node_ptr new_node = (node_ptr)kmalloc(sizeof(node_t));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void to_begin(list_ptr l) {
    l->current = l->start;
}

int hasNext(list_ptr l){
    return l->current != NULL;
}

int size(list_ptr l) {
    return l->size;
}

void *next(list_ptr l) {
    void *element = l->current->data;
    l->current = l->current->next;
    return element;
}

void add(list_ptr list, void *data) {
    node_ptr new_node = create_node(data);

    if (list->start == NULL) {
        list->start = new_node;
        list->end = new_node;
    } else {
        list->end->next = new_node;
        list->end = list->end->next;
    }

    list->size++;
}

int remove(list_ptr list, void *data)
{
    list->start = delete_helper(list, list->start, data);
    list->size--;
    return SUCCESS;
}

void *find(list_ptr list, void *data, int (*comp_funct)(void *, void *)) {
    int (*funct)(void *, void *);
    if (comp_funct == NULL) {
        funct = list->comp_funct;
    } else {
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

static void free_list_helper(node_ptr node){
    if (node == NULL){
        return;
    }
    free_list_helper(node->next);
    kfree(node);
}

void free_list(list_ptr list){
    free_list_helper(list->start);
    kfree(list);
}
