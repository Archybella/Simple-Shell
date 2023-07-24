#include "shell.h"

/**
* interactive - checks whether the shell is in interactive mode
* @info: Address indicator to the input structure
*
* Return: 1 if the shell is in interactive mode, 0 otherwise
*/
static int interactive(info_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
* find_builtin - searches for a built-in command
* @info: Address indicator to the input structure
*
* Return: -1 if the built-in command is absent,
*         0 if the built-in command is processed effectively,
*         1 if the built-in command is found but not effective,
*         2 if the built-in command triggers an exit()
*/
static int find_builtin(info_t *info)
{
int i, built_in_ret = -1;
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
built_in_ret = builtintbl[i].func(info);
break;
}
return (built_in_ret);
}

/**
* fork_cmd - creates a child process to execute a command
* @info: Memory address to the input structure
*
* Return: No return value.
*/
static void fork_cmd(info_t *info)
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
* find_cmd - searches for a command in the PATH
* @info: Memory address to the input structure
*
* Return: No return value
*/
static void find_cmd(info_t *info)
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
fork_cmd(info);
}
else
{
if ((interactive(info) || _getenv(info, "PATH=")
|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
fork_cmd(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
print_error(info, "not found\n");
}
}
}

/**
* hsh - Primary loop of the shell
* @info: Memory address to the input structure
* @av: Array of command-line arguments passed to the main function
*
* Return: 0 on success, 1 if there is an error, else error code
*/
int hsh(info_t *info, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;

while (r != -1 && builtin_ret != -2)
{
clear_info(info);
if (interactive(info))
_puts("$ ");
_eputchar(BUF_FLUSH);
r = get_input(info);
if (r != -1)
{
set_info(info, av);
builtin_ret = find_builtin(info);
if (builtin_ret == -1)
find_cmd(info);
}
else if (interactive(info))
_putchar('\n');
free_info(info, 0);
}
write_history(info);
free_info(info, 1);
if (!interactive(info) && info->status)
exit(info->status);
if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtin_ret);
}
