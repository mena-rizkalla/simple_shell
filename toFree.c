#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdarg.h>

/**
 * free_array - Free function.
 *
 * @arr: array
 */

void free_array(char **arr)
{
	int i = 0;

	for (i = 0; arr[i] != NULL; i++)
	{
		free(arr[i]);
	}

	free(arr);
}


/**
 * free_strings - Free.
 *
 * @num: num
 *
 */


void free_strings(int num, ...)
{
	int i = 0;
	va_list args;

	va_start(args, num);

	for (i = 0; i < num; i++)
	{
		char *str = va_arg(args, char *);

		free(str);
		i++;
	}

	va_end(args);
}
