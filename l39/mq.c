#include "mq.h"
#include <stdlib.h>

node_t* head = NULL;
node_t* tail = NULL;


void enqueue(int *cs)
{
    node_t *newnode = malloc(sizeof(node_t));
    newnode->cs = cs;
    newnode->next = NULL;
    if (tail == NULL)
    {
        head = newnode;
    }else{
        tail->next = newnode;
    }
    tail = newnode;
}

int* dequeue()
{
    if (head == NULL)
    {
        return NULL;
    } else {
        int *result = head->cs;
        node_t *temp = head;
        head = head->next;
        if (head == NULL) {tail = NULL;}
        free(temp);
        return result;
    }
}