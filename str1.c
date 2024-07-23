#include "dupshell.h"

/**
 * str_cpy - copies a string
 * @ptrbufdest: the destination
 * @ptrbufsrc: the source
 *
 * Return: pointer to ptrbufdest
 */
char *str_cpy(char *ptrbufdest, char *ptrbufsrc)
{
	int j = 0;

	if (ptrbufdest == ptrbufsrc || ptrbufsrc == 0)
		return (ptrbufdest);
	while (ptrbufsrc[j])
	{
		ptrbufdest[j] = ptrbufsrc[j];
		j++;
	}
	ptrbufdest[j] = 0;
	return (ptrbufdest);
}

/**
 * str_dup - duplicates a string
 * @string: str to duplicate
 *
 * Return: ptr to the duplicated string
 */
char *str_dup(const char *string)
{
	int len = 0;
	char *ptrRet;

	if (string == NULL)
		return (NULL);
	while (*string++)
		len++;
	ptrRet = malloc(sizeof(char) * (len + 1));
	if (!ptrRet)
		return (NULL);
	for (len++; len--;)
		ptrRet[len] = *--string;
	return (ptrRet);
}

/**
 *_puts - prints an input string
 *@string: the string to be printed
 *
 * Return: void
 */
void _puts(char *string)
{
	int j = 0;

	if (!string)
		return;
	while (string[j] != '\0')
	{
		_putchar(string[j]);
		j++;
	}
}

/**
 * _putchar - writes the character s to stdout
 * @s: The character to print
 *
 * Return: On success 1 or -1 for an error
 */
int _putchar(char s)
{
	static int j;
	static char buf[W_BUF_SZ];

	if (s == FLUSH_INDICATOR || j >= W_BUF_SZ)
	{
		write(1, buf, j);
		j = 0;
	}
	if (s != FLUSH_INDICATOR)
		buf[j++] = s;
	return (1);
}
