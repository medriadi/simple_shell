#include "shell.h"

/**
 * main - Entry point of the shell program.
 * Initializes the program variables and starts the execution loop.
 * @argc: Number of arguments received from the command line.
 * @argv: Array of strings containing the arguments.
 * @env: Array of strings containing environment variables.
 * Return: Zero on successful execution.
 */
int main(int argc, char *argv[], char *env[])
{
	DataOfProgram dataStruct = {NULL}, *data = &dataStruct;
	char *prompt = "";

	initializeData(data, argc, argv, env);

	signal(SIGINT, handleCtrl_C);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	executeSisifo(prompt, data);
	return (0);
}

/**
 * handleCtrl_C - Handles the SIGINT (ctrl + c) signal interrupt.
 * Prints a new line and the shell prompt when SIGINT is received.
 * @UNUSED: Option of the prototype (unused).
 */
void handleCtrl_C(int opr UNUSED)
{
	printString("\n");
	printString(PROMPT_MSG);
}

/**
 * initializeData - Initializes the program's data structure
 *					with necessary info.
 * @data: Pointer to the program's data structure.
 * @argv: Array of strings containing program execution arguments.
 * @env: Array of strings containing environment variables.
 * @argc: Number of arguments received from the command line.
 */
void initializeData(DataOfProgram *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->programName = argv[0];
	data->inputLine = NULL;
	data->commandName = NULL;
	data->execCounter = 0;
	if (argc == 1)
		data->fileDescriptor = STDIN_FILENO;
	else
	{
		data->fileDescriptor = open(argv[1], O_RDONLY);
		if (data->fileDescriptor == -1)
		{
			printErrorString(data->programName);
			printErrorString(": 0: Can't open ");
			printErrorString(argv[1]);
			printErrorString("\n");
			exit(127);
		}
	}
	data->tokenArray = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = duplicateString(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->aliasList = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->aliasList[i] = NULL;
	}
}

/**
 * executeSisifo - Executes the main loop of the shell program.
 * Shows the prompt, reads input, processes, and executes commands.
 * @prompt: Prompt to be printed.
 * @data: Pointer to the program's data structure.
 */
void executeSisifo(char *prompt, DataOfProgram *data)
{
	int errorCode = 0, string_len = 0;

	while (++(data->execCounter))
	{
		printString(prompt);
		errorCode = string_len = getLine(data);

		if (errorCode == EOF)
		{
			freeAllData(data);
			exit(errno);
		}
		if (string_len >= 1)
		{
			expandAlias(data);
			expandVariables(data);
			tokenizeData(data);
			if (data->tokenArray[0])
			{
				errorCode = executeCommand(data);
				if (errorCode != 0)
					printErrorMessage(errorCode, data);
			}
			freeRecurrentData(data);
		}
	}
}

