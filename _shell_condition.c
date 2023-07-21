#include "shell.h"

/**
* is_interactive_mode - Returns true if the shell is in interactive mode.
* @info: Struct address.
*
* Return: 1 if interactive mode, 0 otherwise.
*/
static int is_interactive_mode(info_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
* find_builtin_command - Finds a builtin command.
* @info: The parameter & return info struct.
*
* Return: -1 if builtin not found,
* 0 if builtin executed successfully,
* 1 if builtin found but not successful,
* 2 if builtin signals exit().
*/
static int find_builtin_command(info_t *info)
{
int i, builtin_ret = -1;
builtin_table builtintbl[] = {
{"exit", handle_exit},
{"env", handle_env},
{"help", handle_help},
{"history", handle_history},
{"setenv", handle_setenv},
{"unsetenv", handle_unsetenv},
{"cd", handle_cd},
{"alias", handle_alias},
{NULL, NULL}
};

for (i = 0; builtintbl[i].type; i++)
if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
{
info->line_count++;
builtin_ret = builtintbl[i].func(info);
break;
}
return (builtin_ret);
}

/**
* fork_command - Forks an exec thread to run the command.
* @info: The parameter & return info struct.
*
* Return: void.
*/
static void fork_command(info_t *info)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, get_environ(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
print_error(info, "Permission denied\n");
}
}
}

/**
* find_command_in_path - Finds a command in the PATH.
* @info: The parameter & return info struct.
*
* Return: void.
*/
static void find_command_in_path(info_t *info)
{
char *path = NULL;
int i, k;

info->path = info->argv[0];
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}
for (i = 0, k = 0; info->arg[i]; i++)
if (!is_delim(info->arg[i], " \t\n"))
k++;
if (!k)
return;

path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
fork_command(info);
}
else
{
if ((is_interactive_mode(info) || _getenv(info, "PATH=")
|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
fork_command(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
print_error(info, "not found\n");
}
}
}

/**
* hsh - Main shell loop.
* @info: The parameter & return info struct.
* @av: The argument vector from main().
*
* Return: 0 on success, 1 on error, or error code.
*/
int hsh(info_t *info, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;

while (r != -1 && builtin_ret != -2)
{
clear_info(info);
if (is_interactive_mode(info))
_puts("$ ");
_eputchar(BUF_FLUSH);
r = get_input(info);
if (r != -1)
{
set_info(info, av);
builtin_ret = find_builtin_command(info);
if (builtin_ret == -1)
find_command_in_path(info);
}
else if (is_interactive_mode(info))
_putchar('\n');
free_info(info, 0);
}
write_history(info);
free_info(info, 1);
if (!is_interactive_mode(info) && info->status)
exit(info->status);
if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtin_ret);
}
