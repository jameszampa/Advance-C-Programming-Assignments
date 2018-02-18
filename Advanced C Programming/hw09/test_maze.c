#include <stdio.h>
#include "maze.h"

int main (int argc, char** argv)
{
	int r = 0;
	int c = 0;
	int* a_r = &r;
	int* a_c = &c;
	int opening = 0;
	int paths = 0;
	char type = '0';
	int chars_written = 0;

	FILE* fp = fopen("sample.2.7x9", "r");
	//FILE* fp = fopen("a.txt", "r");

	find_maze_dimensions(fp, a_r, a_c);
	printf("Cols: %d\n", c);
	printf("Rows: %d\n", r);


	opening = find_opening_location(fp);
	printf("Opening: %d\n", opening);

	paths = count_path_locations(fp);
	printf("Paths: %d\n", paths);


	type = get_location_type(fp, 1, 1);
	printf("type: %c\n", type);
	
	chars_written = represent_maze_in_one_line("newsample", fp);
	printf("chars_written: %d\n", chars_written);

	fclose(fp);



	return 0;
}
