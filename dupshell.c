#include "dupshell.h"

/**
 * main - defines the point beginnign of the execution point of the program
 * @ac: argument denoting argument count
 * @av: argument denoting argument vector
 *
 * Return: either 0 on code execution success or 1 if error encountered
 */
int main(int ac, char **av)
{
	d_type d_typeinfo[] = { SYSTEMINFOINIT };
	int file_desc = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_desc)
		: "r" (file_desc));

	if (ac == 2)
	{
		file_desc = open(av[1], O_RDONLY);
		if (file_desc == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				output(av[0]);
				output(": 0: Can't open ");
				output(av[1]);
				putoutchar('\n');
				putoutchar(FLUSH_INDICATOR);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		d_typeinfo->rdfiledes = file_desc;
	}
	initenvar(d_typeinfo);
	rdhist(d_typeinfo);
	strexec(d_typeinfo, av);
	return (EXIT_SUCCESS);
}
