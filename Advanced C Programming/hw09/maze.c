#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "maze.h"

void find_maze_dimensions(FILE * fp, int * a_num_rows, int * a_num_cols) 
{
    *a_num_rows = 0;
	
    char ch = '0';

	*a_num_cols = 0;

	bool first_row = true;
	
    while(ch != EOF)
	{
		ch = fgetc(fp);

		if(ch == '\n')
		{
			*a_num_rows += 1;
			first_row = false;
		}

		if(first_row == true)
		{
			*a_num_cols += 1;
		}
	}
	rewind(fp);
}

int find_opening_location(FILE * fp) 
{
	char ch = '0';
	int loc = 0;

	while(ch != PATH)
	{
		ch = fgetc(fp);
		loc++;
	}
	
	rewind(fp);

    return loc - 1;
}

int count_path_locations(FILE * fp) 
{
	char ch = '0';
	int paths = 0;

	while(ch != EOF)
	{
		ch = fgetc(fp);

		if(ch == PATH)
		{
			paths++;
		}
	}
	rewind(fp);
    return paths;
}

char get_location_type(FILE * fp, int row, int col) 
{
	char ch = '0';
	int i = 0;
	
	int r = 0;
	int c = 0;

	int* a_r = &r;
	int* a_c = &c;

	find_maze_dimensions(fp, a_r, a_c);

	while(i < row * (*a_c + 1) + col + 1)
	{
		ch = fgetc(fp);
		i++;
	}	
		
	rewind(fp);
	
	if(row < *a_r && col < *a_c)
	{
		return ch;
	}
	else
	{
		return '?';
	}
}
 
int represent_maze_in_one_line(char * filename, FILE * fp) 
{
	FILE* new_fp = fopen(filename, "w");
	
	char ch = '0';
	int chars_written = 0;

	while(ch != EOF)
	{
		ch = fgetc(fp);
		if(ch != '\n' && ch != EOF)
		{
			fputc(ch, new_fp);
			chars_written += 1;
		}
	}
	
	rewind(fp);

	fclose(new_fp);

    return chars_written;
}
