#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	
	FILE* fp = fopen("shitpost", "w");
	
	int x, y, z;
	x = 8, y = 16, z = 32;

	fwrite(&x, 1, 4, fp);
	fwrite(&y, 1, 4, fp);
	fwrite(&z, 1, 4, fp);

	fclose(fp);
	
	FILE* fp_r = fopen("shitpost", "r");

	fseek(fp_r, 2, SEEK_SET);

	int a = 0;

	FILE* new_fp = fopen("postshit", "w");

	fread(&a, 1, 4, fp_r);
	fwrite(&a, 1, 4, new_fp);

	printf("%d\n", a);

	fclose(new_fp);
	fclose(fp_r);
	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
