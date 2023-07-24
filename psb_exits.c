#include "shell.h"

/**
* _strncpy - Performs a string copy operation
* @dest: Pointer to the destination string where the copy will be stored
* @src: Pointer to the source string to be copied
* @n: The maximum number of characters to be copied
* Return: Pointer to the destination string
*/
char *_strncpy(char *dest, char *src, int n)
{
int i;
char *s = dest;

i = 0;
while (i < n - 1 && src[i] != '\0')
{
dest[i] = src[i];
i++;
}
if (i < n)
{
int j = i;

while (j < n)
{
dest[j] = '\0';
j++;
}
}
return (s);
}

/**
* *_strncat - Performs a string concatenation operation
*@dest: Pointer to the destination string where merging is performed
*@src: Pointer to the source string to be merged(concantated)
*@n: The maximum number of bytes to be used for merging
*Return: Pointer to the merged string
*/
char *_strncat(char *dest, char *src, int n)
{
int i, j;
char *s = dest;

i = 0;
j = 0;
while (dest[i] != '\0')
i++;
while (j < n && src[j] != '\0')
{
dest[i] = src[j];
i++;
j++;
}
if (j < n)
dest[i] = '\0';
return (s);
}

/**
* *_strchr - searches for a character within a string
* @s: the string to be examined
* @c: the character to be found
* Return: (s) a pointer to the memory location of the character
*/
char *_strchr(char *s, char c)
{
do {
if (*s == c)
return (s);
} while (*s++ != '\0');

return (NULL);
}
