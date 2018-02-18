#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
int main(int argc, char* argv[]) 
{	
	char* error = NULL;
	char* filename = "6x6_24bit.bmp";
	FILE* fp = fopen(filename, "r");
	if(fp == NULL)
	{
		error = "File could not be opened.";
		printf("%s", error);
		return EXIT_FAILURE;
	}

	BMPImage* bmp_img = NULL;
	bmp_img = read_bmp(fp, &error);

	if(error != NULL || bmp_img == NULL)
	{
		printf("%s", error);
		free(error);
		return EXIT_FAILURE;
	}

	printf("Reading bmp file: %s was successful\n", filename);

	
	
	filename = "file_written_from_read_bmp.bmp";

	FILE* fp_output = fopen(filename, "w");

	bool check_write = write_bmp(fp_output, bmp_img, &error);

	if(error != NULL || check_write == false)
	{
		printf("%s", error);
		free(error);
		return EXIT_FAILURE;
	} 
	
	printf("Writing bmp file: %s was successful\n", filename); 
	
	
	
	BMPImage* cropped_img = crop_bmp(bmp_img, 1, 1, 5, 5, &error);

	if(error != NULL || cropped_img == NULL)
	{
		printf("%s", error);
		free(error);
		return EXIT_FAILURE;
	}
	
	filename = "6x6_24bit.bmp";
	printf("Cropping image: %s was successful\n", filename);
	
	
	
	filename = "cropped_file.bmp";
	FILE* fp_output_crop = fopen(filename, "w");
	check_write = write_bmp(fp_output_crop, cropped_img, &error);
	if(error != NULL || check_write == false)
	{
		printf("%s", error);
		free(error);
		return EXIT_FAILURE;
	}
	printf("Writing bmp file: %s was successful\n", filename);

	
	free_bmp(bmp_img);
	free_bmp(cropped_img);
	fclose(fp);
	fclose(fp_output);
	fclose(fp_output_crop);
	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
