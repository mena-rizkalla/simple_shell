#include "shell.h"

/**
 * main - main function for the shell
 * @argc: number of arguments passed to main
 * @argv: array of arguments passed to main
 * @environment: array of environment variables
 *
 * Return: 0 or exit status, or ?
 */



int main(int argc, char **argv, char **environment)
{
	size_t len_buffer;
	unsigned int is_pipe;
	unsigned int i;
	vars_t vars = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	(void) argc;
	vars.argv = argv;

	len_buffer = 0;
	is_pipe = 0;
	vars.env = make_env(environment);

	if (!isatty(STDIN_FILENO))
		is_pipe = 1;
	if (is_pipe == 0)
		putsF("$ ");

	while (getline(&(vars.buffer), &len_buffer, stdin) != -1)
	{
		vars.count++;
		vars.commands = tokenize(vars.buffer, ";");
		for (i = 0; vars.commands && vars.commands[i] != NULL; i++)
		{
			vars.av = tokenize(vars.commands[i], "\n \t\r");
			if (vars.av && vars.av[0])
				if (checkForBuiltInFun(&vars) == NULL)
					check_for_path(&vars);
			free(vars.av);
		}
		free(vars.buffer);
		free(vars.commands);
		if (is_pipe == 0)
			putsF("$ ");
		vars.buffer = NULL;
	}
	if (is_pipe == 0)
		putsF("\n");
	free_env(vars.env);
	free(vars.buffer);
	exit(vars.status);
}
