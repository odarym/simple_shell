#include "dupshell.h"

/**
 * rethistfile - custom fucntion to fetch a file's history
 * @d_typeinfo: argument from struct
 *
 * Return: string with the history file
 */

char *rethistfile(d_type *d_typeinfo)
{
	char *buf, *fld;

	fld = retrienv(d_typeinfo, "HOME=");
	if (!fld)
		return (NULL);
	buf = malloc(sizeof(char) * (str_len(fld) + str_len(HISTORY_FILE_NAME) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	str_cpy(buf, fld);
	str_cat(buf, "/");
	str_cat(buf, HISTORY_FILE_NAME);
	return (buf);
}
/**
 * wrthist - custom function opens file or create a new one if not found
 * @d_typeinfo: argument from struct
 *
 * Return: -1 if fail, 1 is code execution succeeds
 */
int wrthist(d_type *d_typeinfo)
{
	ssize_t file_desc;
	char *filename = rethistfile(d_typeinfo);
	lst_t *nodePtr = NULL;

	if (!filename)
		return (-1);

	file_desc = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file_desc == -1)
		return (-1);
	for (nodePtr = d_typeinfo->hist; nodePtr; nodePtr = nodePtr->next_node)
	{
		writestr(nodePtr->string, file_desc);
		writechar('\n', file_desc);
	}
	writechar(FLUSH_INDICATOR, file_desc);
	close(file_desc);
	return (1);
}

/**
 * rdhist - function to fetch and return the history of an allocated file
 * @d_typeinfo: struct as arg
 *
 * Return: file's numhist on execution success or 0 if otherwise found
 */
int rdhist(d_type *d_typeinfo)
{
	int k, fin = 0, counterl = 0;
	ssize_t file_desc, retlen, szfile = 0;
	struct stat st;
	char *buf = NULL, *filename = rethistfile(d_typeinfo);

	if (!filename)
		return (0);

	file_desc = open(filename, O_RDONLY);
	free(filename);
	if (file_desc == -1)
		return (0);
	if (!fstat(file_desc, &st))
		szfile = st.st_size;
	if (szfile < 2)
		return (0);
	buf = malloc(sizeof(char) * (szfile + 1));
	if (!buf)
		return (0);
	retlen = read(file_desc, buf, szfile);
	buf[szfile] = 0;
	if (retlen <= 0)
		return (free(buf), 0);
	close(file_desc);
	for (k = 0; k < szfile; k++)
		if (buf[k] == '\n')
		{
			buf[k] = 0;
			conhistlist(d_typeinfo, buf + fin, counterl++);
			fin = k + 1;
		}
	if (fin != k)
		conhistlist(d_typeinfo, buf + fin, counterl++);
	free(buf);
	d_typeinfo->numhist = counterl;
	while (d_typeinfo->numhist-- >= MAX_HISTORY_ENTRIES)
		rmnodeindex(&(d_typeinfo->hist), 0);
	renohist(d_typeinfo);
	return (d_typeinfo->numhist);
}

/**
 * conhistlist - function adds nodePtr at end of singly linked list
 * @d_typeinfo: struct potentially with args
 * @buf: buffer
 * @counterl: history of file plus new end nodePtr
 *
 * Return: 0 on execution success
 */
int conhistlist(d_type *d_typeinfo, char *buf, int counterl)
{
	lst_t *nodePtr = NULL;

	if (d_typeinfo->hist)
		nodePtr = d_typeinfo->hist;
	putnode_end(&nodePtr, buf, counterl);

	if (!d_typeinfo->hist)
		d_typeinfo->hist = nodePtr;
	return (0);
}

/**
 * renohist - reno singly llist after alteration
 * @d_typeinfo: struct potentially with args
 *
 * Return: new history of file
 */
int renohist(d_type *d_typeinfo)
{
	lst_t *nodePtr = d_typeinfo->hist;
	int k = 0;

	while (nodePtr)
	{
		nodePtr->no = k++;
		nodePtr = nodePtr->next_node;
	}
	return (d_typeinfo->numhist = k);
}
