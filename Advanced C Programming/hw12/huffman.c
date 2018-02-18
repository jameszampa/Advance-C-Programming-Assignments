#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include <assert.h>
#include <stdbool.h>

Node* pq_enqueue(Node** pq, const void* new_object, int (*cmp_fn)(const void*, const void*))
{
	if(new_object == NULL)
	{
		return NULL;
	}

    Node* new_node = malloc(sizeof(*new_node)); 
	new_node -> amount = amount;

	if(*pq == NULL)
	{	
		new_node -> next = NULL;
		*pq = new_node;
		return new_node;
	}
	
	Node* curr = *pq;
	Node* prev_node = *pq;

	void* first = (*pq) -> ptr;
	if(cmp_fn(first, new_object) >= 0)		//If new_object should be first in list
	{
		new_node -> next = *pq;
		*pq = new_node;
		return new_node;
	}

	bool prev = true;
	
	while(curr != NULL)
	{
		
		if(cmp_fn(curr -> ptr, new_object) >= 0) 	//If new_object is somewhere in the middle of list
		{		
			new_node -> next = curr;
			prev_node -> next = new_node;
			return new_node;
		}
		else
		{
			Node* end_node = *pq;
			while(end_node -> next != NULL) // finds second to last node
			{
				end_node = end_node -> next;
			}
			if(cmp_fn(end_node -> ptr, new_object) <= 0)	//If new_object should be last in list
			{
				new_node -> next = NULL;
				end_node -> next = new_node;
				return new_node;
			}
		}
		if(prev == false)
		{
			prev_node = prev_node -> next;
		}
		curr = curr -> next;
		prev = false;
	}
    return curr;
}

                       
Node* pq_dequeue(Node** pq)  
{
	if(*pq == NULL)
	{
		return NULL;
	}
	Node* popped_node = malloc(sizeof(*popped_node));
	popped_node -> ptr = (*pq) -> ptr;
	popped_node -> next = NULL;

	*pq = (*pq) -> next;

	return popped_node;
}

Node* stack_push(Node **stack, const void *new_object)
{	
	if(new_object == NULL)
	{
		return NULL;
	}

	Node* new_node = malloc(sizeof(*new_node));
	new_node -> next = *stack;
	new_node -> ptr = (void*)new_object;
	*stack = new_node;

    return new_node;
}

                       
Node *stack_pop(Node **stack) 
{
	return pq_dequeue(stack);
}

Node* remove_last_node(Node** list) 
{
	if(*list == NULL)
	{
		return NULL;
	}

	Node* curr = *list;
	while(curr -> next != NULL) // curr represents the last node
	{
		curr = curr -> next;
	}
	Node* removing_node = *list;
	if(removing_node -> next == NULL) // if the node size is 1 set list = null, and return the one node removed
	{
		*list = NULL;
		return curr;
	}
	while(removing_node -> next -> next != NULL) // setting the second to last node next -> NULL;
	{
		removing_node = removing_node -> next;
	}
	removing_node -> next = NULL;
	
	return curr;
}


void destroy_node(Node *list, void (*destroy_fn)(void *)) 
{
	if(list == NULL)
	{
		return;
	}

	Node* curr = list;	
	while(list != NULL)
	{
		curr = list -> next;
		destroy_fn(list -> ptr);
		free(list);
		list = curr;
	}
	assert(list == NULL);

}

/* print an entire linked list                                           */
/* pq is the address of the first Node in the linked list               */
/* print_fn is the address of the function to print the generic object,  */
/* of which the address is stored in the ptr field of an Node in the    */
/* linked list                                                           */
/*                                                                       */
/* DO NOT CHANGE THIS FUNCTION, OTHERWISE YOUR OUTPUT WILL BE DIFFERENT  */
/* AND YOU WILL NOT RECEIVE CREDIT                                       */
 
void print_node(const Node *list, void (*print_fn)(const void *))
{
   while (list != NULL) {
      // print the memory associated with list->ptr
      print_fn(list->ptr);
      // print an arrow
      fprintf(stdout, "->");
      list = list->next;
   } 
   // print NULL and a newline after that 
   fprintf(stdout, "NULL\n");
}

