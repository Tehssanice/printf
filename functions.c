#include "main.h"

/********************* PRINT A CHARACTER *********************/

/**
 * print_char - prints a character
 * @size: size specifier
 * @width: width
 * @precision: precision specifier
 * @types: arguments
 * @buffer: buffer array to handle print
 * @flags: active flags
 *
 * Return: number of characters printed
 */

int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char z = va_arg(types, int);

	return (handle_write_char(z, buffer, flags, width, precision, size));
}

/************************* PRINT STRING *************************/

/**
 * print_string - prints string
 * @size: size specifier
 * @width: width
 * @precision: precision specifier
 * @types: arguments
 * @buffer: buffer array to handle print
 * @flags: active flags
 *
 * Return: Number of chars printed
 */

int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}
	while (str[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}
	return (write(1, str, len));
}

/************************* PRINT PERCENT SIGN *************************/

/**
 * print_percent - prints percent sign
 * @size: size specifier
 * @width: width
 * @precision: precision specifier
 * @types: arguments
 * @buffer: buffer array to handle print
 * @flags: active flags
 *
 * Return: Number of characters printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/

/**
 * print_int - print int
 * @size: size specifier
 * @width: width
 * @precision: precision specifier
 * @types: arguments
 * @buffer: buffer array to handle print
 * @flags: active flags
 *
 * Return: Number of characters printed
 */

int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/

/**
 * print_binary - prints unsigned number
 * @size: size specifier
 * @width: width
 * @precision: precision specification
 * @types: arguments
 * @buffer: buffer array to handle print
 * @flags: active flags
 *
 * Return: Number of characters printed.
 */

int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int num1, num2, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	num1 = va_arg(types, unsigned int);
	num2 = 2147483648; /* (2 ^ 31) */
	a[0] = num1 / num2;

	for (i = 1; i < 32; i++)
	{
		num2 /= 2;
		a[i] = (num1 / num2) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char c = '0' + a[i];

			write(1, &c, 1);
			count++;
		}
	}
	return (count);
}
