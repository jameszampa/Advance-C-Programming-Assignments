#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
char _get_location_type();
void _find_maze_dimensions();

Maze* malloc_maze(int num_rows, int num_cols)
{
	Maze* maze = malloc(sizeof(*maze));

	maze -> cells = malloc(sizeof(*(maze -> cells)) * num_rows);

	maze -> num_rows = num_rows;
	maze -> num_cols = num_cols;

	for(int i = 0; i < num_rows; i++) 
	{
		maze -> cells[i] = malloc(sizeof(**(maze -> cells)) * num_cols);
	}
	
	if(maze == NULL)
	{
		return NULL;
	}
	else if(maze -> cells == NULL)
	{
		free(maze);
		return NULL;
	}
	else if(maze -> cells[0] == NULL)
	{
		free(maze);
		free(maze -> cells);
		return NULL;
	}
	else
	{
		return maze;
	}
}

void free_maze(Maze* maze)
{
	for(int i = 0; i < maze -> num_rows; i++) 
	{
		free(maze -> cells[i]);
	}
	free(maze -> cells);
	free(maze);
}

Maze* read_maze(FILE* fp)
{
	int  num_rows = 0;
	int  num_cols = 0;
	int* a_r      = &num_rows;
	int* a_c      = &num_cols;

	_find_maze_dimensions(fp, a_r, a_c);

	Maze* maze = malloc_maze(num_rows, num_cols);

	for(int i = 0; i < maze -> num_rows; i++) 
	{
		for(int j = 0; j < maze -> num_cols; j++) 
		{
			maze -> cells[i][j] = _get_location_type(fp, i, j);
		}
	}

	return maze;
}
void _find_maze_dimensions(FILE* fp, int* a_rows, int* a_cols)
{
	char character = '0';
	bool first_row = true;
	*a_rows =  0;
	*a_cols =  0;

	while(character != EOF)
	{
		character = fgetc(fp);

		if(character == '\n')
		{
			*a_rows += 1;
			first_row = false;
		}
		if(first_row == true)
		{
			*a_cols += 1;
		}
	}
	rewind(fp);
}

char _get_location_type(FILE* fp, int row, int col)
{
	char character = '0';
	int  i   = 0;
	int  r   = 0;
	int  c   = 0;
	int* a_r = &r;
	int* a_c = &c;

	_find_maze_dimensions(fp, a_r, a_c);

	while(i < row * (*a_c + 1) + col + 1)
	{
		character = fgetc(fp);
		i++;
	}

	rewind(fp);
	return(character);
}

bool write_maze(const char* filename, const Maze* maze)
{
	FILE* fp = fopen(filename, "w");

	for(int i = 0; i < maze -> num_rows; i++) 
	{
		for(int j = 0; j < maze -> num_cols; j++) 
		{
			fputc(maze -> cells[i][j], fp);
		}
		fputc('\n', fp);
	}

	fclose(fp);
	
	return true;
}

Maze* make_taller(const Maze* orig)
{
	Maze* maze = malloc_maze(orig -> num_rows * 2 - 1, orig -> num_cols); 
	
	maze -> num_rows = orig -> num_rows * 2 - 1;
	maze -> num_cols = orig -> num_cols;

	int i = 0;
	for( ; i < orig -> num_rows; i++)
	{
		for(int j = 0; j < maze -> num_cols; j++) 
		{
			maze -> cells[i][j] = orig -> cells[i][j];
		}
	}

	int q = i;
	int r = orig -> num_rows - 2;
	for( ; q < maze -> num_rows; q++)
	{
		for(int w = 0; w < maze -> num_cols; w++) 
		{
			maze -> cells[q][w] = orig -> cells[r][w];
		}
		r--;
	}

	return maze;
}
Maze* make_wider(const Maze* orig)
{
	Maze* maze = malloc_maze(orig -> num_rows, orig -> num_cols * 2 - 1); 
	
	int i = 0;
	for( ; i < orig -> num_rows; i++)
	{
		for(int j = 0; j < orig -> num_cols; j++) 
		{
			maze -> cells[i][j] = orig -> cells[i][j];
		}
	}

	int r = 0;
	for(int q = 0 ; q < maze -> num_rows; q++)
	{
		r = orig -> num_cols - 2;
		for(int w = orig -> num_cols; w < maze -> num_cols; w++) 
		{
			maze -> cells[q][w] = orig -> cells[q][r];
			r--;
		}
	}
	
	int half = maze -> num_rows / 2;
	int index = orig -> num_cols - 1;

	while((maze -> cells[half - 1][index] != PATH) && (maze -> cells[half + 1][index] != PATH))
	{
		index--;
	}

	int limit = orig -> num_cols - 1 + (orig -> num_cols - index);
	for(i = index; i < limit; i++) 
	{
		maze -> cells[half][i] = PATH;
	}
	
	return maze;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
