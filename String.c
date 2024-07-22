#include "String.h"


/**
 * *StringCopy - copies the string pointed to by src including null byte(\0)
 *            to the bufferer pointed to by dest
 * @src: source of string to be copied
 * @dest: destination of string to be copied
 * Return: pointer to dest
*/
char *StringCopy(char *dest, char *src)
{
	int a, b = 0;

	for (a = 0; src[a] != '\0'; a++)
	{
		dest[b] = src[a];
		b++;
	}
	dest[b] = '\0';

	return (dest);
}



/**
 * StringCat - appends the src string to the dest string
 *           overwriting the terminating null byte at the end
 *           of dest, then adds a terminating null byte
 * @src: first string
 * @dest: second string
 *
 * Return: returns a pointer to the resulting string dest
*/
char *StringCat(char *dest, char *src)
{
	int len_dest = 0;
	int len_src = 0;

	for (; dest[len_dest] != '\0'; len_dest++)
		;

	for (; src[len_src] != '\0' ;)
		dest[len_dest++] = src[len_src++];

	dest[len_dest] = '\0';
	return (dest);
}




/**
 * StringCompare - compares two strings
 *
 * @s1: string 1
 * @s2: string 2
 * Return: 0 if identical
 *         <0 if first char in s1's ASCII value less than that of s2
 *         >0 if first charin s2's ASCII value greater than that of s2
*/
int StringCompare(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}

	return (s1[i] - s2[i]);
}



/**
 * StringLength - returns the length of a string
 * @s: string whose length is to be determined
 * Return: Always 0
*/
int StringLength(char *s)
{
	int a;

	for (a = 0; *s != '\0'; s++)
		a++;

	return (a);
}




/**
 * *String_N_Copy - copies a string
 *
 * @dest: destination string
 * @src: source string
 * @n: number of bytes to be copied
 *
 * Return: pointer to dest
*/
char *String_N_Copy(char *dest, char *src, int n)
{
	int i = 0;

	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}

	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}

	return (dest);
}



/**
 * String_N_Compare - Compare n characters in two strings.
 *
 * @s1: first string.
 * @s2: second string.
 * @n: number of characters to check.
 *
 * Return: 0 if strings match
*/
int String_N_Compare(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if (s1 == NULL)
		return (-1);
	for (i = 0; i < n && s2[i]; i++)
	{
		if (s1[i] != s2[i])
		{
			return (1);
		}
	}
	return (0);
}

/**
* StringDuplicate - duplicates a string
*
* @str: string parameter
*
* Return: pointer to a duplicate of str
*/
char *StringDuplicate(char *str)
{
	char *s;
	size_t i = 0, len = 0;

	len = StringLength(str);

	s = malloc(sizeof(char) * (len + 1));

	if (s == NULL)
	{
		free(s);
		return (NULL);
	}

	while (i <= len)
	{
		s[i] = str[i];
		i++;
	}
	return (s);
}




/**
* IsDigit - checks if it is a digit
*
* @ch: parameter integer to test
*
* Return: 1 if its )-9 else 0
*/
int IsDigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);

	else
		return (0);

}




/**
*Atoi - converts string to integer
*
*@s: pointer to string
*
*Return: integer from string
*/
int Atoi(char *s)
{
	uint16_t num = 0;
	uint16_t i;
	uint16_t strLength = StringLength(s);
	int sign = 1;

	for (i = 0; i <  strLength; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		else if (s[i] >= '0' && s[i] <= '9')
		num = num * 10 + (s[i] - 48);

		else if (num > 0)
			break;
	}

	return (num * sign);
}


/**
 * *MemCopy - copies memory area
 *
 * @dest: destination string
 * @src: source string
 * @n: number of bytes
 *
 * Return: pointer to dest
 */
char *MemCopy(char *dest, char *src, unsigned int n)
{
	uint16_t i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

/**
 * *MemSet - fills memory with a constant byte
 * @s: pointer to string s
 * @b: constant byte
 * @n: number of bytes of memory
 * Return: pointer to s
 */
char *MemSet(char *s, char b, unsigned int n)
{
	uint16_t i;

	for (i = 0; i < n; i++)
	{
		s[i] = b;
	}
	return (s);
}

/**
 * Itoa - Convert Integer To Char
 * @n: Int To Convert
 * Return: Char Pointer
 */
char *Itoa(unsigned int n)
{
	int len = 0, i = 0, num;
	char *s;
	char temp;

	num = n;

	while (num != 0)
	{
		len++;
		num /= 10;
	}
	s = malloc(len + 1);

	if (!s)
		return (NULL);

	*s = '\0';
	while (n / 10)
	{
		s[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	s[i] = (n % 10) + '0';

	for (i = 0; i < (len / 2); i++)
	{
		temp = s[i];
		s[i] = s[(len - 1) - i];
		s[(len - 1) - i] = temp;
	}
	s[i + 1] = '\0';
	return (s);
}


/**
* GetLine - Read The Input By User From Stdin
* Return: Input
*/
char *GetLine()
{
	int i, readChar;
	uint16_t buffererSize = 1024;
	char ch = 0, *buffer = malloc(buffererSize);

	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	for (i = 0; (ch != EOF && ch != '\n'); i++)
	{
		fflush(stdin);
		readChar = read(STDIN_FILENO, &ch, 1);
		if (readChar == 0)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		buffer[i] = ch;
		if (buffer[0] == '\n')
		{
			free(buffer);
			return ('\0');
		}
		if (i >= buffererSize)
		{
			buffer = realloc(buffer, buffererSize + 1);
			if (!buffer)
				return (NULL);
		}
	}
	buffer[i] = '\0';
	/* Remove comments */
	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#')
		{
			buffer[i] = '\0';
			break;
		}
	return (buffer);
}

