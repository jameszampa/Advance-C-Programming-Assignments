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
// This is the only file you have to include 

double simpson_numerical_integration(Integrand intg_arg)
{
   double integral = 0.0;

   double range = intg_arg.upper_limit - intg_arg.lower_limit;

   if(range < 0)
   {
      range = -range;
   }
   
   double a = 0.0;
   double b = 0.0;

   //double limit = 0.0;

   double increment = range / intg_arg.n_intervals;

   if(intg_arg.upper_limit > intg_arg.lower_limit)
   {
      //limit = intg_arg.upper_limit;
	  a = intg_arg.lower_limit;
   }
   else
   {
      //limit = intg_arg.lower_limit;
	  a = intg_arg.upper_limit;
   }

   /*if(range <= 1 && increment == (1.0 / 7.0))
   {
      for( ; a < limit - increment; a += increment)
	  {
	     b = a + increment;
		 integral += ((b - a) / 6) * (intg_arg.func_to_be_integrated(a) + 4 * intg_arg.func_to_be_integrated((a + b) / 2) + intg_arg.func_to_be_integrated(b));
	  }
   }
   else
   {*/
      for(int index = 0; index < intg_arg.n_intervals; index++)
      {
	     b = a + increment;

         integral += ((b - a) / 6) * (intg_arg.func_to_be_integrated(a) + 4 * intg_arg.func_to_be_integrated((a + b) / 2) + intg_arg.func_to_be_integrated(b));
		 
		 a += increment;
      }
   //}
   return integral;
}
