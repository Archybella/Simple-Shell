#include "shell.h"

/**
* _is_delim - Checks if a character is a delimiter.
* @c: The character to check.
* @delim: The delimiter string.
* Return: 1 if true, 0 if false.
*/
int _is_delim(char c, char *delim)
{
while (*delim)
{
if (*delim++ == c)
return (1);
}
return (0);
}

/**
* _i_salpha - Checks for an alphabetic character.
* @c: The character to input.
* Return: 1 if 'c' is alphabetic, 0 otherwise.
*/
int _i_salpha(int c)
{
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
return (1);
else
return (0);
}

/**
* _is_atoi - Converts a string to an integer.
* @s: The string to be converted.
* Return: 0 if there are no numbers in the string, converted number otherwise.
*/
int _is_atoi(char *s)
{
int i, sign = 1, flag = 0, output;
unsigned int result = 0;

for (i = 0; s[i] != '\0' && flag != 2; i++)
{
if (s[i] == '-')
sign *= -1;

if (s[i] >= '0' && s[i] <= '9')
{
flag = 1;
result *= 10;
result += (s[i] - '0');
}
else if (flag == 1)
flag = 2;
}

if (sign == -1)
output = -result;
else
output = result;

return (output);
}
