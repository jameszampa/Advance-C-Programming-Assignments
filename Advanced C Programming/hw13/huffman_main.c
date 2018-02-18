#include <stdlib.h>
#include <string.h>
#include "huffman.h"


int main(int argc, char* argv[]) 
{
	if(argc != 5)
	{
		return EXIT_FAILURE;
	}
	Node* head = NULL;

	_occurances_file(argv[1], "occurances.txt");
	_pq_file("occurances.txt", "pq.txt", &head);
	_output_file_1(&head, argv[2]);
	
	Node* temp = head;
	while(temp != NULL)
	{
		_destroy_tree_node(temp -> tree);
		temp = temp -> next;
	}
	_destroy_node(head);
	
	return EXIT_SUCCESS;
}
