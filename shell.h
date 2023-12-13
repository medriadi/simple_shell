#ifndef MAIN_SHELL_H
#define MAIN_SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <stdbool.h>


#define PROMPT_MSG "FA.OU $ "

#define UNUSED __attribute__((unused))

#define BUFFER_SIZE 1024

/*Define help messages for built-in commands*/

#define HELP_CD_MSG "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	Alter the current working directory of the shell.\n\n"\
"	If the cd command is used without providing any arguments, \n"\
"	it will be interpreted as follows:\n"\
"	as cd $HOME.\n"\
"	If the argument is - (cd -), the command will be interpreted:\n"\
"	as cd $OLDPWD.\n\n"

#define HELP_EXIT_MSG "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	Exit of the simple_shell.\n\n"\
"	Quits the shell with an exit status of N.\n"\
"	If N is not provided, the exit status\n"\
"	will be that of the last executed command.\n\n"

#define HELP_ENV_MSG "env=\n"\
"env:\tenv \n\n"\
"	Print environment.\n\n"\
"	The env command prints a comprehensive list of environment variables.\n\n"

#define HELP_SETENV_MSG "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Change or add an environment variable.\n\n"\
"	Initialize a new environment variable or modify an existing one.\n"\
"	If there is an incorrect number of arguments, an error message is printed.\n\n"

#define HELP_UNSETENV_MSG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	The unsetenv function deletes one variable from the environment.\n\n"\
"	When there is an incorrect number of arguments, an error message is printed.\n\n"

#define HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	Display information about builtin commands.\n\n"\
"	Summary of builtin commands.\n"\
"	If BUILTIN_NAME is specified,\n"\
"	provides detailed help on commands matching BUILTIN_NAME.\n"\
"   If not, the list of help topics is printed.\n"\
"	Arguments:\n\n"\
"	BUILTIN_NAME specifying a help topic.\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"


/**
 * struct info - Structure holding program-specific data
 * @programName: Name of the executable program
 * @inputLine: Pointer to the input obtained using getline
 * @commandName: Pointer to the first user-typed command
 * @execCounter: Number of times executeCommand function has been called
 * @fileDescriptor: File descriptor for command input/output
 * @tokenArray: Pointer to an array of tokenized input
 * @env: Copy of environment variables (environ)
 * @aliasList: Array of pointers to aliases
 *
 * This structure encapsulates essential data used by the program,
 * including details about the program, input, commands, and environment.
 */
typedef struct info
{
	char *programName;
	char *inputLine;
	char *commandName;
	int execCounter;
	int fileDescriptor;
	char **tokenArray;
	char **env;
	char **aliasList;
} DataOfProgram;

/**
 * struct builtins - Structure defining built-in commands
 * and their associated functions.
 * @builtin: The name of the built-in command
 * @function: Function pointer to the associated built-in function
 *
 * This structure links the name of a built-in command to its corresponding
 * function pointer, allowing easy access to execute specific built-in cmds.
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(DataOfProgram *data);
} builtins;


/* main.c */
void initializeData(DataOfProgram *data, int arc, char *argv[], char **env);
void executeSisifo(char *prompt, DataOfProgram *data);
void handleCtrl_C(int opr UNUSED);

/* input_processing.c */
int getLine(DataOfProgram *data);
int checkLogicOperators(char *commandArray[], int i, char operatorsArray[]);

/* input_expansion.c */
void expandVariables(DataOfProgram *data);
void expandAlias(DataOfProgram *data);
int addToBuffer(char *buffer, char *str_to_add);

/* data_tokenizerc */
void tokenizeData(DataOfProgram *data);

/* custom_tokenizer.c */
char *customStrtok(char *line, char *delim);

/* command_execution.c */
int executeCommand(DataOfProgram *data);

/* builtin_commands.c */
int listBuiltins(DataOfProgram *data);

/* program_search.c */
char **tokenizePath(DataOfProgram *data);
int findProgram(DataOfProgram *data);

/* memory_management.c */
void freePointerArray(char **directoryIndex);
void freeRecurrentData(DataOfProgram *data);
void freeAllData(DataOfProgram *data);

/* builtin_functions.c */
int exitShell(DataOfProgram *data);
int changeDirectory(DataOfProgram *data);
int setWorkingDirectory(DataOfProgram *data, char *newDirectory);
int displayHelp(DataOfProgram *data);
int handleAlias(DataOfProgram *data);

/* env_operations.c */
int displayEnv(DataOfProgram *data);
int setEnvVariable(DataOfProgram *data);
int unsetEnvVariable(DataOfProgram *data);

/* env_variables.c */
char *getEnvironKey(char *name, DataOfProgram *data);
int setEnvKey(char *key, char *value, DataOfProgram *data);
int removeEnvKey(char *key, DataOfProgram *data);
void printEnv(DataOfProgram *data);

/* output_handling.c*/
int printString(char *string);
int printErrorString(char *string);
int printErrorMessage(int errorCode, DataOfProgram *data);

/* alias_operations.c */
int printAlias(DataOfProgram *data, char *alias);
char *getAlias(DataOfProgram *data, char *alias);
int setAlias(char *aliaString, DataOfProgram *data);

/* string_operations.c */
int getStringLength(char *string);
char *duplicateString(char *string);
int compareStrings(char *frtString, char *scdString, int number);
char *concatenateStrings(char *frtString, char *scdString);
void reverseString(char *string);

/* string_conversion.c */
void convertLongToString(long number, char *string, int base);
int parseInt(char *s);
int countCharacters(char *string, char *character);

#endif /* MAIN_SHELL_H */
