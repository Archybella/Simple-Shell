#include "shell.h"

/**
* clear_info - configures info_t struct, sets its fields to initial values.
* @info: Address of the info_t struct.
*/

void clear_info(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}

/**
* set_info - Sets up the info_t struct by assigning initial values.
* @info: Address of the info_t struct.
* @av: Function argument
*/
void set_info(info_t *info, char **av)
{

info->fname = av[0];
if (info->arg)
{
int i = 0;

info->argv = strtow(info->arg, " \t");
if (!info->argv)
{
info->argv = malloc(sizeof(char *) * 2);
if (info->argv)
{
info->argv[0] = _strdup(info->arg);
info->argv[1] = NULL;
}
}
for (i = 0; info->argv && info->argv[i]; i++)
;
info->argc = i;
replace_alias(info);
replace_vars(info);
}
}

/**
* free_info - Releases memory allocated for the fields of info_t struct.
* @info: Address of the info_t struct.
* @all: Boolean indicating whether to free all fields.
*/
void free_info(info_t *info, int all)
{
ffree(info->argv);
info->argv = NULL;
info->path = NULL;

if (all)
{
if (!info->cmd_buf)
free(info->arg);
if (info->env)
free_list(&(info->env));
if (info->history)
free_list(&(info->history));

if (info->alias)
free_list(&(info->alias));
ffree(info->environ);
info->environ = NULL;
bfree((void **)info->cmd_buf);
if (info->readfd > 2)
close(info->readfd);
_putchar(BUF_FLUSH);
}
}
