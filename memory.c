#include "shell.h"

/**
 * modified_realloc - reallocates a pointer to double the space
 * @ptr: pointer to the old array
 * @size: pointer to number of elements in the old array
 *
 * Return: pointer to the new array
 */

char **modified_realloc(char **ptr, size_t *size)
{
	char **new_ptr;
	size_t i;

	new_ptr = malloc(sizeof(char *) * ((*size) + 10));
	if (new_ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (i = 0; i < (*size); i++)
	{
		new_ptr[i] = ptr[i];
	}
	*size += 10;
	free(ptr);
	return (new_ptr);
}
