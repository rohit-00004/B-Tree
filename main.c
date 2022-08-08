#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "btree.h"
#include "queue.h"
#include "utility.h"

/*
    Name: Rohit Magar
    MIS: 112003079
    DSA 2 MINI PROJECT (B-Tree)
*/

int main(){
    btree bt;
    init_btree(&bt);
    FILE* fp = fopen("data.txt", "r");
    
    if(!fp){
        fprintf(stdout, "File not found\n");
        return 0;
    }

    printf("1. Insert keys from input file\n");
    printf("2. Insert random keys from input file\n");
    printf("3. Insert a key from input file\n");
    printf("4. Insert a key-val\n");
    printf("5. Search for a key\n");
    printf("6. Get level-order-traversal of the btree\n");
    printf("7. Get traversal of the btree\n");


    bool cont = 1;

    while(cont){
        printf("Your choice: ");
        int ch;
        scanf("%d", &ch);
        int keys, key;
        keyval* kv;
        FILE* fp;

        switch(ch){
            case 1:
                printf("Enter number of keys to be inserted: ");
                scanf("%d", &keys);
                for(int i=1; i<=keys; i++){
                    int d = rand() % 200;
                    kv = malloc(sizeof(keyval));
                    kv->key = i;
                    kv->val = getval("data.txt", i);
                    insert(&bt, bt, NULL, i, kv);
                }
                printf("Inserted %d keys\n", keys);
                break;

            case 2:
                printf("Enter number of keys to be inserted: ");
                scanf("%d", &keys);
                for(int i=1; i<=keys; i++){
                    int d = rand() % 200;
                    kv = malloc(sizeof(keyval));
                    kv->key = d;
                    kv->val = getval("data.txt", d);
                    insert(&bt, bt, NULL, d, kv);
                }
                // insertfirstK(&bt, key);
                printf("Inserted random %d keyvalues\n", keys);
                break;

            case 3:
                printf("Enter key: ");
                scanf("%d", &key);
                keyval* kv = malloc(sizeof(keyval));
                kv->key = key;
                kv->val = getval("data.txt", key);
                insert(&bt, bt, NULL, kv->key, kv);
                printf("Inserted %d\n", key);
                break;
            
            case 4:
                kv = malloc(sizeof(keyval));
                kv->val = (char*)malloc(50*sizeof(char));
                printf("Enter key: ");
                scanf("%d", &kv->key);
                printf("Enter value: ");
                fgetc(stdin);
                fgets(kv->val, 50, stdin);
                // scanf("%s", kv->val);
                insert(&bt, bt, NULL, kv->key, kv);
                break;
            
            case 5:
                printf("Key to be searched: ");
                scanf("%d", &key);
                printf("%s\n", search(bt, key));
                break;
            
            case 6: 
                fp = fopen("level_traversal.txt", "w");
                level_order(bt, &fp);
                fclose(fp);
                printf("Btree was written in level_traversal.txt file\n");
                break;
            
            case 7:
                fp = fopen("traversal.txt", "w");
                traverse(bt, &fp);
                fclose(fp);
                printf("Btree was written in traversal.txt file\n");
                break;
            
            default:
                printf("Invalid choice\n");
        }
        char c;
        printf("\nPress 1 to continue... ");
        scanf(" %c", &c);
        
        if(c != '1') cont = 0;
    }


    // for(int i=1; i<=50; i++){
    //     keyval* kv = malloc(sizeof(keyval));
    //     kv->key = i;
    //     kv->val = getval("data.txt", i);

    //     insert(&bt, bt, NULL, i, kv);
    // }
    // FILE* fpp = fopen("ans.txt", "w");

    // traverse(bt, &fpp);

    //traversal will be stored in a file
    // level_order(bt, &fpp);
    // fclose(fpp);
    // fclose(fp);
    return 0;
}

// insert(&bt, bt, NULL, 5);
    // insert(&bt, bt, NULL, 20);
    // insert(&bt, bt, NULL, 11);
    // insert(&bt, bt, NULL, 26);
    // insert(&bt, bt, NULL, 30);
    // insert(&bt, bt, NULL, 40);
    // insert(&bt, bt, NULL, 35);
    // insert(&bt, bt, NULL, 38);
    // insert(&bt, bt, NULL, 27);
    // insert(&bt, bt, NULL, 28);
    // insert(&bt, bt, NULL, 29);
    // insert(&bt, bt, NULL, 45);
    // insert(&bt, bt, NULL, 50);
    // insert(&bt, bt, NULL, 52);
    // insert(&bt, bt, NULL, 54);
    // insert(&bt, bt, NULL, 56);
    // insert(&bt, bt, NULL, 31);
    // insert(&bt, bt, NULL, 32);
    // insert(&bt, bt, NULL, 33);
    // insert(&bt, bt, NULL, 6);
    // insert(&bt, bt, NULL, 7);
    // insert(&bt, bt, NULL, 39);
    // insert(&bt, bt, NULL, 57);
    // insert(&bt, bt, NULL, 23);
    // insert(&bt, bt, NULL, 12);
    // insert(&bt, bt, NULL, 24);
    // insert(&bt, bt, NULL, 25);
    // insert(&bt, bt, NULL, 8);
    // insert(&bt, bt, NULL, 22);
    // insert(&bt, bt, NULL, 13);
    // insert(&bt, bt, NULL, 14);
    // traverse(bt);