#include <stdio.h>
#include <math.h>

double function_to_be_integrated(double m);

double function_to_be_integrated(double m)
{
	double integrand = m*m;

	return integrand; 
}
