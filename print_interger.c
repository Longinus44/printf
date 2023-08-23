#include "main.h"
/**
 * print_integer - function that prints interger
 * @num: the integer
 *
 * Return: 0
 */

void print_integer(int num)
{
	char buffer[20];
	int i;
	int index = 0;

	if (num == 0)
	{
		_putchar('0');
		return;
	}

	if (num < 0)
	{
		_putchar('-');
		num = -num;
	}

	while (num > 0)
	{
		buffer[index++] = (num % 10) + '0';
		num /= 10;
	}

	for (i = index - 1; i >= 0; i--)
	{
		_putchar(buffer[i]);
	}
}
