#include "dupshell.h"

/**
 * clearmem - frees a pointer and NULLs the address
 * @shw: address of the pointer to free
 *
 * Return: 1 if success, otherwise 0.
 */
int clearmem(void **shw)
{
	if (shw && *shw)
	{
		free(*shw);
		*shw = NULL;
		return (1);
	}
	return (0);
}
