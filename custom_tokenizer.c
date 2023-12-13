#include "shell.h"

/**
 * customStrtok - Splits a string into tokens based on a set of delimiters.
 *
 * @line: The string to be tokenized.
 * @delim: A string containing the delimiters to use for tokenization.
 *
 * This function works similarly to the standard `strtok` function, but allows
 * for specifying a custom set of delimiters. It modifies the original string
 * by replacing the first delimiter encountered with a null terminator,
 * effectively separating the string into two parts. Subsequent calls to the
 * function with `line` set to NULL will continue tokenizing the remaining
 * portion of the string.
 *
 * Return: A pointer to the first token, or NULL if no more tokens exist.
 */
char *customStrtok(char *line, char *delim)
{
	int j;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			break;
		}
		if (delim[j] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}
