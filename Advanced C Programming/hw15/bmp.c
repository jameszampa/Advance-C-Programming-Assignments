#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include <string.h>

char* _error_string();

char* _error_string(const char* s)
{
	char* s_copy = malloc(sizeof(*s_copy)*strlen(s) + 1);
	strcpy(s_copy, s);
	return s_copy;
}
 
BMPImage* read_bmp(FILE* fp, char** error)
{
	rewind(fp);
	BMPHeader bmp_hdr = {0};
	int hdr = fread(&bmp_hdr, 1, BMP_HEADER_SIZE, fp);

	if(hdr != BMP_HEADER_SIZE)
	{
		*error = _error_string("ERROR: read_bmp failed because fread failed.");
		return NULL;
	}

	if(check_bmp_header(&bmp_hdr, fp) == false)
	{
		*error = _error_string("ERROR: read_bmp failed because the bmp_header was incorrect.");
		return NULL;
	}

	BMPImage* bmp_img = malloc(sizeof(*bmp_img));
	bmp_img -> header = bmp_hdr;
	bmp_img -> data = malloc(sizeof(*(bmp_img -> data)) * bmp_hdr.image_size_bytes);
	
	fseek(fp, BMP_HEADER_SIZE, SEEK_SET);

	int data = fread(bmp_img -> data, 1, bmp_hdr.image_size_bytes, fp);
	
	if(data != bmp_hdr.image_size_bytes)
	{
		*error = _error_string("ERROR: read_bmp failed because fread failed.");
		return NULL;
	}

	return bmp_img; 
} 
bool check_bmp_header(BMPHeader* bmp_hdr, FILE* fp)
{
	rewind(fp);
	int padding = 0;
	int width_bytes = bmp_hdr -> width_px * 3;

	while((width_bytes + padding) % 4 != 0) // Determine number of bytes */
	{										// required for padding */
		padding++;							// the rows */
	}

	int  imagesize = bmp_hdr -> height_px * bmp_hdr -> width_px * 3 + padding * bmp_hdr -> height_px;
	int  size      = imagesize + BMP_HEADER_SIZE;
	
	fseek(fp, 0, SEEK_END);
	int size_fromfile = ftell(fp);
	int imagesize_fromfile = size_fromfile - BMP_HEADER_SIZE;

	bool check1   = bmp_hdr -> type == 0x4d42;
	bool check2   = bmp_hdr -> offset == BMP_HEADER_SIZE;
	bool check3   = bmp_hdr -> dib_header_size == DIB_HEADER_SIZE;
	bool check4   = bmp_hdr -> num_planes == 1; 
	bool check5   = bmp_hdr -> compression == 0;
	bool check6   = bmp_hdr -> num_colors == 0; 
	bool check6_2 = bmp_hdr -> important_colors == 0;
	bool check7   = bmp_hdr -> bits_per_pixel == 24;
	bool check8   = bmp_hdr -> image_size_bytes == imagesize;
	bool check8_2 = bmp_hdr -> size == size;
	bool check8_3 = bmp_hdr -> image_size_bytes == imagesize_fromfile;
	bool check8_4 = bmp_hdr -> size == size_fromfile;
	
	return check1 && check2 && check3 && check4 && check5 && check6 && check6_2  && check7 && check8 && check8_2 && check8_3 && check8_4; 
} 
bool write_bmp(FILE* fp, BMPImage* image, char** error) 
{ 
	rewind(fp);
	int hdr = fwrite(&(image -> header), 1, BMP_HEADER_SIZE, fp); 
	int data = fwrite(image -> data, 1, image -> header.image_size_bytes, fp);

	if(hdr != BMP_HEADER_SIZE)
	{
		*error = _error_string("ERROR: write_bmp failed because fwrite did not write the entire BMP header of image.");
		return false;
	}
	if(data != image -> header.image_size_bytes)
	{
		*error = _error_string("ERROR: write_bmp failed because fwrite did not write the entire data section of image.");
		return false;
	}
	
	return true;
} 
void free_bmp(BMPImage* image) 
{
	free(image -> data); 
	free(image);
}
BMPImage* crop_bmp(BMPImage* image, int x, int y, int w, int h, char** error)
{
	if(x < 0 || y < 0 || w < 0 || h < 0 || image == NULL || image -> header.width_px < w || image -> header.height_px < h || x > image -> header.width_px || y > image -> header.height_px) 
	{
		*error = _error_string("ERROR: crop_bmp failed because inputs were invalid.");
		return NULL;
	}

	BMPImage* new_image = malloc(sizeof(*new_image));
	
	new_image -> header.width_px = w;
	new_image -> header.height_px = h;
	new_image -> header.reserved1 = 0;
	new_image -> header.reserved2 = 0;
	new_image -> header.offset = BMP_HEADER_SIZE;
	new_image -> header.dib_header_size = DIB_HEADER_SIZE;
	new_image -> header.num_planes = 1;
	new_image -> header.type = 0x4d42;
	new_image -> header.bits_per_pixel = 24;
	new_image -> header.compression = 0;
	new_image -> header.x_resolution_ppm = 0;
	new_image -> header.y_resolution_ppm = 0;
	new_image -> header.num_colors = 0;
	new_image -> header.important_colors = 0;

	int padding = 0;
	int width_bytes = new_image -> header.width_px * 3;

	while((width_bytes + padding) % 4 != 0) // Determine number of bytes
	{										// required for padding
		padding++;							// the rows
	}
	
	new_image -> header.size = (width_bytes + padding) * h + BMP_HEADER_SIZE;
	new_image -> header.image_size_bytes = new_image -> header.size - BMP_HEADER_SIZE;
	
	int padding_old = 0;
	int width_bytes_old = image -> header.width_px * 3;

	while((width_bytes_old + padding_old) % 4 != 0) // Determine number of bytes
	{												// required for padding
		padding_old++;								// the rows
	}

	int i = x * 3;
	int j = 0;
	int height_counter = 1;
	int x_fr = image -> header.width_px - w - x; // index from right int pixels
	int y_fb = image -> header.height_px - h - y; // index from bottom in pixels
	if(y_fb > 0)
	{
		i += (width_bytes_old +padding_old)* y_fb;
		height_counter += y_fb;
	}
	
	new_image -> data = malloc(sizeof(*(new_image -> data)) * new_image -> header.image_size_bytes);
	
	while((i < image -> header.image_size_bytes - y * (image -> header.width_px + padding_old)) && (j < new_image -> header.image_size_bytes))
	{
		int condition = (width_bytes_old * height_counter + padding_old * (height_counter - 1) - x_fr * 3) ;
		if(i == condition) 																		  // if at padding of original file,
		{																			   			  // skip old padding and pixels from the left being cropped out
			height_counter++;
			i = i + x * 3 + padding_old + x_fr * 3;
			for(int k = 0; k < padding; k++) 
			{
				new_image -> data[j] = 0;
				j++;
			}
		}
		else
		{
			new_image -> data[j] = image -> data[i];
			i++;
			j++;
		}
	}
	
	return new_image;
}


/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
