
#ifndef _QUEUE_H_
#define _QUEUE_H_


typedef struct Queue Queue;

Queue *queue_construct();
void queue_push(Queue *queue, void *data);
int queue_empty(Queue *queue);
void *queue_pop(Queue *queue);
void queue_destroy(Queue *queue);

#endif