#include "shell.h"

/**
* executeCommand - Execute a command with its entire path variables.
* This function executes a command along with its associated path variables.
* It checks if the command is a built-in function; if not, it attempts to find
* the program in the directories listed in the PATH environment variable.
* @data: Pointer to the program's data including command, arguments, and env.
* Return: Returns zero on success; otherwise, returns -1 in case of failure.
*/
int executeCommand(DataOfProgram *data)
{
	int retval = 0, status;
	pid_t processID;

	retval = listBuiltins(data);
	if (retval != -1)
		return (retval);

	retval = findProgram(data);
	if (retval)
	{
		return (retval);
	}
	else
	{
		processID = fork();
		if (processID == -1)
		{
			perror(data->commandName);
			exit(EXIT_FAILURE);
		}
		if (processID == 0)
		{
			retval = execve(data->tokenArray[0], data->tokenArray, data->env);
			if (retval == -1)
				perror(data->commandName), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
