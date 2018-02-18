#include <stdio.h>

int main (int argc, char** argv)
{
	for(int i; i < 5; i++)
	{
		printf("%s\n", argv[i]);
	}
	return 0;
}
