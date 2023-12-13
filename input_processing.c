#include "shell.h"

/**
 * getLine - Reads a line from the input source into commandArray.
 * This function reads a line from the specified file descriptor into a buffer
 * and splits it into individual commands stored in the commandArray.
 * It also handles logical operators ('&&' and '||') to separate commands.
 * @data: Pointer to the program's data structure.
 * Return: Number of bytes read from the input source.
 */
int getLine(DataOfProgram *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *commandArray[10] = {NULL};
	static char operatorsArray[10] = {'\0'};
	ssize_t bytesRead, i = 0;


	if (!commandArray[0] || (operatorsArray[0] == '&' && errno != 0) ||
		(operatorsArray[0] == '|' && errno == 0))
	{
		for (i = 0; commandArray[i]; i++)
		{
			free(commandArray[i]);
			commandArray[i] = NULL;
		}

		bytesRead = read(data->fileDescriptor, &buff, BUFFER_SIZE - 1);
		if (bytesRead == 0)
			return (-1);

		i = 0;
		do {
			commandArray[i] = duplicateString(customStrtok(i ? NULL : buff, "\n;"));
			i = checkLogicOperators(commandArray, i, operatorsArray);
		} while (commandArray[i++]);
	}

	data->inputLine = commandArray[0];
	for (i = 0; commandArray[i]; i++)
	{
		commandArray[i] = commandArray[i + 1];
		operatorsArray[i] = operatorsArray[i + 1];
	}

	return (getStringLength(data->inputLine));
}

/**
 * checkLogicOperators - Checks for && and || operators in commands.
 * This function searches for '&&' and '||' operators in
 * the commandArray's commands.
 * It splits the command into separate commands if these operators are found.
 * @commandArray: Array of commands.
 * @i: Index in the commandArray to be checked.
 * @operatorsArray: Array of logical operators for each previous command.
 * Return: Index of the last command in the commandArray.
 */
int checkLogicOperators(char *commandArray[], int i, char operatorsArray[])
{
	char *temp = NULL;
	int j;

	for (j = 0; commandArray[i] != NULL  && commandArray[i][j]; j++)
	{
		if (commandArray[i][j] == '&' && commandArray[i][j + 1] == '&')
		{
			temp = commandArray[i];
			commandArray[i][j] = '\0';
			commandArray[i] = duplicateString(commandArray[i]);
			commandArray[i + 1] = duplicateString(temp + j + 2);
			i++;
			operatorsArray[i] = '&';
			free(temp);
			j = 0;
		}
		if (commandArray[i][j] == '|' && commandArray[i][j + 1] == '|')
		{
			temp = commandArray[i];
			commandArray[i][j] = '\0';
			commandArray[i] = duplicateString(commandArray[i]);
			commandArray[i + 1] = duplicateString(temp + j + 2);
			i++;
			operatorsArray[i] = '|';
			free(temp);
			j = 0;
		}
	}
	return (i);
}
