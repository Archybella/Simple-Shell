#include "shell.h"

/**
* split_string - Splits a string into words. Repeat delimiters are ignored.
* @str: The input string.
* @delimiters: The delimiters string.
*
* Return: A pointer to an array of strings, or NULL on failure.
*/
char **split_string(char *str, char *delimiters)
{
int i, j, m, numwords = 0;
char **result;

if (str == NULL || str[0] == 0)
return (NULL);
if (!delimiters)
delimiters = " ";
for (i = 0; str[i] != '\0'; i++)
if (!is_delimiter(str[i], delimiters) && (is_delimiter(str[i + 1], delimiters)
|| !str[i + 1]))
	numwords++;
if (numwords == 0)
return (NULL);
result = malloc((1 + numwords) * sizeof(char *));
if (!result)
return (NULL);
for (i = 0, j = 0; j < numwords; j++)
{
int k = 0;

while (is_delimiter(str[i], delimiters))
i++;
while (!is_delimiter(str[i + k], delimiters) && str[i + k])
k++;
result[j] = malloc((k + 1) * sizeof(char));
if (!result[j])
{
for (k = 0; k < j; k++)
free(result[k]);
free(result);
return (NULL);
}
for (m = 0; m < k; m++)
result[j][m] = str[i++];
result[j][m] = 0;
}
result[j] = NULL;
return (result);
}

/**
* split_string2 - Splits a string into words.
* @str: The input string.
* @delimiter: The delimiter character.
*
* Return: A pointer to an array of strings, or NULL on failure.
*/
char **split_string2(char *str, char delimiter)
{
int i, j, m, numwords = 0;
char **result;

if (str == NULL || str[0] == 0)
return (NULL);
for (i = 0; str[i] != '\0'; i++)
if ((str[i] != delimiter && str[i + 1] == delimiter) ||
(str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
numwords++;
if (numwords == 0)
return (NULL);
result = malloc((1 + numwords) *sizeof(char *));
if (!result)
return (NULL);
for (i = 0, j = 0; j < numwords; j++)
{
int k = 0;

while (str[i + k] && str[i + k] != delimiter)
k++;
result[j] = malloc((k + 1) * sizeof(char));
if (!result[j])
{
for (k = 0; k < j; k++)
free(result[k]);
free(result);
return (NULL);
}
for (m = 0; m < k; m++)
result[j][m] = str[i++];
result[j][m] = 0;
}
result[j] = NULL;
return (result);
}
