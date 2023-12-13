#include "shell.h"

/**
 * exitShell - Terminate the program with the specified status.
 * @data: Struct holding program data.
 *
 * Return: 0 on success, or another number if specified in the arguments.
 */
int exitShell(DataOfProgram *data)
{
	int i;

	if (data->tokenArray[1] != NULL)
	{
		for (i = 0; data->tokenArray[1][i]; i++)
			if ((data->tokenArray[1][i] < '0' || data->tokenArray[1][i] > '9')
				&& data->tokenArray[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = parseInt(data->tokenArray[1]);
	}
	freeAllData(data);
	exit(errno);
}

/**
 * changeDirectory - Change the current working directory.
 * @data: Struct holding program data.
 *
 * Return: 0 on success, or another number if specified in the arguments.
 */
int changeDirectory(DataOfProgram *data)
{
	char *homeDirectory = getEnvironKey("HOME", data), *previousDirectory = NULL;
	char oldDirectory[128] = {0};
	int errorCode = 0;

	if (data->tokenArray[1])
	{
		if (compareStrings(data->tokenArray[1], "-", 0))
		{
			previousDirectory = getEnvironKey("OLDPWD", data);
			if (previousDirectory)
				errorCode = setWorkingDirectory(data, previousDirectory);
			printString(getEnvironKey("PWD", data));
			printString("\n");

			return (errorCode);
		}
		else
		{
			return (setWorkingDirectory(data, data->tokenArray[1]));
		}
	}
	else
	{
		if (!homeDirectory)
			homeDirectory = getcwd(oldDirectory, 128);

		return (setWorkingDirectory(data, homeDirectory));
	}
	return (0);
}

/**
 * setWorkingDirectory - Set the working directory.
 * @data: Struct holding program data.
 * @newDirectory: Path to be set as the working directory.
 *
 * Return: 0 on success, or another number if specified in the arguments.
 */
int setWorkingDirectory(DataOfProgram *data, char *newDirectory)
{
	char oldDirectory[128] = {0};
	int errCode = 0;

	getcwd(oldDirectory, 128);

	if (!compareStrings(oldDirectory, newDirectory, 0))
	{
		errCode = chdir(newDirectory);
		if (errCode == -1)
		{
			errno = 2;
			return (3);
		}
		setEnvKey("PWD", newDirectory, data);
	}
	setEnvKey("OLDPWD", oldDirectory, data);
	return (0);
}

/**
 * displayHelp - Display information about the shell environment.
 * @data: Struct holding program data.
 *
 * Return: 0 on success, or another number if specified in the arguments.
 */
int displayHelp(DataOfProgram *data)
{
	int i, length = 0;
	char *messages[6] = {NULL};

	messages[0] = HELP_MSG;

	if (data->tokenArray[1] == NULL)
	{
		printString(messages[0] + 6);
		return (1);
	}
	if (data->tokenArray[2] != NULL)
	{
		errno = E2BIG;
		perror(data->commandName);
		return (5);
	}
	messages[1] = HELP_EXIT_MSG;
	messages[2] = HELP_ENV_MSG;
	messages[3] = HELP_SETENV_MSG;
	messages[4] = HELP_UNSETENV_MSG;
	messages[5] = HELP_CD_MSG;

	for (i = 0; messages[i]; i++)
	{
		length = getStringLength(data->tokenArray[1]);
		if (compareStrings(data->tokenArray[1], messages[i], length))
		{
			printString(messages[i] + length + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->commandName);
	return (0);
}

/**
 * handleAlias - Manipulate aliases: add, remove, or display.
 * @data: Struct holding program data.
 *
 * Return: 0 on success, or another number if specified in the arguments.
 */
int handleAlias(DataOfProgram *data)
{
	int i = 0;

	if (data->tokenArray[1] == NULL)
		return (printAlias(data, NULL));

	while (data->tokenArray[++i])
	{
		if (countCharacters(data->tokenArray[i], "="))
			setAlias(data->tokenArray[i], data);
		else
			printAlias(data, data->tokenArray[i]);
	}

	return (0);
}
