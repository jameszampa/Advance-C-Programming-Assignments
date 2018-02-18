#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "fourier.h"
#define M_PI 3.141592653589793115997963468544185161590576171875L

double simpson_numerical_integration(Integrand intg_arg) {
   double integral = 0.0;
   double range = intg_arg.upper_limit - intg_arg.lower_limit;
   double increment = range / (double)intg_arg.n_intervals;
   double a = intg_arg.lower_limit;
   double b = 0.0;

   for(int index = 0; index < intg_arg.n_intervals; index++)
   {
      b = a + increment;

	  integral += (increment / 6.0) * (intg_arg.func_to_be_integrated(a) + 4.0 * intg_arg.func_to_be_integrated((a + b) / 2.0) + intg_arg.func_to_be_integrated(b));

	  a += increment;
   }

   return integral;
}

double simpson_numerical_integration_for_fourier(Integrand intg_arg, int n, 
                                                 double (*cos_sin)(double)) {
   double integral = 0.0;

   double range = intg_arg.upper_limit - intg_arg.lower_limit;
   double increment = range / (double)intg_arg.n_intervals;

   double a = intg_arg.lower_limit;
   double b = 0.0;

   double L = (intg_arg.upper_limit - intg_arg.lower_limit) / 2.0;

   for(int index = 0; index < intg_arg.n_intervals; index++)
   {
      b = a + increment;

	  double part1 = (b - a) / 6.0;
	  double partLow = intg_arg.func_to_be_integrated(a) * cos_sin((n * M_PI * a) / L);
	  double partMid = intg_arg.func_to_be_integrated((a + b) / 2.0) * cos_sin(n * M_PI * ((a + b) / 2.0) / L);
	  double partHigh = intg_arg.func_to_be_integrated(b) * cos_sin((n * M_PI * b) / L);

	  integral += part1 * (partLow + 4.0 * partMid + partHigh);

	  a += increment;
   }

   return integral;
}

void fourier_coefficients(Fourier fourier_arg) {
   double L = (fourier_arg.intg.upper_limit - fourier_arg.intg.lower_limit) / 2.0;

   fourier_arg.a_i[0]  = (1 / L) * simpson_numerical_integration(fourier_arg.intg);

   for (int i = 1; i < fourier_arg.n_terms; i++) {
	  fourier_arg.a_i[i] = (1 / L) * simpson_numerical_integration_for_fourier(fourier_arg.intg, i, cos);
	  fourier_arg.b_i[i] = (1 / L) * simpson_numerical_integration_for_fourier(fourier_arg.intg, i, sin);
   }
}
