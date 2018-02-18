#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

int find_path_from_top_entrance_to_bottom_exit(char *maze_file, char *directions_file, char *visited_file);

int main(int argc, char* argv[]) 
{  
   if (strcmp("-s", argv[1]) == 0)
   {
      if (argc != 9)
	  { 
         return EXIT_FAILURE; 
      }
	   Coord source = {
		  .row = 0,
		  .col = 0
	   };
	   Coord destination = {
	  	  .row = 0,
		  .col = 0
	   };

	   char* s = "\0";

	   int num = strtol(argv[5], &s, 10);
	   if(strcmp(s, "\0") == 0)
	   {
		   source.row = num;
	   }
	   else
	   {
		   return EXIT_FAILURE;
	   }

	   num = strtol(argv[6], &s, 10);
	   if(strcmp(s, "\0") == 0)
	   {
		   source.col = num;
	   }
	   else
	   {
		   return EXIT_FAILURE;
	   }

	   num = strtol(argv[7], &s, 10);
	   if(strcmp(s, "\0") == 0)
	   {
		   destination.row = num;
	   }
	   else
	   {
		   return EXIT_FAILURE;
	   }
		
	   num = strtol(argv[8], &s, 10);
	   if(strcmp(s, "\0") == 0)
	   {
		   destination.col = num;
	   }
	   else
	   {
		   return EXIT_FAILURE;
	   }
		
       int step_count = simulate_movement(argv[2], argv[3], argv[4], source, destination);
       printf("%d\n", step_count);
   } 
   else if(strcmp("-m", argv[1]) == 0)
   {
	   if(argc != 8)
	   {
		   return EXIT_FAILURE;
	   }
	   	
	   Coord source = 
	   {
	 	   .row = 0,
		   .col = 0
	   };
	   Coord destination = 
	   {
	  	   .row = 0,
		   .col = 0
	   };

	   char* s = "\0";

	   int num = strtol(argv[4], &s, 10);
	   if(strcmp(s, "\0") == 0)
	   {
		   source.row = num;
	   }
	   else
	   {
		   return EXIT_FAILURE;
	   }

	   num = strtol(argv[5], &s, 10);
	   if(strcmp(s, "\0") == 0)
	   {
		   source.col = num;
	   }
	   else
	   {
		   return EXIT_FAILURE;
	   }

	   num = strtol(argv[6], &s, 10);
	   if(strcmp(s, "\0") == 0)
	   {
		   destination.row = num;
	   }
	   else
	   {
		   return EXIT_FAILURE;
	   }
		
	   num = strtol(argv[7], &s, 10);
	   if(strcmp(s, "\0") == 0)
	   {
		   destination.col = num;
	   }
	   else
	   {
		   return EXIT_FAILURE;
	   }

       int count = dfs_shortest_path_directions(argv[2], argv[3], source, destination);
   	   
	   printf("%d", count);

	   return count;
   }
   else
   {
	   return EXIT_FAILURE;
   }
}
