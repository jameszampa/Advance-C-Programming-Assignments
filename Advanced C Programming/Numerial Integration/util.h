#ifndef UTIL_H
#define UTIL_H 

#define M_PI 3.141592653589793115997963468544185161590576171875L

void function_plot(double (*original_func)(double), 
                   double lower_limit, double upper_limit,
                   double * a_i, double * b_i, int n_terms,
                   char * filename);

void print_fourier_coefficients(double * a_i, double * b_i, int n_terms);

#endif
