#include "main.h"
#include <stdarg.h>

void print_buffer(char buffer[], int *buffs_ind);
/**
 * _printf - function that produces output according to a format
 * @format: output format
 *
 * by Longinus and emmanuel
 *
 * Return : 0
 */
int _printf(const char *format, ...)
{
	int i, result, output_chars, flags, width, precision, size, buffs_ind;

	buffs_ind = 0;
	result = 0;
	output_chars = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
	{
		return (-1);
	}
	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buffs_ind++] = format[i];
			if (buffs_ind == BUFF_SIZE)
				print_buffer(buffer, &buffs_ind);
			output_chars++;
		}
		else
		{
			print_buffer(buffer, &buffs_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			result = handle_print(format, &i, list, buffer, flags, width, precision, size);
			if (result == -1)
				return (-1);
			output_chars += result;
		}
	}
	print_buffer(buffer, &buffs_ind);
	va_end(list);

	return (output_chars);
}

/**
 * print_buffer - writes the buffer content
 * @buffer: char arrays
 * @buffs_ind: index to add next char
 *
 */

void print_buffer(char buffer[], int *buffs_ind)
{
	if (*buffs_ind > 0)
		write(1, &buffer[0], *buffs_ind);
	*buffs_ind = 0;
}
