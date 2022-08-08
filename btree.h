#define fix_deg 5

typedef struct{
    int key;
    char* val;
}keyval;

typedef struct node{
    bool leaf;
    int filled_nodes;
    keyval* keys[fix_deg];
    struct node* childpointers[fix_deg+1];
}* btree;

typedef struct node node;

node* newnode();
void init_btree(btree* bt);
void traverse(btree bt, FILE** fp);
void SplitChild(node* par, node* child, keyval* kv, int child_idx);
bool isSplitreq(node* x, int key);
void multiplesplit(btree* root, node* par, node* child, int child_idx, keyval** kv);
void insert(btree* root, node* x, node* par, int d, keyval* kv);
void level_order(btree bt, FILE** fp);
char* search(btree bt, int k);