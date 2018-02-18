#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "assert.h"
#include "mintf.h"

void print_integer(int n, int radix, char* prefix)
{
	char digits[32] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e',
					   'f', 'g', 'g', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
					   'u', 'v'};
	int converted_num[33];

	int index = 0;
	int predex = 0;
	unsigned int n_abs = 0;

	if(n < 0)
	{
		n_abs = -n;
		fputc('-', stdout);
	}
	else
	{
		n_abs = n;
	}

	while(n_abs != 0)
	{
		converted_num[index] = n_abs % radix;
		n_abs /= radix;
		index++;
	}
	index--;

	while(prefix[predex] != '\0')
	{
		fputc(prefix[predex], stdout);
		predex++;
	}

	for( ; index >= 0; index--)
	{
		fputc(digits[converted_num[index]], stdout);
	}

	if(n == 0)
	{
		fputc('0', stdout);
	}				   
}

void mintf(const char *format, ...)
{
	int index = 0;

	va_list num_list;		
	va_start (num_list, format);

	while(format[index] != '\0')
	{
		char percent = format[index];
		if(percent == '%')
		{
			char identity = format[index + 1];

			if(identity == 'd')
			{
				int next_arg = va_arg (num_list, int);
				print_integer(next_arg, 10, "");
				index += 2;
			}
			else if(identity == 'x')
			{
				int next_arg = va_arg (num_list, int);
				print_integer(next_arg, 16, "0x");
				index += 2;
			}
			else if(identity == 'b')
			{
				int next_arg = va_arg (num_list, int);
				print_integer(next_arg, 2, "0b");
				index += 2;
			}
			else if(identity == '$')
			{
				double next_arg = va_arg (num_list, double);
				long long int int_next_arg = (int)next_arg;			 // left side of decimal point
				int dec_next_arg = next_arg*100 - int_next_arg*100;  // right side of decimal point
				
				print_integer(int_next_arg, 10, "$");
			    
				fputc('.', stdout);

				if(dec_next_arg < 0)
				{
					dec_next_arg = -dec_next_arg + 1;
				}

				if(dec_next_arg < 10)
				{
					fputc('0', stdout);
				}

				print_integer(dec_next_arg, 10, "");
				index += 2;
			}
			else if(identity == 's')
			{
				char* next_arg = va_arg (num_list, char*);
				int i = 0;
				while(next_arg[i] != '\0')
				{
					fputc(next_arg[i], stdout);
					i++;
				}
				index += 2;
			}
			else if(identity == 'c')
			{
				int next_arg = va_arg (num_list, int);
				char char_next_arg = (char)next_arg;
				fputc(char_next_arg, stdout);
				index += 2;
			}
			else if(identity == '%')
			{
				fputc('%', stdout);
				index += 2;

			}
			else
			{
				fputc('%', stdout);
				index++;
			}
		}
		else
		{
			fputc(format[index], stdout);
			index++;
		}
	}

	va_end (num_list);
}
