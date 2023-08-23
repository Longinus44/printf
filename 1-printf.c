#include "main.h"
/**
 * ******** PRINT CHAR *********
 * write_char - returns a char
 * @type: argument list
 * @buffer:array buffer
 * @flags:active flags calculator
 * @width: the width
 * @precision:precisions
 * @size: tells the size
 *
 * Return:number of chars
 */
int write_char(va_list type, char buffer[],
			   int flags, int width, int precision, int size)
{
	char c = va_arg(type, int);
	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
 * *********** PRINT STRING *********
 * print_str - prints string
 * @type: argument list
 * @buffer:array buffer
 * @flags:active flags calculator
 * @width: the width
 * @precision:precisions
 * @size: tells the size
 *
 * Return: char numbers
 */
int print_str(va_list type, char buffer[],
			  int flags, int width, int precision, int size)
{
	int i, j;
	char *strg = va_arg(type, char *);

	j = 0;
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (strg == NULL)
	{
		strg = "(null)";
		if (precision >= 6)
			strg = "   ";
	}
	while (strg[j] != '\0')
		j++;

	if (precision >= 0 && precision < j)
		j = precision;

	if (width > j)
	{
		if (flags & F_MINUS)
		{
			write(1, &strg[0], j);
			for (i = width - j; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - j; i > 0; i--)
				write(1, " ", 1);
			write(1, &strg[0], j);
			return (width);
		}
	}
	return (write(1, strg, j));
}

/**
 * ******* PRINTS PERCENT SIGN **********
 * write_percent - writes a percent sign
 * @type:argument list
 * @buffer:array buffer
 * @flags:calculate flags
 * @width:width
 * @precision:precision
 * @size:size
 *
 * Return:0
 */
int write_percent(va_list type, char buffer[],
				  int flags, int width, int size, int precision)
{
	UNUSED(type);
	UNUSED(buffer);
	UNUSED(precision);
	UNUSED(size);
	UNUSED(flags);
	UNUSED(width);
	return (write(1, "%%", 1));
}

/**
 * *******PRiNT INT *******
 * write_int - outputs int
 * @type:argument list
 * @width: width
 * @size: size
 * @precision: precision
 * @buffer:array of buffer
 * @flags:flags calculator
 *
 * Return:0
 */
int write_int(va_list type, char buffer[],
			  int precision, int size, int flags, int width)
{
	int i = BUFF_SIZE - 2;
	int negate = 0;
	long int j = va_arg(type, long int);
	unsigned long int num;

	j = change_num_size(j, size);
	if (j == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)j;
	if (j < 0)
	{
		num = (unsigned long int)((-1) * j);
		negate = 1;
	}
	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}
	i++;
	return (write_number(negate, i, buffer, flags, size, width, precision));
}

/**
 * write_binary - outputs an unsigned number
 * @type: arguments list
 * @size:size
 * @width:width
 * @buffer: buffer array
 * @precision: speculation
 * @flags:flags
 *
 * Return: 0
 */

int print_binary(va_list types, char buffer[],
				 int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
