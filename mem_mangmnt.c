#include "shell.h"

/**
* bfree -  Releases a pointer and sets the address to NULL
* @ptr: Address of the pointer to release
*
* Return: 1 if the freeying succeeds, 0 if not
*/

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
