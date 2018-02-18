#ifndef FOURIER_H
#define FOURIER_H 

/* you have to define the structure integrand as in HW04           */
/*                                                                 */
/* complete your definition of structure integrand below this line */
/* include the following three fields (and nothing else):          */
/* upper_limit, n_intervals, func_to_be_integrated                 */
/* it is important to have the correct types and field names for us*/
/* to evaluate your functions properly                             */

typedef struct _Integrand {
   double lower_limit;
   double upper_limit;
   int n_intervals;
   double (*func_to_be_integrated)(double);

} Integrand;

/* define your structure integrand above this line */
/* DO NOT make changes at other locations          */
/* DO NOT declare other functions in this file     */

// structure defined by instructor and used in HW05

typedef struct _Fourier {
   Integrand intg;
   double * a_i;
   double * b_i;
   int n_terms;
} Fourier;

// you have to define the following three functions in numint.c

double simpson_numerical_integration(Integrand intg_arg);

double simpson_numerical_integration_for_fourier(Integrand intg_arg, int n, double (*cos_sin)(double));

void fourier_coefficients(Fourier fourier_arg);

#endif
