#ifndef MQ_H_
#define MQ_H_

struct node 
{
    struct node* next;
    int *cs;
};
typedef struct node node_t;

void enqueue(int *cs);
 int* dequeue();

#endif