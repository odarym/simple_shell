#include "dupshell.h"

/**
 * str_len - custom function that performs purpose of custom strlen
 * @ptrstr: string passed to str_len
 *
 * Return: length of string passed to function
 */
int str_len(char *ptrstr)
{
	int j = 0;

	if (!ptrstr)
		return (0);

	while (*ptrstr++)
		j++;
	return (j);
}

/**
 * str_cmp - function that compares two strings passed to it lexicographically
 * @ptrstr1: first arg, first string
 * @ptrstr2: second arg, second string
 *
 * Return: positive if str1 >, negative for shorter str1, 0 for equal length
 */
int str_cmp(char *ptrstr1, char *ptrstr2)
{
	while (*ptrstr1 && *ptrstr2)
	{
		if (*ptrstr1 != *ptrstr2)
			return (*ptrstr1 - *ptrstr2);
		ptrstr1++;
		ptrstr2++;
	}
	if (*ptrstr1 == *ptrstr2)
		return (0);
	else
		return (*ptrstr1 < *ptrstr2 ? -1 : 1);
}

/**
 * str_start - checks if the substring starts with strptr
 * @strptr: 1st arg, the string to be passed
 * @strarg: the substring being sought out for
 *
 * Return: &of the larger string'ptrstr next char, else NULL
 */
char *str_start(const char *strptr, const char *strarg)
{
	while (*strarg)
		if (*strarg++ != *strptr++)
			return (NULL);
	return ((char *)strptr);
}

/**
 * str_cat - function that concatenates/appends two strings
 * @ptrbufdest: denotes the pointer to the destination buffer
 * @ptrbufsrc: denotes the pointer to the source buffer
 *
 * Return: pointer to destination buffer
 */
char *str_cat(char *ptrbufdest, char *ptrbufsrc)
{
	char *ret = ptrbufdest;

	while (*ptrbufdest)
		ptrbufdest++;
	while (*ptrbufsrc)
		*ptrbufdest++ = *ptrbufsrc++;
	*ptrbufdest = *ptrbufsrc;
	return (ret);
}
