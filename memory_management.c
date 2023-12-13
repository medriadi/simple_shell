#include "shell.h"


/**
 * freeAllData - Free all allocated memory fields within the data structure.
 * This function frees all memory fields within the program's data structure.
 * @data: Pointer to the program's data structure.
 * Return: None.
 */
void freeAllData(DataOfProgram *data)
{
	if (data->fileDescriptor != 0)
	{
		if (close(data->fileDescriptor))
			perror(data->programName);
	}
	freeRecurrentData(data);
	freePointerArray(data->env);
	freePointerArray(data->aliasList);
}

/**
 * freePointerArray - Free memory allocated to an array of pointers
 *					  and the array itself.
 * This function frees memory allocated for an array of pointers
 * and each individual pointer.
 * @array: Array of pointers to be deallocated.
 * Return: None.
 */
void freePointerArray(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}

/**
 * freeRecurrentData - Free the memory allocated for recurring loop fields.
 * This function releases the memory allocated for specific fields used
 * within each loop iteration in the program's data structure.
 * @data: Pointer to the program's data structure.
 * Return: None.
 */
void freeRecurrentData(DataOfProgram *data)
{
	if (data->tokenArray)
		freePointerArray(data->tokenArray);
	if (data->inputLine)
		free(data->inputLine);
	if (data->commandName)
		free(data->commandName);

	data->inputLine = NULL;
	data->commandName = NULL;
	data->tokenArray = NULL;
}
