#include "dupshell.h"

/**
 * atoiErr - changes a string to in
 * @str: the string to be converted
 * Return: 0 success
 *       -1 error
 */
int atoiErr(char *str)
{
	int k = 0;
	unsigned long int finding = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make main return 255? */
	for (k = 0;  str[k] != '\0'; k++)
	{
		if (str[k] >= '0' && str[k] <= '9')
		{
			finding *= 10;
			finding += (str[k] - '0');
			if (finding > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (finding);
}

/**
 * outputErr - outputs error message
 * @d_typeinfo: the parameter & return info struct
 * @imstr: string with err message
 * Return: 0 if no number, converted number or
 *        -1 on error
 */
void outputErr(d_type *d_typeinfo, char *imstr)
{
	output(d_typeinfo->filename);
	output(": ");
	print_int(d_typeinfo->line_tt, STDERR_FILENO);
	output(": ");
	output(d_typeinfo->argvstr[0]);
	output(": ");
	output(imstr);
}

/**
 * print_int - function prints a decimal number
 * @inputString: the inputString message
 * @file_desc: the filedescriptor to write to
 *
 * Return: no of characters printed
 */
int print_int(int inputString, int file_desc)
{
	int (*__putchar)(char) = _putchar;
	int k, counter = 0;
	unsigned int absolute, position;

	if (file_desc == STDERR_FILENO)
		__putchar = putoutchar;
	if (inputString < 0)
	{
		absolute = -inputString;
		__putchar('-');
		counter++;
	}
	else
		absolute = inputString;
	position = absolute;
	for (k = 1000000000; k > 1; k /= 10)
	{
		if (absolute / k)
		{
			__putchar('0' + position / k);
			counter++;
		}
		position %= k;
	}
	__putchar('0' + position);
	counter++;

	return (counter);
}

/**
 * stringify_no- converts a string to int
 * @no: numb
 * @base_er: base_er
 * @checks: argument checks
 *
 * Return: string
 */
char *stringify_no(long int no, int base_er, int checks)
{
	static char *arrptr;
	static char buff[50];
	char operation = 0;
	char *p;
	unsigned long u = no;

	if (!(checks & UNSIGNED_ENABLED) && no < 0)
	{
		u = -no;
		operation = '-';

	}
	arrptr = checks & LOWERCASE_ENABLED ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buff[49];
	*p = '\0';

	do	{
		*--p = arrptr[u % base_er];
		u /= base_er;
	} while (u != 0);

	if (operation)
		*--p = operation;
	return (p);
}

/**
 * strip_comments - function replaces '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void strip_comments(char *buf)
{
	int k;

	for (k = 0; buf[k] != '\0'; k++)
		if (buf[k] == '#' && (!k || buf[k - 1] == ' '))
		{
			buf[k] = '\0';
			break;
		}
}
