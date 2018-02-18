#ifndef MAZE_H
#define MAZE_H 

#define WALL 'X'
#define PATH ' '
#define MAZE_WRITE_FAILURE -1

/* The __attribute__ mechanism attaches characteristics to function 
   declarations to allow the compiler to perform more error checking.
   In this exercise, all parameters that are storing addresses should 
   be non-NULL.  */

#include <stdio.h>

void find_maze_dimensions(FILE* fp, int* num_rows, int* a_num_cols)
			__attribute__((nonnull));

int find_opening_location(FILE* fp)
			__attribute__((nonnull (1)));

int count_path_locations(FILE* fp)
			__attribute__((nonnull (1)));

char get_location_type(FILE* fp, int row, int col)
			__attribute__((nonnull (1)));

int represent_maze_in_one_line(char* filename, FILE* fp)
			__attribute__((nonnull));

#endif
