#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef B_TREE
#define B_TREE
#include "btree.h"
#endif

#ifndef QUEUE
#define QUEUE
#include "queue.h"
#endif


void init_queue(queue* q){
    *q = NULL;
    return;
}

void enqueue(queue* q, node* n){
    queue_node* p = *q;

    queue_node* nn = malloc(sizeof(queue_node));
    nn->bt_node = newnode();
    nn->bt_node = n;
    nn->next = NULL;

    if(!p){
        *q = nn;
        return;
    }

    while(p->next)
        p = p->next;
    
    p->next = nn;
    return;
}

int isQempty(queue q){
    return q == NULL;
}

node* front(queue q){
    if(!isQempty(q)) return q->bt_node;
    return NULL;
}

void dequeue(queue* q){
    queue_node* to_delete = *q;

    if(!to_delete) return;

    *q = to_delete->next;

    free(to_delete);
    to_delete = NULL;
    return;
}

int qSize(queue q){
    int cnt = 0;

    queue_node* p = q;

    while(p){
        cnt++;
        p = p->next;
    }

    // printf("before leaving %d\n", q->bt_node->keys[0]->key);
   

    return cnt;
}