#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

/* used to define custom getline()*/
#define ENABLE_GETLINE 0
#define ENABLE_STRTOK 0

#define HISTORY_FILE_NAME	".simple_shell_history"
#define MAX_HISTORY_ENTRIES	4096

/* used to/for number conevrsion */
#define LOWERCASE_ENABLED	1
#define UNSIGNED_ENABLED	2

/* used to merge several commands */
#define NORM	0
#define OR		1
#define AND		2
#define CHAIN	3


/* used to read&writing buffers */
#define R_BUF_SZ 1024
#define W_BUF_SZ 1024
#define FLUSH_INDICATOR -1


extern char **environ;


/**
 * struct built - contains a builtin string and related function
 * @cmd: the builtin command flag
 * @handler: the function
 */typedef struct lststr
{
	int no;
	char *string;
	struct lststr *next_node;
} lst_t;

/**
 *struct argbundle - holds pseudo-arguments for a function
 *@argstr: user input fetched by getline
 *@argvstr: string array obtained from user input
 *@path: path of current argument string
 *@argc_no: number of arguments
 *@line_tt: number of errors
 *@error_no: exit()s error code
 *@counter_line: the number of lines in each output
 *@filename: filename of current program
 *@envcpy: singly linked list local environ copy
 *@environcpy: edited environ copy
 *@hist: node in singly linked list
 *@aka: alternate name of node
 *@altered_env: denote environ change
 *@status: d_typeinfo about the last exec'd command
 *@buf_cmd: pointer address to buf_cmd, it is used when chaining commands
 *@buf_operation: variable to specify command opperation ||, &&, ;
 *@rdfiledes: file descriptor from which line input is read
 *@numhist: keeps track of the history line number count
 */
typedef struct argbundle
{
	char *argstr;
	char **argvstr;
	char *path;
	int argc_no;
	unsigned int line_tt;
	int error_no;
	int counter_line;
	char *filename;
	lst_t *envcpy;
	lst_t *hist;
	lst_t *aka;
	char **environcpy;
	int altered_env;
	int status;

	char **buf_cmd;
	int buf_operation;
	int rdfiledes;
	int numhist;
} d_type;

#define SYSTEMINFOINIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct built - contains a builtin string and related function
 * @cmd: the builtin command flag
 * @handler: the function
 */
typedef struct modbuild
{
	char *cmd;
	int (*handler)(d_type *);
} tblbuild;

/* used in the file (strparse.c)*/
int cmd_exist(d_type *, char *);
char *dup_str(char *, int, int);
char *cmd_path(d_type *, char *, char *);

/*used in the file (strget.c) */
ssize_t getSysInput(d_type *);
int custGetLine(d_type *, char **, size_t *);
void sigintHandler(int);

/* used in the file (strtoken.c) */
char **tkzStr(char *, char *);
char **tkzStr2(char *, char);

/* used in the file (strexec.c) */
int strexec(d_type *, char **);
int search_builtin(d_type *);
void search_cmd(d_type *);
void child_fork(d_type *);

/* used in the file (loopexec.c) */
int loopexec(char **);

/* used in the file (strerr1.c) */
int atoiErr(char *);
void outputErr(d_type *, char *);
int print_int(int, int);
char *stringify_no(long int, int, int);
void strip_comments(char *);

/* used in the file (str.c) */
int str_len(char *);
int str_cmp(char *, char *);
char *str_start(const char *, const char *);
char *str_cat(char *, char *);

/* used in the file (strerr1.c) */
void output(char *);
int putoutchar(char);
int writechar(char c, int fd);
int writestr(char *string, int fd);

/* used in the file (str1.c) */
char *str_cpy(char *, char *);
char *str_dup(const char *);
void _puts(char *);
int _putchar(char);

/* used in the file (dynmcmemory.c) */
char *filblock(char *, char, unsigned int);
void freemem(char **);
void *reallocmem(void *, unsigned int, unsigned int);

/* used in the file (freemem.c) */
int clearmem(void **);

/* used in the file(stratoi.c)*/
int modsys(d_type *);
int delimchar(char, char *);
int alphachar(int);
int strtint(char *);

/* used in the file (prdfndcmd.c)*/
int exitbin(d_type *);
int cdbin(d_type *);
int helpbin(d_type *);

/* used in the file (prdfndcmd1.c) */
int histdisp(d_type *);
int createaka(d_type *);

/* used in the file (strenv.c)*/
char **strenv(d_type *);
int rmsetenv(d_type *, char *);
int setenvset(d_type *, char *, char *);

/* used in the file (strenviron.c) */
char *retrienv(d_type *, const char *);
int managenv(d_type *);
int modsetenv(d_type *);
int unsetenvrm(d_type *);
int initenvar(d_type *);

/* used in the file (strinfo.c)*/
void resetinfo(d_type *);
void settinginfo(d_type *, char **);
void memfrinfo(d_type *, int);

/* used in the file (nodemod.c) */
lst_t *putnode_start(lst_t **, const char *, int);
lst_t *putnode_end(lst_t **, const char *, int);
size_t printstrlst(const lst_t *);
int rmnodeindex(lst_t **, unsigned int);
void memfree(lst_t **);

/* used in the file (nodemod1.c) */
size_t szlst(const lst_t *);
char **lsttostr(lst_t *);
size_t putlst(const lst_t *);
lst_t *specprefix(lst_t *, char *, char);
ssize_t retrindex(lst_t *, lst_t *);

/* used in the (manhistory.c) */
char *rethistfile(d_type *d_typeinfo);
int wrthist(d_type *d_typeinfo);
int rdhist(d_type *d_typeinfo);
int conhistlist(d_type *d_typeinfo, char *buf, int linecount);
int renohist(d_type *d_typed_typeinfo);

/* used in the (strvar.c) */
int check_opp(d_type *, char *, size_t *);
void chainproc(d_type *, char *, size_t *, size_t, size_t);
int akasub(d_type *);
int varsub(d_type *);
int strsub(char **, char *);

/* used in the (term.c) */
char *str_n_cpy(char *, char *, int);
char *str_n_cat(char *, char *, int);
char *str_chr(char *, char);

#endif
