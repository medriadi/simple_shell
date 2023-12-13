#include "shell.h"

/**
 * listBuiltins - Search for a match and execute the associated built-in cmd.
 * This function iterates through a list of built-in cmds, attempting to match
 * the provided cmd name with a built-in cmd. If a match is found, it executes
 * the associated built-in command function.
 * @data: Pointer to the program's data structure.
 *
 * Return: Returns the return value of the executed built-in function
 * if there is a match, otherwise returns -1 indicating no match.
 */
int listBuiltins(DataOfProgram *data)
{
	int index_;
	builtins options[] = {
		{"exit", exitShell},
		{"help", displayHelp},
		{"cd", changeDirectory},
		{"alias", handleAlias},
		{"env", displayEnv},
		{"setenv", setEnvVariable},
		{"unsetenv", unsetEnvVariable},
		{NULL, NULL}
	};

	for (index_ = 0; options[index_].builtin != NULL; index_++)
	{

		if (compareStrings(options[index_].builtin, data->commandName, 0))
		{
			return (options[index_].function(data));
		}

	}
	return (-1);
}
