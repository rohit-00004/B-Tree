typedef struct queue_node{
    node* bt_node;
    struct queue_node* next;
}* queue;

typedef struct queue_node queue_node;

void init_queue(queue* q);
void enqueue(queue* q, node* n);
int isQempty(queue q);
node* front(queue q);
void dequeue(queue* q);
int qSize(queue q);