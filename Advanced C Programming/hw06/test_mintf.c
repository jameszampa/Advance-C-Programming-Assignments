#include <stdio.h>
#include <stdlib.h>
#include "mintf.h"
#include <limits.h>

int main (int argc, char* argv[])
{
	mintf("Hello %d World!", 20);
	printf("\n");
	mintf("Hello %x World!", 20);
	printf("\n");
	mintf("Hello %d World! %x", 20, 99);
	printf("\n");
	mintf("Hello %x World! %d", 20, 99);
	printf("\n");
	mintf("Hello %b World! %x", 20, 99);
	printf("\n");
	mintf("Hello %b World! %d", 20, 99);
	printf("\n");
	mintf("Hello %$ World! %$", 20.00, 99.00);
	printf("\n");
	mintf("Hello %$ World!", 21.99999);
	printf("\n");
	mintf("Hello %$ World!", 21.01);
	printf("\n");
	mintf("Hello %s World!", "test");
	printf("\n");
	mintf("Hello %c World!", 'c');
	printf("\n");
	mintf("Hello %% World!");
	printf("\n");
	mintf("abcdefghijk%slmnopqrstuvwxyz", "");
	printf("\n");
	mintf("", 0);
	printf("\n");
	mintf("Hello %d World! %d", INT_MAX, INT_MIN);
	printf("\n");
	mintf("Hello %$ World! %$", INT_MAX+0.99, INT_MIN-0.99);
	printf("\n");
	mintf("Hello %d World!", 0);
	printf("\n");
	mintf("Hello %x World!", 0);
	printf("\n");
	mintf("Hello %b World!", 0);
	printf("\n");
	mintf("Hello %$ World!", 0.0);
	printf("\n");
	mintf("Hello %s World!", "0");
	printf("\n");
	mintf("Hello %c World!", 0);
	printf("\n");
	mintf("Hello %% World!", 0);
	printf("\n");
	mintf("Hello \n World!");
	printf("\n");
	mintf("bunch %of % stuff% % %% %");
	printf("\n");
	mintf("%c ascii value 128", 128);
	printf("\n");
	mintf("777: %$\n", 777.777);
	mintf("%%%d\n", 50);

	return EXIT_SUCCESS;
}
