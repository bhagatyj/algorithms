
/*

Queue using Linked Lists:


  --------
 |  head  |-----> NULL
 |--------|
 |  tail  |-----> NULL
  --------


  --------
 |  head  |---------.
 |--------|         |
 |  tail  |-----.   |
  --------      |   |
                v   V
              --------
             |  next  | ---> NULL
             |--------|
             |  it 1  |
              --------


  --------
 |  head  |---------------------.
 |--------|                     |
 |  tail  |-----.               |
  --------      |               |
                v               V
              --------       --------
             |  next  |---->|  next  | ---> NULL
             |--------|     |--------|
             |  it 1  |     |  it 2  |
              --------       --------


*/

#include "queue.h"

typedef struct __queueNode__ {
    void * item;
    struct __queueNode__ *next;
} queueNode;

typedef struct __queue__ {
    queueNode *head;
    queueNode *tail;
    int count;
} queue;


void * createQueue()
{
    queue *q;

    q = (queue *)malloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;
    q->count = 0;
    return (void *)q;
}


void enqueue(void *qp, void *item)
{
    queueNode *node;
    queue *q = (queue *)qp;

    node = (queueNode *) malloc(sizeof(queueNode));
    node->item = item;
    node->next = NULL;

    if (q->head) {
        q->head->next = node;
    }
    q->head = node;
    if (q->tail == NULL) {
        q->tail = node;
    }

    q->count++;
}

void * dequeue(void *qp)
{
    queueNode *node;
    void *item;
    queue *q = (queue *)qp;

    if (q->count == 0) {
        return NULL;
    }

    node = q->tail;
    q->tail = node->next;

    if (q->head == node) {
        q->head = NULL;
    }

    q->count--;
    item = node->item;
    free(node);

    return item;
}

void deleteQueue(void *qp)
{
    queue *q = (queue *)qp;
    while (q->head) {
        dequeue(q);
    }
    free(q);
}


int size(void *qp)
{
    return ((queue *)qp)->count;
}
