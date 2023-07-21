#include "shell.h"

/**
* get_environ - Returns the string array copy of our environ.
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* Return: Pointer to the array of environment strings.
*/
char **get_environ(info_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = list_to_strings(info->env);
info->env_changed = 0;
}
return (info->environ);
}

/**
* custom_unsetenv - Remove an environment variable.
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* @var: The string representing the environment variable to remove.
* Return: 1 on successful delete, 0 otherwise.
*/
int custom_unsetenv(info_t *info, char *var)
{
list_t *node = info->env;
size_t i = 0;

if (!node || !var)
return (0);
while (node)
{
char *p = starts_with(node->str, var);

if (p && *p == '=')
{
info->env_changed = delete_node_at_index(&(info->env), i);
i = 0;
node = info->env;
continue;
}
node = node->next;
i++;
}
return (info->env_changed);
}

/**
* custom_setenv - Initialize a new environment
* variable or modify an existing one.
* @info: Structure containing potential arguments.
* Used to maintain constant function prototype.
* @var: The string representing the environment variable.
* @value: The string representing the environment variable's value.
* Return: Always 0.
*/
int custom_setenv(info_t *info, char *var, char *value)
{
char *buf = NULL;
list_t *node;

if (!var || !value)
return (0);
buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
return (1);
_strcpy(buf, var);
_strcat(buf, "=");
_strcat(buf, value);
node = info->env;
while (node)
{
char *p = starts_with(node->str, var);

if (p && *p == '=')
{
free(node->str);
node->str = buf;
info->env_changed = 1;
return (0);
}
node = node->next;
}
add_node_end(&(info->env), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}
