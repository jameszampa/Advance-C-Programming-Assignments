#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

int main(int argc, char* argv[]) 
{
	Maze* maze;

	FILE* fp = fopen("sample.2.7x9", "r");

	maze = read_maze(fp);

	bool success = write_maze("a.txt", maze);

	printf("success: %d\n", success);	

	Maze* maze2 = make_wider(maze);

	success = write_maze("c.txt", maze2);
	
	Maze* maze3 = make_taller(maze2);

	success = write_maze("d.txt", maze3);
    
	free_maze(maze);
	free_maze(maze2);
	free_maze(maze3);
	fclose(fp);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
