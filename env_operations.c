#include "shell.h"

/**
* setEnvVariable - Sets an environment variable to a specific value.
* This function sets an environment variable to the provided value.
* @data: Struct containing program's data including tokenized input.
* Return: Zero on success, or an error number if arguments are incorrect.
*/
int setEnvVariable(DataOfProgram *data)
{
	if (data->tokenArray[1] == NULL || data->tokenArray[2] == NULL)
		return (0);
	if (data->tokenArray[3] != NULL)
	{
		errno = E2BIG;
		perror(data->commandName);
		return (5);
	}

	setEnvKey(data->tokenArray[1], data->tokenArray[2], data);

	return (0);
}


/**
* unsetEnvVariable - Unsets/removes an environment variable.
* This function removes an environment variable with the given name.
* @data: Struct containing program's data including tokenized input.
* Return: Zero on success, or an error number if arguments are incorrect.
*/
int unsetEnvVariable(DataOfProgram *data)
{
	if (data->tokenArray[1] == NULL)
		return (0);
	if (data->tokenArray[2] != NULL)
	{
		errno = E2BIG;
		perror(data->commandName);
		return (5);
	}
	removeEnvKey(data->tokenArray[1], data);

	return (0);
}

/**
* displayEnv - Displays the environment variables for the current shell.
* This function shows the environment variables where the shell is operating.
* @data: Struct containing program's data including tokenized input.
* Return: Zero on success, or an error number as defined in the arguments.
*/
int displayEnv(DataOfProgram *data)
{
	int i;
	char copyName[50] = {'\0'};
	char *cpVar = NULL;

	if (data->tokenArray[1] == NULL)
		printEnv(data);
	else
	{
		for (i = 0; data->tokenArray[1][i]; i++)
		{
			if (data->tokenArray[1][i] == '=')
			{
				cpVar = duplicateString(getEnvironKey(copyName, data));
				if (cpVar != NULL)
					setEnvKey(copyName, data->tokenArray[1] + i + 1, data);

				printEnv(data);
				if (getEnvironKey(copyName, data) == NULL)
				{
					printString(data->tokenArray[1]);
					printString("\n");
				}
				else
				{
					setEnvKey(copyName, cpVar, data);
					free(cpVar);
				}
				return (0);
			}
			copyName[i] = data->tokenArray[1][i];
		}
		errno = 2;
		perror(data->commandName);
		errno = 127;
	}
	return (0);
}
