#include "shell.h"

/**
 * printAlias - Display specified or all stored aliases.
 * @data: Pointer to the program's data structure.
 * @alias: Name of the alias to be printed. If NULL, prints all aliases.
 *
 * Return: Zero on success or a specific error code if indicated in arguments.
 */
int printAlias(DataOfProgram *data, char *alias)
{
	int i, j, aliasLength;
	char buffer[250] = {'\0'};

	if (data->aliasList)
	{
		aliasLength = getStringLength(alias);
		for (i = 0; data->aliasList[i]; i++)
		{
			if (!alias || (compareStrings(data->aliasList[i], alias, aliasLength)
				&&	data->aliasList[i][aliasLength] == '='))
			{
				for (j = 0; data->aliasList[i][j]; j++)
				{
					buffer[j] = data->aliasList[i][j];
					if (data->aliasList[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				addToBuffer(buffer, "'");
				addToBuffer(buffer, data->aliasList[i] + j + 1);
				addToBuffer(buffer, "'\n");
				printString(buffer);
			}
		}
	}

	return (0);
}

/**
 * getAlias - Retrieve the value of a specific alias.
 * @data: Pointer to the program's data structure.
 * @name: Name of the requested alias.
 *
 * Return: Pointer to the value of the alias if found, otherwise NULL.
 */
char *getAlias(DataOfProgram *data, char *name)
{
	int i, aliasLength;

	if (name == NULL || data->aliasList == NULL)
		return (NULL);

	aliasLength = getStringLength(name);

	for (i = 0; data->aliasList[i]; i++)
	{
		if (compareStrings(name, data->aliasList[i], aliasLength) &&
			data->aliasList[i][aliasLength] == '=')
		{
			return (data->aliasList[i] + aliasLength + 1);
		}
	}
	return (NULL);

}

/**
 * setAlias - Add or override an alias in the program's data structure.
 * @aliaString: Alias to be set in the form (name='value').
 * @data: Pointer to the program's data structure.
 *
 * Return: Zero on success, or a specific error code if indicated in arguments.
 */
int setAlias(char *aliaString, DataOfProgram *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	if (aliaString == NULL ||  data->aliasList == NULL)
		return (1);
	for (i = 0; aliaString[i]; i++)
		if (aliaString[i] != '=')
			buffer[i] = aliaString[i];
		else
		{
			temp = getAlias(data, aliaString + i + 1);
			break;
		}
	for (j = 0; data->aliasList[j]; j++)
		if (compareStrings(buffer, data->aliasList[j], i) &&
			data->aliasList[j][i] == '=')
		{
			free(data->aliasList[j]);
			break;
		}

	if (temp)
	{
		addToBuffer(buffer, "=");
		addToBuffer(buffer, temp);
		data->aliasList[j] = duplicateString(buffer);
	}
	else
		data->aliasList[j] = duplicateString(aliaString);
	return (0);
}
