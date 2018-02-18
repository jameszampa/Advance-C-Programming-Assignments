#ifndef MAZE_H
#define MAZE_H 

#define WALL 'X'
#define PATH ' '

#include <stdio.h>
#include <stdbool.h>

typedef struct _Maze {
   int num_rows; // number of newline characters in the file
   int num_cols; // number of WALL or PATH characters in each row (excludes '\n')
   char** cells; // 2D array; .cells[r][c] is the location (WALL or PATH) at row r, column c
} Maze;

Maze* malloc_maze(int num_rows, int num_cols);

void free_maze(Maze* maze)
			__attribute__((nonnull));

Maze* read_maze(FILE* fp)
			__attribute__((nonnull));

bool write_maze(const char* filename, const Maze* maze)
			__attribute__((nonnull));

Maze* make_taller(const Maze* orig)
			__attribute__((nonnull));

Maze* make_wider(const Maze* orig)
			__attribute__((nonnull));

#endif
