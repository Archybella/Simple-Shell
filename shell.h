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

/* ... (existing macros and struct definitions) ... */

/* Function Prototypes */

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

/* split_string.c */
char **split_string(char *str, char *delimiters);
char **split_string2(char *str, char delimiter);

#endif

