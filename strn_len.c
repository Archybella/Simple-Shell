#include "shell.h"

/**
 * _strlen - Computes the length of a given string.
 * @s: The string for which the length is to be determined.
 *
 * Return: The length of the string as a size_t value.
 */
int _strlen(char *s)
{
    int i = 0;

    if (!s)
        return (0);

    while (*s++)
        i++;
    return (i);
}

/**
 * _strcmp - Compares two strings in lexicographic order.
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 *
 * Return: A negative value if s1 comes before s2,
 *         or zero if s1 and s2 are equal,
 *         or a positive value if s1 comes after s2.
 */
int _strcmp(char *s1, char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }
    if (*s1 == *s2)
        return (0);
    else
        return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Checks if the needle is found at the beginning of haystack.
 * @haystack: The string to search within.
 * @needle: The substring to find.
 *
 * Return: The address of the next char after the matched substring in haystack
 *         or NULL if the substring is not found at the start.
 */
char *starts_with(const char *haystack, const char *needle)
{
    while (*needle)
        if (*needle++ != *haystack++)
            return (NULL);
    return ((char *)haystack);
}

/**
 * _strcat - Combines two strings together.
 * @dest: The destination buffer to which the source string will be appended.
 * @src: The source buffer containing the string to be appended.
 *
 * Return: A pointer to the destination buffer after the concatenation.
 */
char *_strcat(char *dest, char *src)
{
    char *ret = dest;

    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = *src;
    return (ret);
}
