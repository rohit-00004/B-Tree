#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#ifndef B_TREE
#define B_TREE
#include "btree.h"
#endif

#ifndef QUEUE
#define QUEUE
#include "queue.h"
#endif

node* newnode(){
    node* nn = malloc(sizeof(node));
    nn->filled_nodes = 0;
    
    for(int i=0; i<=fix_deg; i++){
        nn->childpointers[i] = (node*)malloc(sizeof(node));
        nn->childpointers[i]->filled_nodes = 0;
    }

    return nn;
}

void init_btree(btree* bt){
    *bt = NULL;
    return;
}

bool isSplitreq(node* x, int key){
    if(x->filled_nodes < fix_deg-1) return 0;

    if(x->leaf){
        if(x->filled_nodes < fix_deg-1) return 0;
        return 1;
    }

    int j = x->filled_nodes-1;
    while(j>=0 && x->keys[j]->key > key)
        j--;

    j++;

    return isSplitreq(x->childpointers[j], key);
}

void multiplesplit(btree* root, node* par, node* child, int child_idx, keyval** kv){
    if(child->leaf){
        int k = child->filled_nodes-1;

        while(k>=0 && child->keys[k]->key > (*kv)->key){
            child->keys[k+1] = child->keys[k];
            k--;
        }
        child->keys[k+1] = *kv;

        *kv = child->keys[fix_deg / 2];

        // shifting keys to left
        for(int i=fix_deg/2; i < fix_deg - 1; i++) 
            child->keys[i] = child->keys[i+1];

        node* new_ch = newnode();
        new_ch->leaf = 1;

        // copy into new child, from the middle half
        for(int i=0; i<fix_deg/2; i++){
            new_ch->keys[i] = child->keys[i + fix_deg/2];
        }

        // inserting mid at right pos in parent
        k = par->filled_nodes-1;
        while(k>=0 && par->keys[k]->key > (*kv)->key){
            par->keys[k+1] = par->keys[k];
            k--;
        }

        for(int i=par->filled_nodes; i>child_idx; i--)
            par->childpointers[i+1] = par->childpointers[i];

        par->keys[k+1] = *kv;
        child->filled_nodes = new_ch->filled_nodes = fix_deg / 2;

        par->childpointers[child_idx + 1] = new_ch;
        // or just call Split Child....naa parent is full
        return;
    }

    int j = child->filled_nodes-1;

    while(j >= 0 && child->keys[j]->key > (*kv)->key)
        j--;
    j++;

    multiplesplit(root, child, child->childpointers[j], j, kv);

    // it will now have the element inserted beforehand, just split
    if(!par){
        node* new_child = newnode();
        new_child->leaf = child->leaf;

        node* nr = newnode();
        nr->leaf = 0;

        for(int i=0; i<fix_deg/2; i++){
            new_child->keys[i] = child->keys[i + fix_deg/2 + 1];
        }
        
        for(int i=0; i<=fix_deg/2; i++){
            new_child->childpointers[i] = child->childpointers[i + fix_deg/2 + 1];
        }
        child->filled_nodes = new_child->filled_nodes = fix_deg/2;

        *root = nr;
        nr->keys[0] = child->keys[fix_deg/2];
        nr->filled_nodes++;
        nr->childpointers[0] = child;
        nr->childpointers[1] = new_child;
    }
    else{
        // insert kv into mid of parent and split current child
        node* new_child = newnode();
        new_child->leaf = 0;

        int c ;
        
        c = par->filled_nodes-1;
        while(c>=0 && par->keys[c]->key > child->keys[fix_deg/2]->key){
            par->keys[c+1] = par->keys[c];
            c--;
        }
        c++;
        par->keys[c] = child->keys[fix_deg/2];
        par->filled_nodes++;

        for(int i=par->filled_nodes; i>c; i--)
            par->childpointers[i+1] = par->childpointers[i];

        for(int i=0; i<fix_deg/2; i++)
            new_child->keys[i] = child->keys[i + fix_deg/2 + 1];
        
        for(int i=0; i<=fix_deg/2; i++)
            new_child->childpointers[i] = child->childpointers[i + fix_deg/2 + 1];
        
        new_child->filled_nodes = child->filled_nodes = fix_deg/2;
       
        par->childpointers[c+1] = new_child;
    }
    
}

void insert(btree* root, node* x, node* par, int d, keyval* kv){

    if(!x){
        node* nr = newnode();
        nr->keys[0] = kv;
        nr->leaf = 1;
        nr->filled_nodes++;

        *root = nr;
        return;
    }
    if(x->leaf){
        if(x->filled_nodes == fix_deg - 1){ // new root will be created
            // the only node present which is full
            node* nr = newnode();
            nr->leaf = 0;
            
            //insert into node first, then shift its mid to nr[0]
            int j = x->filled_nodes - 1;

            while(j>=0 && x->keys[j]->key > d){
                x->keys[j+1] = x->keys[j];
                j--;
            }
            j++;
            x->keys[j] = kv;

            nr->keys[0] = x->keys[fix_deg / 2];
            nr->filled_nodes++;
            *root = nr;

            //shifting keys of x towards left
            for(int i=fix_deg / 2; i<fix_deg-1; i++){
                x->keys[i] = x->keys[i+1];
            }

            nr->childpointers[0] = x;
            
            // split x
            node* new_child = newnode();
            new_child->leaf = 1;
            
            for(int i=0; i<fix_deg / 2; i++){
                new_child->keys[i] = x->keys[i + fix_deg / 2];
            }

            x->filled_nodes = new_child->filled_nodes = fix_deg / 2;

            nr->childpointers[1] = new_child;
        }
        else{
            // just insert
            int j = x->filled_nodes - 1;
            while(j >= 0 && x->keys[j]->key > kv->key){
                x->keys[j+1] = x->keys[j];
                j--;
            }

            j++;
            x->keys[j] = kv;
            x->filled_nodes++;
        }
    }
    else{
        int j = x->filled_nodes - 1;
        while(j >= 0 && x->keys[j]->key > kv->key){
            j--;
        }
        j++;

        int splitted = 0;
        if(x->childpointers[j]->filled_nodes == fix_deg - 1){
            // printf("Child full %d\n",d);
            
            splitted = 0;

            if(x->filled_nodes == fix_deg-1){
                if(isSplitreq(x, kv->key)){
                splitted = 1;
                // printf("multiple Splitted\n");
                multiplesplit(root, par, x, j, &kv);
                }                
            }

            else if(x->childpointers[j]->leaf) {
                // printf("Splitted %d\n", kv->key);
                SplitChild(x, x->childpointers[j], kv, j);
                splitted = 1;
            }
            // i=0, if mid > k i++
            //then again call to insert (remove if!splitted)
        }
        // insert(x->child[j])
        if(!splitted)
        insert(root, x->childpointers[j], x, d, kv);
    }

}

void SplitChild(node* par, node* child, keyval* kv, int child_idx){
    node* new_child = newnode();
    new_child->leaf = child->leaf;

    int k = child->filled_nodes-1;

    while(k >= 0 && child->keys[k]->key > kv->key){
        child->keys[k+1] = child->keys[k];
        k--;
    }

    child->keys[k+1] = kv;
    
    // shifting keys and cps  
    for(int j=par->filled_nodes; j>=child_idx; j--)
        par->keys[j+1] = par->keys[j];

    for(int j=par->filled_nodes; j>=child_idx+1; j--)
        par->childpointers[j+1] = par->childpointers[j];

    par->keys[child_idx] = child->keys[fix_deg / 2];
    par->filled_nodes++;

    // shifting child keys to left
    for(int i=fix_deg/2; i<fix_deg-1; i++)
        child->keys[i] = child->keys[i+1];

    // filling new_child from middle half of child
    for(int i=0; i<fix_deg / 2; i++)
        new_child->keys[i] = child->keys[i + fix_deg / 2];
    
    new_child->filled_nodes = fix_deg / 2;
    child->filled_nodes = fix_deg / 2;

    if(!child->leaf){
        for(int i=0; i<=fix_deg / 2; i++)
            new_child->childpointers[i] = child->childpointers[i + fix_deg / 2];
    }

    par->childpointers[child_idx+1] = new_child;
    
    return;    
}

void traverse(btree bt, FILE** fp){
    int i;
    // fprintf(*fp, "trav: %d\n", bt->filled_nodes);
    for(i=0; i<bt->filled_nodes; i++){
        if(!bt->leaf){ 
            // fprintf(*fp, "child\n");
            traverse(bt->childpointers[i], fp);
        }
        // printf("%d: \n", bt->filled_nodes);
        fprintf(*fp, "%d -> %s\n", bt->keys[i]->key, bt->keys[i]->val);
    }
 
    if(!bt->leaf)
        traverse(bt->childpointers[i], fp);
    
    return;
}

void level_order(btree bt, FILE** fp){
    if(!bt) return;

    queue q;
    init_queue(&q);
    enqueue(&q, bt);
    
    while(!isQempty(q)){
        node* curr = front(q);

        int sz = qSize(q);
        int i;  
        fprintf(*fp, "node: ");
        
            for(i=0; i<curr->filled_nodes; i++){
                if(!curr->leaf)
                    enqueue(&q, curr->childpointers[i]);
                
 
                fprintf(*fp, "%d -> %s, ", curr->keys[i]->key, curr->keys[i]->val);
              
            }
            if(!curr->leaf)
                enqueue(&q, curr->childpointers[i]);

        fprintf(*fp, "\n");
        dequeue(&q);
    }

    return;
}

char* search(btree bt, int k){
    int i=0;
    while(i < bt->filled_nodes && k > bt->keys[i]->key)
        i++;

    // printf("nodes: %d, ", bt->filled_nodes);
    if(i < bt->filled_nodes && bt->keys[i]->key == k){
        return bt->keys[i]->val;
    }
    
    if(bt->leaf)
    return "Key not present";

    return search(bt->childpointers[i], k);
}