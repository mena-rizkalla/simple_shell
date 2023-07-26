#include "shell.h"


/**
 * tokenize - tokenizes a buffer with a delimiter
 * @buffer: buffer to tokenize
 * @delimiter: delimiter to tokenize along
 *
 * Return: pointer to an array of pointers to the tokens
 */
char **tokenize(char *buffer, char *delimiter)
{
	char **tokens = NULL;
	size_t i = 0, counter = 10;

	if (buffer == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * counter);
	if (tokens == NULL)
	{
		perror("Error");

		return (NULL);
	}
	while ((tokens[i] = new_strtok(buffer, delimiter)) != NULL)
	{
		i++;
		if (i == counter)
		{
			tokens = modified_realloc(tokens, &counter);
			if (tokens == NULL)
			{
				perror("Error");

				return (NULL);
			}
		}
		buffer = NULL;
	}
	return (tokens);
}
