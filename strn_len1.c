#include "shell.h"

/**
* _strcpy - replicates a string from (src) to (dest)
* @dest: memory address to the destination string
* @src: memory address to the source string
*
* Return: memory address to the dest str after the copy operation
*/

char *_strcpy(char *dest, char *src)
{
int i = 0;

if (dest == src || src == 0)
return (dest);
while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = 0;
return (dest);
}

/**
* _strdup - dreplicates a string
* @str: string to be replicated
*
* Return: Memory address to replicated string
*/

char *_strdup(const char *str)
{
int length = 0;
char *ret;

if (str == NULL)
return (NULL);
while (*str++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--str;
return (ret);
}

/**
* _puts - outputs input string
* @str: output string
*
* Return: No value.
*/
void _puts(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}
}

/**
* _putchar - Displays Char 'c' to standard output
* @c: element to display
*
* Return: 1 if successful
* -1 if there is an error, consequently errno is set fittingly.
*/

int _putchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}
