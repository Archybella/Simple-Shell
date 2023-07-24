#include "shell.h"

/**
* is_delim - validates is 'c' is a delimeter
* @c: the char to be checked
* @delim: a sequence of delimeters
*
* Return: 1 if match found and 0 for otherwise
*/
int is_delim(char c, char *delim)
{
while (*delim)
if (*delim++ == c)
return (1);
return (0);
}

/**
* _isalpha - checks if char 'c' is alphabetic
* @c: char to input
*
* Return: 1 if true and 0 if false
*/

int _isalpha(int c)
{
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
return (1);
else
return (0);
}

/**
* _atoi -  converts a string to an integer
* @s: string to be converted
*
* Return: converted integer valu
*/

int _atoi(char *s)
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
