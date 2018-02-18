#include <stdio.h>

typedef struct _TreeNode {
	long int amount;
	int ascii;
	struct _TreeNode* left;
	struct _TreeNode* right;
} TreeNode;

typedef struct _Node {
   struct _Node* next;
   struct _TreeNode* tree;
} Node;

void _occurances_file();
long int _ascii_occurances(char, FILE*);
void _pq_file();
void _print_node();
void _pq_enqueue();
void _destroy_node();
Node * _pq_dequeue();
void output_file_1();
void _print_output1();
void _destroy_tree_node();
void post_order();
void output_file_2();
void binary(char**, char);
void output_file_3();
