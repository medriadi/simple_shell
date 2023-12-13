#include "shell.h"

/**
 * convertLongToString - Converts a long number to a string representation.
 * @number: The number to convert to a string.
 * @string: Buffer to store the resulting string.
 * @base: Base for the number system conversion.
 *
 * Return: No return value.
 */
void convertLongToString(long number, char *string, int base)
{
	int index = 0, inNegative = 0;
	long quotient  = number;
	char nameLetters[] = {"0123456789abcdef"};

	if (quotient  == 0)
		string[index++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (quotient)
	{
		if (quotient  < 0)
			string[index++] = nameLetters[-(quotient  % base)];
		else
			string[index++] = nameLetters[quotient  % base];
		quotient  /= base;
	}
	if (inNegative)
		string[index++] = '-';

	string[index] = '\0';
	reverseString(string);
}


/**
 * parseInt - Converts a string to an integer representation.
 * @s: Pointer to the source string.
 *
 * Return: Integer representation of the string or 0.
 */
int parseInt(char *s)
{
	int valueSign  = 1;
	unsigned int number = 0;

	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			valueSign  *= -1;
		if (*s == '+')
			valueSign  *= +1;
		s++;
	}

	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * valueSign);
}

/**
 * countCharacters - Counts the occurrences of a character in a string.
 * @string: Pointer to the source string.
 * @character: String containing characters to be counted.
 *
 * Return: Count of characters found in the string or 0.
 */
int countCharacters(char *string, char *character)
{
	int i = 0, dirCounter  = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			dirCounter++;
	}
	return (dirCounter);
}

