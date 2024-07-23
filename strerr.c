#include "dupshell.h"

/**
 * output - prints string to CLI
 * @string: user input string
 *
 * Return: none as void d_type is returned
 */
void output(char *string)
{
	int t = 0;

	if (!string)
		return;
	while (string[t] != '\0')
	{
		putoutchar(string[t]);
		t++;
	}
}

/**
 * putoutchar - output char to stream 1
 * @y: argument of function; char
 *
 * Return: 1 if success of code execution
 * If err is found, -1 error number appropriately set
 */
int putoutchar(char y)
{
	static int t;
	static char buf[W_BUF_SZ];

	if (y == FLUSH_INDICATOR || t >= W_BUF_SZ)
	{
		write(2, buf, t);
		t = 0;
	}
	if (y != FLUSH_INDICATOR)
		buf[t++] = y;
	return (1);
}

/**
 * writechar - write to file_desc; char y
 * @y: character; argument
 * @file_desc: file_desc being output to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int writechar(char y, int file_desc)
{
	static int t;
	static char buf[W_BUF_SZ];

	if (y == FLUSH_INDICATOR || t >= W_BUF_SZ)
	{
		write(file_desc, buf, t);
		t = 0;
	}
	if (y != FLUSH_INDICATOR)
		buf[t++] = y;
	return (1);
}

/**
 * writestr - output char arr of strings
 * @string: user input string
 * @file_desc: file_desc being written to
 *
 * Return: the number of chars put
 */
int writestr(char *string, int file_desc)
{
	int t = 0;

	if (!string)
		return (0);
	while (*string)
	{
		t += writechar(*string++, file_desc);
	}
	return (t);
}
