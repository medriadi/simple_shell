#include "shell.h"

/**
 * printString - Writes a string to the standard output.
 * @string: Pointer to the string to be written.
 *
 * Return: The number of bytes written or -1 on error.
 *         On error, errno is set appropriately.
 */
int printString(char *string)
{
	return (write(STDOUT_FILENO, string, getStringLength(string)));
}

/**
 * printErrorString - Writes a string to the standard error.
 * @string: Pointer to the string to be written.
 *
 * Return: The number of bytes written or -1 on error.
 *         On error, errno is set appropriately.
 */
int printErrorString(char *string)
{
	return (write(STDERR_FILENO, string, getStringLength(string)));
}

/**
 * printErrorMessage - Prints an error message to the standard error.
 * @errorCode: Error code to determine the message to print.
 * @data: Pointer to the program's data.
 *
 * Return: Always returns 0.
 */
int printErrorMessage(int errorCode, DataOfProgram *data)
{
	char nString[10] = {'\0'};

	convertLongToString((long) data->execCounter, nString, 10);

	if (errorCode == 2 || errorCode == 3)
	{
		printErrorString(data->programName);
		printErrorString(": ");
		printErrorString(nString);
		printErrorString(": ");
		printErrorString(data->tokenArray[0]);
		if (errorCode == 2)
			printErrorString(": Illegal number: ");
		else
			printErrorString(": can't cd to ");
		printErrorString(data->tokenArray[1]);
		printErrorString("\n");
	}
	else if (errorCode == 127)
	{
		printErrorString(data->programName);
		printErrorString(": ");
		printErrorString(nString);
		printErrorString(": ");
		printErrorString(data->commandName);
		printErrorString(": not found\n");
	}
	else if (errorCode == 126)
	{
		printErrorString(data->programName);
		printErrorString(": ");
		printErrorString(nString);
		printErrorString(": ");
		printErrorString(data->commandName);
		printErrorString(": Permission denied\n");
	}
	return (0);
}

