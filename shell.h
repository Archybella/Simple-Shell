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
int is_delim(char, char *);
int isalpha(int);
int is_atoi(char *);

/* toem_builtin_extra.c */
int handle_history(info_t *);
int unset_alias(info_t *);
int print_alias(info_t *);
int set_alias(info_t *);
int handle_alias(info_t *);

/* toem_inbuilt.c */
int handle_exit(info_t *);
int handle_cd(info_t *);
int handle_help(info_t *);

/* toem_environment.c */
char *_custom_getenv(info_t *, const char *);
int _custom_handle_env(info_t *);
int _custom_handle_setenv(info_t *);
int _custom_handle_unsetenv(info_t *);
int _custom_populate_env_list(info_t *);

/* toem_psb_errors.c */
void _custom_eputs(char *);
int _custom_eputchar(char);
int _custom_putfd(char c, int fd);
int _custom_putsfd(char *str, int fd);

/* toem_psb_errors1.c */
int _custom_erratoi(char *);
void custom_print_error(info_t *, char *);
int custom_print_d(int, int);
char *custom_convert_number(long int, int, int);

/* toem_psb_exits.c */
char *custom_strncpy(char *, char *, int);
char *custom_strncat(char *, char *, int);
char *custom_strchr(char *, char);

/* toem_get_line.c */
ssize_t custom_get_input(info_t *);
int custom_getline(info_t *, char **, size_t *);
void custom_sigintHandler(int);

/* toem_get_information.c */
void custom_clear_info(info_t *);
void custom_set_info(info_t *, char **);
void custom_free_info(info_t *, int);

/* toem_hstry.c */
int renumber_history(info_t *info);
int get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);

/* toem_lst.c */
list_t *new_add_node(list_t **, const char *, int);
list_t *new_add_node_end(list_t **, const char *, int);
size_t print_new_list_str(const list_t *);
int delete_new_node_at_index(list_t **, unsigned int);
void free_new_list(list_t **);

/* toem_lst_1.c */
size_t new_list_len(const list_t *);
char **list_to_new_strings(list_t *);
size_t print_new_list(const list_t *);
list_t *new_node_starts_with(list_t *, char *, char);
ssize_t get_new_node_index(list_t *, list_t *);

/* toem_mem_mangmnt.c */
int free_and_null(void **);

/* toem_chk_dub_exe.c */
int check_cmd(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_executable(info_t *, char *, char *);

/* toem_mem_realloc.c */
char *custom_memset(char *, char, unsigned int);
void free_string_array(char **);
void *custom_realloc(void *, unsigned int, unsigned int);

/* toem_shell_condition.c */
int is_interactive_mode(char **);
int find_builtin_command(info_t *);
int fork_command(info_t *);
int find_command_in_path(info_t *, char *, char *);
int hsh(info_t *, char **);

/* toem_strn_len.c */
int custom_strlen(char *);
int str_compare(char *, char *);
char *str_starts_with(const char *, const char *);
char *str_concat(char *, char *);

/* toem_strn_len1.c */
char *str_copy(char *, char *);
char *str_duplicate(const char *);
void print_string(char *);
int write_character(char);

/* toem_split_strn.c */
char **split_string(char *, char *);
char **split_string2(char *, char *);

/* toem_char_handler.c */
int is_chain(info_t *, char *, size_t *);
void check_chain_continue(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif



