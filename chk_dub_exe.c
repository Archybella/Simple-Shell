#include "shell.h"

/**
* is_cmd - checks whether a file is executable
* @info: info structure parameter
* @path: file path parameter
*
* Return: 1 if a file is executable, 0 if false.
*/
int is_cmd(info_t *info, char *path)
{
struct stat st;

(void)info;
if (!path || stat(path, &st))
return (0);

if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
* dup_chars - replicates selected characters from a string
* @pathstr: PATH string parameter
* @start: A starting index parameter
* @stop: A stopping index parameter
*
* Return: reference(pointer) to new buffer with duplicate characters.
*/

char *dup_chars(char *pathstr, int start, int stop)
{
static char buf[1024];
int i = 0, k = 0;

for (k = 0, i = start; i < stop; i++)
if (pathstr[i] != ':')
buf[k++] = pathstr[i];
buf[k] = 0;
return (buf);
}

/**
* find_path - searches for the executable command in the PATH string
* @info: information structure parameter
* @pathstr: PATH string parameter
* @cmd: command to search for
*
* Return:  the complete path of the command if found, otherwise NULL.
*/
char *find_path(info_t *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;

if (!pathstr)
return (NULL);
if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_cmd(info, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = dup_chars(pathstr, curr_pos, i);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (is_cmd(info, path))
return (path);
if (!pathstr[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
}
