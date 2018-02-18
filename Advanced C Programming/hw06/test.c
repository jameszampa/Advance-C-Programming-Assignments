#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void func(int max, ...);

int main (int argc, char* argv[])
{
	func(2, 15, 17);
	return EXIT_SUCCESS;
}

void func(int max, ...)
{
	va_list args;
	va_start (args, max);

	for(int i = 0; i < max; i++)
	{
		int next_i = va_arg(args, int);
		printf("%d\n", next_i);
	}

	va_end(args);
}
