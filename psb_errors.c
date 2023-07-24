#include "shell.h"

/**
* _eputs - displays contents of a given string as output
* @str: string to display
*
* Return: No explicit return value
*/
void _eputs(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
_eputchar(str[i]);
i++;
}
}

/**
* _eputchar - prints the single character(c) output to the stderr
* @c: ouput character
*
* Return: 1 if the output is a success, otherwise -1 is returned and
* appropriate error code is set
*/
int _eputchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(2, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}

/**
* _putfd - writes a single  character(c) to specified file descriptor(fd)
* @c: displayed character
* @fd: file descriptor to be printed
*
* Return: 1 for success, -1 for otherwise and
* Appropriate error code is set
*/
int _putfd(char c, int fd)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(fd, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}

/**
*_putsfd - Outputs an input string to a specified fd
* @str: string output
* @fd: file descriptor to be printed
*
* Return: number of characters that was successfully written
*/
int _putsfd(char *str, int fd)
{
int i = 0;

if (!str)
return (0);
while (*str)
{
i += _putfd(*str++, fd);
}
return (i);
}
