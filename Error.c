#include "shell.h"

/**
 * print_error - prints error messages to standard error
 * @vars: pointer to struct of variables
 * @msg: message to print out
 *
 * Return: void
 */
void print_error(vars_t *vars, char *msg)
{
	char *count;

	nPuts2(vars->argv[0]);
	nPuts2(": ");
	count = _uitoa(vars->count);
	nPuts2(count);
	free(count);
	nPuts2(": ");
	nPuts2(vars->av[0]);
	if (msg)
	{
		nPuts2(msg);
	}
	else
		perror("");
}

/**
 * nPuts2 - prints a string to standard error
 * @str: string to print
 *
 * Return: void
 */
void nPuts2(char *str)
{
	ssize_t num, len;

	num = _strlen(str);
	len = write(STDERR_FILENO, str, num);
	if (len != num)
	{
		perror("Fatal Error");
		exit(1);
	}

}

/**
 * _uitoa - converts an unsigned int to a string
 * @count: unsigned int to convert
 *
 * Return: pointer to the converted string
 */
char *_uitoa(unsigned int count)
{

	int digits = 0;
	unsigned int tmp = count;
	char *numStr;
	int i;

	while (tmp != 0)
	{
		digits++;
		tmp /= 10;
	}

	numStr = malloc(sizeof(char) * (digits + 1));

	if (numStr == NULL)
	{
		perror("Fatal error");
		exit(127);
	}
	numStr[digits] = '\0';
	for (i = digits - 1; i >= 0; i--)
	{
		numStr[i] = (count % 10) + '0';
		count /= 10;
	}

	return (numStr);
}
