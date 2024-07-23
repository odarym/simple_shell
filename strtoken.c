#include "dupshell.h"

/**
 * **tkzStr - function to split user input string into arguments
 * @string: user input, char array string
 * @dlmt: delimiter character
 * Return: NULL if fail, else ptr to string array
 */

char **tkzStr(char *string, char *dlmt)
{
	int j, y, z, n, wordcount = 0;
	char **t;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!dlmt)
		dlmt = " ";
	for (j = 0; string[j] != '\0'; j++)
		if (!delimchar(string[j], dlmt)
						&& (delimchar(string[j + 1], dlmt) || !string[j + 1]))
			wordcount++;

	if (wordcount == 0)
		return (NULL);
	t = malloc((1 + wordcount) * sizeof(char *));
	if (!t)
		return (NULL);
	for (j = 0, y = 0; y < wordcount; y++)
	{
		while (delimchar(string[j], dlmt))
			j++;
		z = 0;
		while (!delimchar(string[j + z], dlmt) && string[j + z])
			z++;
		t[y] = malloc((z + 1) * sizeof(char));
		if (!t[y])
		{
			for (z = 0; z < y; z++)
				free(t[z]);
			free(t);
			return (NULL);
		}
		for (n = 0; n < z; n++)
			t[y][n] = string[j++];
		t[y][n] = 0;
	}
	t[y] = NULL;
	return (t);
}

/**
 * **tkzStr2 - func that split char array string to args
 * @string: user input in CLI
 * @dlmt: denote delimiter character
 * Return: NULL if fail, ptr to arr of strings
 */
char **tkzStr2(char *string, char dlmt)
{
	int j, y, z, n, wordcount = 0;
	char **t;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (j = 0; string[j] != '\0'; j++)
		if ((string[j] != dlmt && string[j + 1] == dlmt) ||
		    (string[j] != dlmt && !string[j + 1]) || string[j + 1] == dlmt)
			wordcount++;
	if (wordcount == 0)
		return (NULL);
	t = malloc((1 + wordcount) * sizeof(char *));
	if (!t)
		return (NULL);
	for (j = 0, y = 0; y < wordcount; y++)
	{
		while (string[j] == dlmt && string[j] != dlmt)
			j++;
		z = 0;
		while (string[j + z] != dlmt && string[j + z] && string[j + z] != dlmt)
			z++;
		t[y] = malloc((z + 1) * sizeof(char));
		if (!t[y])
		{
			for (z = 0; z < y; z++)
				free(t[z]);
			free(t);
			return (NULL);
		}
		for (n = 0; n < z; n++)
			t[y][n] = string[j++];
		t[y][n] = 0;
	}
	t[y] = NULL;
	return (t);
}
