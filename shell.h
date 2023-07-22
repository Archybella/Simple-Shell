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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangment */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_is_atoi.c */
int toem_is_delim(char, char *);
int toem_isalpha(int);
int toem_atoi(char *);

/* toem_builtin_extra.c */
int toem_handle_history(info_t *);
int toem_handle_alias(info_t *);

/* toem_inbuilt.c */
int toem_handle_exit(info_t *);
int toem_handle_cd(info_t *);
int toem_handle_help(info_t *);

/* toem_environment.c */
char *toem_getenv(info_t *, const char *);
int toem_handle_env(info_t *);
int toem_handle_setenv(info_t *);
int toem_handle_unsetenv(info_t *);
int toem_populate_env_list(info_t *);

/* toem_psb_errors.c */
void toem_eputs(char *);
int toem_eputchar(char);
int toem_putfd(char c, int fd);
int toem_putsfd(char *str, int fd);

/* toem_psb_errors1.c */
int toem_erratoi(char *);
void toem_print_error(info_t *, char *);
int toem_print_d(int, int);
char *toem_convert_number(long int, int, int);
void toem_remove_comments(char *);

/* toem_psb_exits.c */
char *toem_strncpy(char *, char *, int);
char *toem_strncat(char *, char *, int);
char *toem_strchr(char *, char);

/* toem_get_line.c */
ssize_t toem_get_input(info_t *);
int toem_getline(info_t *, char **, size_t *);
void toem_sigintHandler(int);

/* toem_get_information.c */
void toem_clear_info(info_t *);
void toem_set_info(info_t *, char **);
void toem_free_info(info_t *, int);

/* toem_hstry.c */
int toem_write_history(info_t *info);
int toem_read_history(info_t *info);
int toem_build_history_list(info_t *info, char *buf, int linecount);

/* toem_lst.c */
list_t *toem_add_node(list_t **, const char *, int);
list_t *toem_add_node_end(list_t **, const char *, int);
size_t toem_print_list_str(const list_t *);
int toem_delete_node_at_index(list_t **, unsigned int);
void toem_free_list(list_t **);

/* toem_lst_1.c */
size_t toem_list_len(const list_t *);
char **toem_list_to_strings(list_t *);
size_t toem_print_list(const list_t *);
list_t *toem_node_starts_with(list_t *, char *, char);
ssize_t toem_get_node_index(list_t *, list_t *);

/* toem_mem_mangmnt.c */
int toem_bfree(void **);

/* toem_chk_dub_exe.c */
int toem_is_chain(info_t *, char *, size_t *);
void toem_check_chain(info_t *, char *, size_t *, size_t, size_t);

/* toem_mem_realloc.c */
char *toem_memset(char *, char, unsigned int);
void toem_ffree(char **);
void *toem_realloc(void *, unsigned int, unsigned int);

/* toem_shell_condition.c */
int toem_loophsh(char **);

/* toem_strn_len.c */
int toem_strlen(char *);
int toem_strcmp(char *, char *);
char *toem_starts_with(const char *, const char *);
char *toem_strcat(char *, char *);

/* toem_strn_len1.c */
char *toem_strcpy(char *, char *);
char *toem_strdup(const char *);
void toem_puts(char *);
int toem_putchar(char);

/* toem_split_strn.c */
char **toem_strtow(char *, char *);
char **toem_strtow2(char *, char);

/* toem_char_handler.c */
int toem_replace_alias(info_t *);
int toem_replace_vars(info_t *);
int toem_replace_string(char **, char *);

#endif


