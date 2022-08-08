#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef B_TREE
#define B_TREE
#include "btree.h"
#endif

#include "utility.h"

char* getval(char* fname, int n){
    FILE* fp = fopen(fname, "r");
    char* value = malloc(100 * sizeof(char));

    char buff[100], inp[100];
    char c;

    char s_num[5];
    sprintf(s_num, "%d", n);
    fscanf(fp, "%s", buff);

    if(strcmp(s_num, buff) == 0){
        fgets(buff, 100, fp);
        strncat(value, buff+1, strlen(buff)-3);
        value[strlen(value)+1] = '\0';
        return value;
    }

    while(!feof(fp)){
        c = fgetc(fp);

        if(c == '\n'){
                  
            fscanf(fp, "%s", buff);

            if(strcmp(s_num, buff) == 0){
                // strcpy(value, "");
                fgets(buff, 100, fp);
                strncat(value, buff+1, strlen(buff)-3);
                value[strlen(value)+1] = '\0';

                fclose(fp);
                return value;
            }
        }

    }

    return value;
}

void insertfirstK(btree* bt, int n){
    int key;
    btree root = *bt;
    FILE* fp = fopen("data.txt", "r");
    char* value;
    keyval* kv;
    printf("Keys: %d\n", n);


    for(int i=0; i<n; i++){
        fscanf(fp, "%d", &key);

        value = malloc(100*sizeof(char));
        char buff[100];

        fgets(buff, 100, fp);
        strncpy(value, buff + 1, strlen(buff)-2);
        kv = malloc(sizeof(keyval));
        kv->key = key;
        kv->val = value;
        printf("%d %s\n", kv->key, kv->val);
        insert(bt, root, NULL, key, kv);
    }

    return;
}