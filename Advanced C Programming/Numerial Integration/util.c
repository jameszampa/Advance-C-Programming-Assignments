#include <stdio.h>
#include <math.h>
#include "util.h"
const int N_STEPS = 1000;

double fourier_eval(double lower_limit, double upper_limit,
						  double *a_i, double *b_i, int n_terms, double x) {
	double period = upper_limit - lower_limit;
	double eval = 0.5 * a_i[0];
	for (int i = 1; i < n_terms; i++) {
		eval += a_i[i] * cos(2*i*M_PI*x/period);
		eval += b_i[i] * sin(2*i*M_PI*x/period);
	}
	return eval;
}

void function_plot(double (*original_func)(double),
						 double lower_limit, double upper_limit,
						 double *a_i, double *b_i, int n_terms, char *filename) {
	if (n_terms <= 0) {
		return;
	}

	FILE *fp = fopen(filename, "w");
	if (fp == NULL) {
		return;
	}

	int n_steps = N_STEPS;
	double steps = (upper_limit - lower_limit)/n_steps;
	fprintf(fp, "x = [");
	double llimit = lower_limit;
	for (int i = 0; i < n_steps - 1; i++) {
		fprintf(fp, "%e, ", llimit);
		llimit += steps;
	}
	fprintf(fp, "%e];\n", upper_limit);

	fprintf(fp, "y0 = [");
	llimit = lower_limit;
	for (int i = 0; i < n_steps - 1; i++) {
		fprintf(fp, "%e, ", original_func(llimit));
		llimit += steps;
	}
	fprintf(fp, "%e];\n", original_func(upper_limit));

	fprintf(fp, "y1 = [");
	llimit = lower_limit;
	for (int i = 0; i < n_steps - 1; i++) {
		fprintf(fp, "%e, ", fourier_eval(lower_limit, upper_limit, a_i, b_i,
													n_terms, llimit));
		llimit += steps;
	}
	fprintf(fp, "%e];\n", fourier_eval(lower_limit, upper_limit, a_i, b_i, 
												  n_terms, upper_limit));
	fprintf(fp, "figure\n");
	fprintf(fp, "plot(x,y0,x,y1)\n");
	fclose(fp);
}

void print_fourier_coefficients(double *a_i, double *b_i, int n_terms) {
	if (n_terms <= 0) {
		return;
	}
	printf("%.10e\n", a_i[0]);
	for (int i = 1; i < n_terms; i++) {
		printf("%.10e\n", a_i[i]);
	}
	for (int i = 1; i < n_terms; i++) {
		printf("%.10e\n", b_i[i]);
	}
}
