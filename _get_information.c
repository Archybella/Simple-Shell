#include "shell.h"

/**
* custom_clear_info - Initializes the info_t struct.
* @info: The struct address to be initialized.
*/
void custom_clear_info(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}

/**
* custom_set_info - Initializes the info_t struct.
* @info: The struct address to be initialized.
* @av: Argument vector.
*/
void custom_set_info(info_t *info, char **av)
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
* custom_free_info - Frees the info_t struct fields.
* @info: The struct address.
* @all: True if freeing all fields.
*/
void custom_free_info(info_t *info, int all)
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
