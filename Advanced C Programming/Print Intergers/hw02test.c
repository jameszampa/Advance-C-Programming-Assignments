#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "hw02.h"


int main (int args, char* argv[])
{
	print_integer(INT_MAX, 2, "");
	
	fputc('\n', stdout);
	
	print_integer(INT_MIN, 2, "");
	
	fputc('\n', stdout);

	print_integer(0, 10, "");
	
	fputc('\n', stdout);

	print_integer(INT_MAX, 16, "0x");
	
	fputc('\n', stdout);

	print_integer(INT_MIN, 16, "0x");

	fputc('\n', stdout);

	print_integer(0, 2, "");

	fputc('\n', stdout);

	print_integer(36, 36, "");

	fputc('\n', stdout);

	print_integer('z', 36, "");


	return EXIT_SUCCESS;
}
