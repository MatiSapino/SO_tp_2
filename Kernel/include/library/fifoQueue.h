#ifndef _FIFOQUEUE_H_
#define _FIFOQUEUE_H_

#include <memory_manager.h>

typedef struct node
{
    void *data;
    struct node *next;
} node_t;

typedef struct fifo_queue
{
    node_t *front;
    node_t *rear;
} fifo_queue;

typedef struct fifo_queue * fifo_queue_ptr;
typedef struct node  * node_ptr;

fifo_queue_ptr new_fifo_queue();
node_ptr create_node();
void enqueue(fifo_queue_ptr queue, void *data);
void *dequeue(fifo_queue_ptr queue);

#endif