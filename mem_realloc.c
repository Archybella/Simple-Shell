#include "shell.h"

/**
* _memset - fills the memory with a specific byte
* @s: pointer to the memory area
* @b: byte value to fill the memory area with
* @n: number of bytes to be filled with
*
* Return: pointer to the memory area 's'
*/
char *_memset(char *s, char b, unsigned int n)
{
unsigned int i;

for (i = 0; i < n; i++)
s[i] = b;
return (s);
}

/**
* ffree - frees a pointer to an array of strings
* @pp: sequence of strings
*/
void ffree(char **pp)
{
char **a = pp;

if (!pp)
return;
while (*pp)
free(*pp++);
free(a);
}

/**
* _realloc - reallocates a block of memory
* @ptr: points to the initially allocated block of memory
* @old_size: size of the previous block in bytes
* @new_size: size of the new block in bytes
*
* Return: pointer to the reallocated block of memory, otherwise a pointer
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *p;

if (!ptr)
return (malloc(new_size));
if (!new_size)
return (free(ptr), NULL);
if (new_size == old_size)
return (ptr);

p = malloc(new_size);
if (!p)
return (NULL);

old_size = old_size < new_size ? old_size : new_size;
while (old_size--)
p[old_size] = ((char *)ptr)[old_size];
free(ptr);
return (p);
}
