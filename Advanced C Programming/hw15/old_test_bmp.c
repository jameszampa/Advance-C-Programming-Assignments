#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
int main(int argc, char* argv[]) 
{	
	char* error = NULL;
	char* filename = "6x6_24bit.bmp";
	FILE* fp = fopen(filename, "r");

	BMPImage* bmp_img = NULL;
	bmp_img = read_bmp(fp, &error);

	if(error != NULL || bmp_img == NULL)
	{
		printf("%s", error);
		free(error);
		return EXIT_FAILURE;
	}

	printf("Reading bmp file: %s was successful\n", filename);

	FILE* fp_output = fopen("file_written_from_read_bmp.bmp", "w");

	bool check_write = write_bmp(fp_output, bmp_img, &error);

	if(error != NULL || check_write == false)
	{
		printf("%s", error);
		free(error);
		return EXIT_FAILURE;
	}

	printf("Writing bmp file from read_bmp was successful\n");
	printf("New bmp file name: file_written_from_read_bmp.bmp\n");

	BMPImage* cropped_img = NULL;
	cropped_img = crop_bmp(bmp_img, 1, 1, 5, 5, &error); 

	if(error != NULL || cropped_img == NULL)
	{
		printf("%s", error);
		free(error);
		return EXIT_FAILURE;
	}

	printf("Cropping image: %s was successful\n", filename);
	
	FILE* fp_output_crop = fopen("cropped_file.bmp", "w");

	check_write = write_bmp(fp_output_crop, cropped_img, &error);

	if(error != NULL || check_write == false)
	{
		printf("%s", error);
		free(error);
		return EXIT_FAILURE;
	}
	
	printf("Writing bmp file from cropped image was successful\n");
	printf("New bmp file name: cropped_img.bmp\n");
	
	free_bmp(bmp_img);
	free_bmp(cropped_img);
	fclose(fp);
	fclose(fp_output);
	fclose(fp_output_crop);
	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
