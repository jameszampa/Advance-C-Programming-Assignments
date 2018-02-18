#ifndef MAZE_H
#define MAZE_H 

#define WALL 'X'
#define PATH ' '
#define VISITED '.'

#include <stdio.h>

typedef struct {
   int n_row;
   int n_col;
   char **maze_array;  
} Maze;

typedef struct {
   int row;
   int col;
} Coord;


int dfs_shortest_path_directions(char *maze_file, char *directions_file,
                        Coord source, Coord destination)
		 	__attribute__((nonnull));

int simulate_movement(char *maze_file, char *directions_file, char *visited_file,
                      Coord source, Coord destination)
			__attribute__((nonnull));

#endif
