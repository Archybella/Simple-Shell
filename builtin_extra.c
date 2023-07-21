#include "shell.h"

/**
* _handle_history - Displays the history list, one command per line, preceded
*                   with line numbers, starting at 0.
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* Return: Always 0
*/
int _handle_history(info_t *info)
{
print_list(info->history);
return (0);
}

/**
* _unset_alias - Removes an alias from the alias list.
* @info: Parameter struct.
* @str: The string alias.
*
* Return: Always 0 on success, 1 on error
*/
int _unset_alias(info_t *info, char *str)
{
char *p, c;
int ret;

p = _strchr(str, '=');
if (!p)
return (1);
c = *p;
*p = 0;
ret = delete_node_at_index(&(info->alias),
get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
*p = c;
return (ret);
}

/**
* _set_alias - Sets or updates an alias in the alias list.
* @info: Parameter struct.
* @str: The string alias.
*
* Return: Always 0 on success, 1 on error
*/
int _set_alias(info_t *info, char *str)
{
char *p;

p = _strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (_unset_alias(info, str));

_unset_alias(info, str);
return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
* _print_alias - Prints an alias string.
* @node: The alias node.
*
* Return: Always 0 on success, 1 on error
*/
int _print_alias(list_t *node)
{
char *p = NULL, *a = NULL;

if (node)
{
p = _strchr(node->str, '=');
for (a = node->str; a <= p; a++)
_putchar(*a);
_putchar('\'');
_puts(p + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
* _handle_alias - Mimics the alias builtin (man alias).
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* Return: Always 0
*/
int _handle_alias(info_t *info)
{
int i = 0;
char *p = NULL;
list_t *node = NULL;

if (info->argc == 1)
{
node = info->alias;
while (node)
{
_print_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; info->argv[i]; i++)
{
p = _strchr(info->argv[i], '=');
if (p)
_set_alias(info, info->argv[i]);
else
_print_alias(node_starts_with(info->alias, info->argv[i], '='));
}

return (0);
}
