#ifndef HUFFMAN_H
#define HUFFMAN_H 


typedef struct _Node {
   void *ptr;
   struct _Node *next;
} Node;


Node *pq_enqueue(Node **pq, const void *new_object, 
                  int (*cmp_fn)(const void *, const void *));

                       
Node *pq_dequeue(Node **pq);


Node *stack_push(Node **stack, const void *new_object);

                       
Node *stack_pop(Node **stack);


Node *remove_last_node(Node **list);


void destroy_node(Node *list, void (*destroy_fn)(void *));

 
void print_node(const Node *list, void (*print_fn)(const void *));


Node *__pq_enqueue(Node **pq, const void *new_object, 
                  int (*cmp_fn)(const void *, const void *));

Node *__pq_dequeue(Node **pq);
Node *__stack_push(Node **stack, const void *new_object);
Node *__stack_pop(Node **stack);
Node *__remove_last_node(Node **list);
void __destroy_node(Node *list, void (*destroy_fn)(void *));
void __print_node(const Node *list, void (*print_fn)(const void *));

#endif

