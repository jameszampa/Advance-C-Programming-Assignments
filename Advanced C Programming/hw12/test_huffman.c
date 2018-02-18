#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

static int int_cmp();
static void int_print();

static int int_cmp(const void* p1, const void* p2)
{
	return *(const int*)p1 - *(const int*)p2;
}
static void int_print(const void* ptr)
{
	printf("%d", *(const int*)ptr);
}

void destroy(void* ptr)
{
}

int main (int argc, char* argv[])
{
	void (*a_fn)() = int_print;
	static int (*a_cmp_fn)(const void*, const void*) = int_cmp;  //Testing pq_enqueue inside list
	
	Node* head = NULL;
	printf("Original Node\n");
	print_node(head, a_fn);
	printf("\n");

	int num4 = 3;
	printf("pq_enqueue (%d)\n", num4);
	Node* new_node = pq_enqueue(&head, &num4, a_cmp_fn);
	printf("Head: ");
	print_node(head, a_fn);
	printf("return: ");
	print_node(new_node, a_fn);
	printf("\n");

	printf("Remove Last Node\n");								//Testing removing last node
	Node* last_node2 = remove_last_node(&head);
	printf("return: ");
	print_node(last_node2, a_fn);
	printf("Head: ");
	print_node(head, a_fn);
	printf("\n");
		
	int num6 = 0;
	printf("pq_enqueue (%d)\n", num6);							//Testing pq_enqueue adding to beginnging of list	
	Node* new_node2 = pq_enqueue(&head, &num6, a_cmp_fn);
	printf("Head: ");
	print_node(head, a_fn);
	printf("return: ");
	print_node(new_node2, a_fn);
	printf("\n");

	int num7 = 10;												//Testing pq_enqueue adding to end of list
	printf("pq_enqueue (%d)\n", num7);
	Node* new_node3 = pq_enqueue(&head, &num7, a_cmp_fn);
	printf("Head: ");
	print_node(head, a_fn);
	printf("return: ");
	print_node(new_node3, a_fn);
	printf("\n");	

	int num9 = 4;
	printf("pq_enqueue (%d)\n", num9);
	Node* new_node4 = pq_enqueue(&head, &num9, a_cmp_fn);
	printf("Head: ");
	print_node(head, a_fn);
	printf("return: ");
	print_node(new_node4, a_fn);
	printf("\n");

	int num5 = 7;												 //Testing Stack Push
	printf("Stack Push (%d)\n", num5);
	Node* list_stack_push = stack_push(&head, &num5);
	printf("return: ");
	print_node(list_stack_push, a_fn);	
	printf("\n");
	
	
	printf("pq_dequeue\n");										//Testing pq_dequeue
	Node* popped_node = pq_dequeue(&head);
	printf("return: ");
	print_node(popped_node, a_fn);
	printf("Head: ");
	print_node(head, a_fn);
	printf("\n");
	
	printf("Remove Last Node\n");								//Testing removing last node
	Node* last_node = remove_last_node(&head);
	printf("return: ");
	print_node(last_node, a_fn);
	printf("Head: ");
	print_node(head, a_fn);
	printf("\n");

	printf("Stack pop\n");										//Testing Stack pop
	Node* stack = stack_pop(&head);
	printf("return: ");
	print_node(stack, a_fn);
	printf("Head: ");
	print_node(head, a_fn);
	printf("\n");

	printf("Stack pop again\n");								
	Node* stack2 = stack_pop(&head);
	printf("return: ");
	print_node(stack2, a_fn);
	printf("Head: ");
	print_node(head, a_fn);
	printf("\n");
		
	printf("Stack pop for empty list\n");						//Testing stack pop until linked list is null
	Node* stack5 = stack_pop(&head);
	printf("return: ");
	print_node(stack5, a_fn);
	printf("Head: ");
	print_node(head, a_fn);
	printf("\n");

	int num8 = 9;
	printf("Stack Push on empty list (%d)\n", num8);
	Node* stack6 = stack_push(&head, &num8);
	printf("return: ");
	print_node(stack6, a_fn);
	printf("Head: ");
	print_node(head, a_fn);
	printf("\n");
	
	printf("pq_dequeue\n");										//Testing pq_dequeue
	Node* popped_node2 = pq_dequeue(&head);
	printf("return: ");
	print_node(popped_node2, a_fn);
	printf("Head: ");
	print_node(head, a_fn);
	printf("\n");


	void (*a_free)() = destroy;
	
	destroy_node(popped_node, a_free);
	destroy_node(popped_node2, a_free);
	destroy_node(last_node, a_free);
	destroy_node(last_node2, a_free);
	destroy_node(stack, a_free);
	destroy_node(stack2, a_free);
	destroy_node(stack5, a_free);
	destroy_node(stack6, a_free);
	destroy_node(list_stack_push, a_free);
	return EXIT_SUCCESS;
}
