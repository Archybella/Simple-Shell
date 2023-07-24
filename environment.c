#include "shell.h"

/**
* handle_env - responsible for printing current environment
* @info: parameter holding potential arguments. Maintains
* constant function prototype.
* Return: consistently 0
*/
int handle_env(info_t *info)
{
print_list_str(info->env);
return (0);
}
/**
*_getenv - retrieves the value of environment variable
* @name: environment variable name
*
* Return: value of the environment variable
*/
char *_getenv(info_t *info, const char *name)
{
list_t *node = info->env;
char *p;

while (node)
{
p = starts_with(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
* handle_setenv - creates a new environment variable or updates an existing one
* @info: parameter holding potential arguments. Maintains
* constant function prototype.
* Return: consistently 0
*/
int handle_setenv(info_t *info)
{
if (info->argc != 3)
{
_eputs("Incorrect number of arguements\n");
return (1);
}
if (_setenv(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}

/**
* handle_unsetenv - deletes environment variables
* @info: parameter holding potential arguments. Maintains
* constant function prototype.
* Return: consistently 0
*/
int handle_unsetenv(info_t *info)
{
int i;

if (info->argc == 1)
{
_eputs("Too few arguements.\n");
return (1);
}
for (i = 1; i <= info->argc; i++)
_unsetenv(info, info->argv[i]);

return (0);
}

/**
* populate_env_list - Fills the environment linked list
* @info: parameter holding potential arguments. Maintains
* constant function prototype.
* Return: consistently 0
*/
int populate_env_list(info_t *info)
{
list_t *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);
info->env = node;
return (0);
}
