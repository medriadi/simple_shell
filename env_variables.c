#include "shell.h"

/**
 * getEnvironKey - Retrieve the value of an environment variable.
 * @key: The environment variable name.
 * @data: Pointer to the program's data structure.
 *
 * Return: A pointer to the value of the variable or NULL if not found.
 */
char *getEnvironKey(char *key, DataOfProgram *data)
{
	int i, keyLen = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);

	keyLen = getStringLength(key);

	for (i = 0; data->env[i]; i++)
	{
		if (compareStrings(key, data->env[i], keyLen) &&
		 data->env[i][keyLen] == '=')
		{
			return (data->env[i] + keyLen + 1);
		}
	}
	return (NULL);
}

/**
 * setEnvKey - Set or overwrite the value of an environment variable.
 * @key: Name of the variable to set.
 * @value: New value of the variable.
 * @data: Pointer to the program's data structure.
 *
 * Return: 1 for NULL parameters, 2 for errors, or 0 for success.
 */
int setEnvKey(char *key, char *value, DataOfProgram *data)
{
	int i, keyLen = 0, is_new_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	keyLen = getStringLength(key);

	for (i = 0; data->env[i]; i++)
	{
		if (compareStrings(key, data->env[i], keyLen) &&
		 data->env[i][keyLen] == '=')
		{
			is_new_key = 0;
			free(data->env[i]);
			break;
		}
	}
	data->env[i] = concatenateStrings(duplicateString(key), "=");
	data->env[i] = concatenateStrings(data->env[i], value);

	if (is_new_key)
	{
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * removeEnvKey - Remove an environment variable.
 * @key: The variable to remove.
 * @data: Pointer to the program's data structure.
 *
 * Return: 1 if the variable was removed, 0 if it doesn't exist.
 */
int removeEnvKey(char *key, DataOfProgram *data)
{
	int i, keyLen = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	keyLen = getStringLength(key);

	for (i = 0; data->env[i]; i++)
	{
		if (compareStrings(key, data->env[i], keyLen) &&
		 data->env[i][keyLen] == '=')
		{
			free(data->env[i]);

			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * printEnv - Print the current environment variables.
 * @data: Pointer to the program's data structure.
 *
 * Return: None.
 */
void printEnv(DataOfProgram *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		printString(data->env[j]);
		printString("\n");
	}
}
