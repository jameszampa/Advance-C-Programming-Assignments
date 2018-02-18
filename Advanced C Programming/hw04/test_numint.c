#include <stdio.h>
#include <stdlib.h>
#include "aux.h"
// do not change this part, if you do, your code may not compile
//
/* test for structure defined by student */
#ifndef NTEST_STRUCT 
#include "numint.h"
#else
#include "numint_key.h"
#endif /* NTEST_STRUCT */
//
// do not change above this line, if you do, your code may not compile

      
int main(int argc, char * * argv)
{
   if(argc != 5)
   {
      return EXIT_FAILURE;
   }
   
   int func_num = atoi(argv[1]);

   if(func_num == 1 || func_num == 2 || func_num == 3)
   {
      double (*func_to_be_integrated)(double) = NULL;

	  if(func_num == 1)
	  {
	     func_to_be_integrated = unknown_function_1;
	  }
	  else if(func_num == 2)
	  {
	     func_to_be_integrated = unknown_function_2;
	  }
	  else
	  {
	     func_to_be_integrated = unknown_function_3;
	  }

	  int intervals = atoi(argv[4]);

	  if(intervals < 1)
	  {
	     intervals = 1;
      }

	  Integrand intg_arg = 
	  {
	     .func_to_be_integrated = func_to_be_integrated,
		 .lower_limit = atof(argv[2]),
		 .upper_limit = atof(argv[3]),
		 .n_intervals = intervals
	  }; 

      double integral = simpson_numerical_integration(intg_arg);

      printf("%.10e\n", integral);
	  
      return EXIT_SUCCESS;
   }
   else
   {
      return EXIT_FAILURE;
   }
}
