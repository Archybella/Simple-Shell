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
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

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
* struct passinfo - contains pseudo-arguments to pass into a function,
* allowing a uniform prototype for the function pointer struct
* @arg: a string generated from getline containing arguments
* @argv: an array of strings generated from arg
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

char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
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

/* _shell_condition.c */
int is_interactive_mode(info_t *, char **);
int find_builtin_command(info_t *, char *);
int fork_command(info_t *, char *);
int find_command_in_path(info_t *, char *);
int hsh(info_t *, char **);

/* chk_dub_exe.c */
int check_cmd(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_executable(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* _psb_errors.c */
void custom_print_error(char *);
int custom_print_character(char);
int write_to_file_descriptor(char c, int fd);
int write_string_to_file_descriptor(char *str, int fd);

/* _strn_len.c */
int custom_strlen(char *);
int str_compare(char *, char *);
char *str_starts_with(const char *, const char *);
char *str_concat(char *, char *);

/* _strn_len1.c */
char *str_copy(char *, char *);
char *str_duplicate(const char *);
void print_string(char *);
int print_character(char);

/* _ psb_exits.c */
char *str_copy_n(char *, char *, int);
char *str_concat_n(char *, char *, int);
char *find_character_in_string(char *, char);

/* _getline.c */
ssize_t custom_getline(info_t *, char **, size_t *);
int custom_get_input(info_t *);
int custom_read_buf(info_t *, char *, int);
void custom_sigintHandler(int);

/* _get_information.c */
void custom_clear_info(info_t *);
void custom_set_info(info_t *, char **);
void custom_free_info(info_t *, int);

/* _environment.c */
char *custom_getenv(info_t *, const char *);
int custom_handle_env(info_t *);
int custom_handle_setenv(info_t *);
int custom_handle_unsetenv(info_t *);
int custom_populate_env_list(info_t *);

/* _get_environment.c */
char **get_environ(info_t *);
int custom_unsetenv(info_t *, char *);
int custom_setenv(info_t *, char *, char *);

/* _hstry.c */
int _get_history_file(info_t *, const char *);
int _write_history(info_t *);
int _read_history(info_t *);
int _build_history_list(info_t *, char *, int);

/* _lst.c */
list_t *new_add_node(list_t **, const char *, int);
list_t *new_add_node_end(list_t **, const char *, int);
size_t print_new_list_str(const list_t *);
int delete_new_node_at_index(list_t **, unsigned int);
void free_new_list(list_t **);

/* _lst_1.c */
size_t new_list_len(const list_t *);
char **list_to_new_strings(list_t *);
size_t print_new_list(const list_t *);
list_t *new_node_starts_with(list_t *, char *, char);
ssize_t get_new_node_index(list_t *, list_t *);

/* mem_mangmnt.c */
int free_and_null(void **);

/* _is_atoi.c */
int is_chain(info_t *, char *, size_t *);
void check_chain_continue(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif

