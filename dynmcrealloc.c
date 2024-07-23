#include "dupshell.h"

/**
 **filblock - custom memset; fill byteno=memry block with constant/similar byte
 *@sptr: points to the block of memory
 *@u: the similar/constant byte with which *sptr is filled with
 *@byteno: total bytes the memset aims to fill the memory block with
 *Return: pointer to the blockof memory mset fills with cnstnt byte
 */
char *filblock(char *sptr, char u, unsigned int byteno)
{
	unsigned int a;

	for (a = 0; a < byteno; a++)
		sptr[a] = u;
	return (sptr);
}

/**
 * freemem - clears strings' string
 * @ptrstr: strings' string
 */
void freemem(char **ptrstr)
{
	char **a = ptrstr;

	if (!ptrstr)
		return;
	while (*ptrstr)
		free(*ptrstr++);
	free(a);
}

/**
 * reallocmem - custom realloc function that re-allocates memoryblock
 * @p: points to blckold
 * @blockold: blckold byte size
 * @blocknew: blcknew byte size
 *
 * Return: pointer to the old block
 */
void *reallocmem(void *p, unsigned int blockold, unsigned int blocknew)
{
	char *m;

	if (!p)
		return (malloc(blocknew));
	if (!blocknew)
		return (free(p), NULL);
	if (blocknew == blockold)
		return (p);

	m = malloc(blocknew);
	if (!m)
		return (NULL);

	blockold = blockold < blocknew ? blockold : blocknew;
	while (blockold--)
		m[blockold] = ((char *)p)[blockold];
	free(p);
	return (m);
}
