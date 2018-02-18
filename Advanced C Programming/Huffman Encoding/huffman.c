#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void output_file_2(Node** pq, char* output)
{
	FILE* fp_output = fopen(output, "w");
	post_order((*pq) -> tree, fp_output);
	fprintf(fp_output, "0");
	fclose(fp_output);
}
void post_order(TreeNode* tree, FILE* fp_output)
{
	if(tree != NULL)
	{
		post_order(tree -> left, fp_output);
		post_order(tree -> right, fp_output);
		if(tree -> ascii == 260)
		{
			fprintf(fp_output, "0");
		}
		else
		{
			fprintf(fp_output, "1%c", tree -> ascii); 
		}
	}
}

void output_file_3(char* input, char* output)
{
	FILE* fp_input = fopen(input, "r");
	FILE* fp_output = fopen(output, "w");

	char temp_ch = '0';
	int counter = 0;
	unsigned int bits = 0;
	unsigned int extracted_bits = 0;

	while(temp_ch != EOF)
	{
		temp_ch = fgetc(fp_input);
		if(temp_ch == EOF && counter != 0)
		{
			while(counter < 8)
			{
				bits = bits | (0 << (8 - counter - 1));
				counter++;
			}
			fputc(bits, fp_output);
		}
		if(temp_ch == '0')
		{
			bits = bits | (0 << (8 - counter - 1)); 
			counter++;
			if(counter == 8)
			{
				fputc(bits, fp_output);
				counter = 0;
				bits = 0;
			}	
		}
		else if(temp_ch == '1')
		{
			bits = bits | (1 << (8 - counter - 1));
			counter++;
			if(counter == 8)
			{
				fputc(bits, fp_output);
				counter = 0;
				bits = 0;
			}
			temp_ch = fgetc(fp_input);
			extracted_bits = temp_ch >> counter; // extract counter most significant bits
			bits = bits | extracted_bits; // add results
			fputc(bits, fp_output);
			bits = (temp_ch & (0xFF >> (8 - counter))) << (8 - counter); // extract least significant bits from ascii
		}	
	}

	fclose(fp_input);
	fclose(fp_output);
}

void _occurances_file(char* input, char* output)
{
	FILE* fp_input  = fopen(input, "r");
	FILE* fp_output = fopen(output, "w");
	char ch         = 0;
	long int occurances  = 0;

	for(int i = 0; i < 256; i++) 
	{
		ch = i;
		occurances = _ascii_occurances(ch, fp_input);
		fprintf(fp_output, "%ld\n", occurances);
	}

	fclose(fp_input);
	fclose(fp_output);
}

void _pq_file(char* ascii_occurances, char* output, Node** pq)
{
	FILE* fp_input  = fopen(ascii_occurances, "r");
	FILE* fp_output = fopen(output, "w");
	
	long int amount = 0;
	int ascii_num   = 0;

	while(!feof(fp_input))
	{
		fscanf(fp_input, "%ld", &amount);

		if(amount != 0)
		{
			_pq_enqueue(pq, amount, ascii_num, NULL, NULL);	
		}

		ascii_num++;
	}
	_print_node(*pq, fp_output);
	
		
	fclose(fp_input);
	fclose(fp_output);
}
void output_file_1(Node** pq, char* output)
{
	FILE* fp_output = fopen(output, "w");

	if((*pq) == NULL)
	{
		fclose(fp_output);
		return;
	}
	
	while((*pq) -> next != NULL)
	{
		Node* pop_node_1 = _pq_dequeue(pq, &pop_node_1);
		Node* pop_node_2 = _pq_dequeue(pq, &pop_node_2);
		_pq_enqueue(pq, pop_node_1 -> tree -> amount + pop_node_2  -> tree -> amount, 260, pop_node_1 -> tree, pop_node_2 -> tree);
		free(pop_node_1);
		free(pop_node_2);
	}

	char* path = malloc(sizeof(*path) * (*pq) -> tree -> amount);

	 _print_output1(fp_output, (*pq) -> tree, path, 0);

	fclose(fp_output);

	free(path);
}
void _print_output1(FILE* fp, TreeNode* tree, char* path, int i)
{
	if(tree -> ascii != 260)
	{
		fprintf(fp, "%c:", tree -> ascii);
		path[i] = '\0';
		fprintf(fp, "%s\n", path);
		return;
	}
	else
	{
		path[i] = '0';
		_print_output1(fp, tree -> left, path, i + 1);
		path[i] = '1';
		_print_output1(fp, tree -> right, path, i + 1);
	}	
}

long int _ascii_occurances(char ch, FILE* fp) // counts the number of occurances of character ch
{
	rewind(fp);
	
	long int occurances = 0;
	char temp_ch = '0';

	while(temp_ch != EOF)
	{
		if(ch == EOF)
		{
			return occurances;
		}
		temp_ch = fgetc(fp);
		if(temp_ch == ch)
		{
			occurances++;
		}
	}
	return occurances;
}

void _destroy_node(Node* list)
{
	if(list == NULL)
	{
		return;
	}
	
	Node* curr = list;
	while(list != NULL)
	{
		curr = list -> next;
		free(list);
		list = curr;
	}
}
void _destroy_tree_node(TreeNode* tree)
{
	if(tree == NULL)
	{
		return;
	}
	_destroy_tree_node(tree -> left);
	_destroy_tree_node(tree -> right);
	free(tree);
	
}

void _print_node(const Node *list, FILE* output)
{
   while (list != NULL) 
   { 
      fprintf(output, "%c:%ld->", list -> tree -> ascii, list -> tree -> amount);
      list = list->next;
   } 
   fprintf(output, "NULL\n");
}
void  _pq_enqueue(Node** pq, long int amount, int ascii, TreeNode* left_node, TreeNode* right_node)
{	
    TreeNode* new_tree_node = malloc(sizeof(*new_tree_node)); 
	new_tree_node -> amount = amount;
	new_tree_node -> ascii  = ascii;
	new_tree_node -> left   = left_node;
	new_tree_node -> right  = right_node;
	Node* new_node = malloc(sizeof(*new_node));
	new_node -> tree = new_tree_node;

	if(*pq == NULL)
	{	
		new_node -> next = NULL;
		*pq = new_node;
		return;
	}
	
	Node* curr      = *pq;
	Node* prev_node = *pq;

	long int first = (*pq) -> tree -> amount;
	if(first - new_node ->  tree -> amount > 0)		
	{
		new_node -> next = *pq;
		*pq              = new_node;
		return;
	}

	bool prev = true;
	
	while(curr != NULL)
	{
		if(curr -> tree -> amount == new_node ->  tree -> amount) // if frequencies are the same
		{
			curr = *pq;
			prev = true;
			prev_node = *pq;
			
			while(new_node -> tree -> amount != curr -> tree -> amount) // find the first node for that frequency
			{
				curr = curr -> next;
				if(prev == false)
				{
					prev_node = prev_node -> next;
				}
				prev = false;
			}
			int first_ascii = curr -> tree -> ascii;
			if(first_ascii == (*pq) -> tree -> ascii && new_node -> tree -> ascii < first_ascii) // if new_node should be first of linked list
			{
				new_node -> next = curr;
				*pq = new_node;
				return;
			}
			if(first_ascii - new_node -> tree -> ascii > 0) // if new_node is first but not beginning of linked list
			{
				new_node -> next = curr;
				prev_node -> next = new_node;
				return;
			}
			else
			{
				curr = *pq;
				prev = true;
				prev_node = *pq;

				while(curr != NULL)
				{
					if(new_node -> tree -> amount == curr -> tree -> amount)
					{
						if(new_node -> tree -> ascii < curr -> tree -> ascii) // if new_node is in the middle of a given frequency
						{
							new_node -> next = curr;
							prev_node -> next = new_node;
							return;
						}
						else if(new_node -> tree -> ascii == curr -> tree -> ascii) // if new_node is a parent node
						{
							Node* check_end = curr;

							while(check_end -> next != NULL)
							{
								check_end = check_end -> next;
							}
							if(new_node -> tree -> ascii == check_end -> tree -> ascii) // if new_node should be last in linked list
							{
								check_end -> next = new_node;
								new_node -> next = NULL;
								return;
							}
							while(new_node -> tree -> ascii == curr -> next -> tree -> ascii) // look to see where the last parent node for this 
							{																  //frequency is insert new parents after that node
								curr = curr -> next;
							}
							new_node -> next = curr -> next;
							curr -> next = new_node;
							return;
						}
						else
						{
							Node* end_ascii = curr;
							while(new_node -> tree -> amount == end_ascii -> tree -> amount)
							{
								if(end_ascii -> next == NULL)
								{
									break;
								}
								if(end_ascii -> next -> tree -> amount != new_node -> tree -> amount)
								{
									break;
								}
								end_ascii = end_ascii -> next;
							}
							if(end_ascii -> tree -> ascii < new_node -> tree -> ascii) // if the last value is a leaf add parent to end of frequencies							{
							{	
								Node* temp = end_ascii -> next;
								end_ascii -> next = new_node;
								new_node -> next = temp;
								
								return;
							}
						}
					}
					if(prev == false)
					{
						prev_node = prev_node -> next;
					}
					curr = curr -> next;
					prev = false;
				
				}
			return;
			}
		}
		
		else if(curr -> tree -> amount - new_node -> tree -> amount > 0)
		{											//If node is somewhere inbetween amount already in list		
			new_node -> next  = curr;
			prev_node -> next = new_node;
			return;
		}
		else
		{	
			Node* end_node = *pq;
			while(end_node -> next != NULL) // finds second to last node
			{
				end_node = end_node -> next;
			}
			if(end_node -> tree -> amount - new_node -> tree -> amount < 0)	//If node should be last in list
			{
				new_node -> next = NULL;
				end_node -> next = new_node;
				return;
			}
		}
		if(prev == false)
		{
			prev_node = prev_node -> next;
		}
		curr = curr -> next;
		prev = false;
	}
    return;
}
Node*  _pq_dequeue(Node** pq, Node** popped_node)  
{
	if(*pq == NULL)
	{
		return NULL;
	}
	Node* temp = *pq;
	*pq = (*pq) -> next;
	temp -> next = NULL;	
	return temp;

}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
