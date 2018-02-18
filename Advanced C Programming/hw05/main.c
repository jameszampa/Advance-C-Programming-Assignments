#include <stdio.h>
#include <stdlib.h>
#include "aux.h"
#include "util.h"
#include "fourier.h"

int main(int argc, char ** argv) {

   if(argc != 6)
   {
      return EXIT_FAILURE;
   }

   int func = atoi(argv[1]); // first input which 

   double (*func_to_be_integrated)(double) = NULL;
   
   if(func == 1)
   {
      func_to_be_integrated = unknown_function_1;
   }
   else if(func == 2)
   {
      func_to_be_integrated = unknown_function_2;
   }
   else if(func == 3)
   {
      func_to_be_integrated = unknown_function_3;
   }
   else
   {
      return EXIT_FAILURE;
   }

   int intervals = atoi(argv[4]);

   if(intervals < 1)
   {
      intervals = 1;
   }
   int coefs = atoi(argv[5]);

   if(coefs < 1)
   {
      coefs = 1;
   }

   Integrand integrand = {
	   .upper_limit = atof(argv[3]),  // TODO: change to the real value
	   .lower_limit = atof(argv[2]), // TODO: change to the real value
	   .n_intervals = intervals,    // TODO: change to the real value
	   .func_to_be_integrated = func_to_be_integrated
   };

   int n_terms = coefs;         // TODO: change to the real value

   Fourier fourier = {
	   .intg      = integrand,
	   .n_terms   = n_terms,
	   .a_i       = malloc(sizeof(*fourier.a_i) * n_terms),
	   .b_i       = malloc(sizeof(*fourier.b_i) * n_terms)
   };

   // If allocation of fourier.a_i and/or fourier.b_i failed, then free the
   // one that didn't fail and then exit with EXIT_FAILURE.
   if (fourier.a_i == NULL || fourier.b_i == NULL) {
      free(fourier.a_i);  // free(..) has not effect if its argument is NULL
      free(fourier.b_i);
      return EXIT_FAILURE;
   }

   if(integrand.upper_limit == integrand.lower_limit)
   {
      return EXIT_FAILURE;
   }


   fourier_coefficients(fourier);

   print_fourier_coefficients(fourier.a_i, fourier.b_i, 
                              fourier.n_terms);

   function_plot(fourier.intg.func_to_be_integrated, integrand.lower_limit, integrand.upper_limit, fourier.a_i, fourier.b_i, fourier.n_terms,"gg.m");

   free(fourier.a_i);
   free(fourier.b_i);

   return EXIT_SUCCESS;
} 
