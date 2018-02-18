#include <stdio.h>
#include "hw02.h"

void print_integer(int n, int radix, char* prefix)
{
	char digits[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u','v', 'w', 'x', 'y', 'z'};
	int converted_num[36] = {0};
	int index = 0;
	int predex = 0;
	long int n_abs = (n < 0 ? -(long int)n : (long int)n);

	if(n < 0) // If negtive print negative sign and switch the signs of n
	{
		fputc('-', stdout);
	}

	do // Looks at each number in n and puts its equivalent base number in an array
	{
		converted_num[index] = n_abs % radix;
		n_abs = n_abs / radix;
		index++;
	} while(n_abs != 0);
	
	while(prefix[predex] != '\0') // prints prefix
	{
		fputc(prefix[predex], stdout);
		predex++;
	}

	for( ; index - 1 >= 0; index--) // prints converted number
	{
		fputc(digits[converted_num[index - 1]], stdout);
	}

	return;
}
	
