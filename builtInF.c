#include "shell.h"

/**
 * checkForBuiltInFun - check if the command is builtin function
 *
 * @vars: variablesShell
 *
 * Return: pointer to the func
 *
 */

void (*checkForBuiltInFun(vars_t *vars))(vars_t *vars)
{

	builtins_t find[] = {{"exit", nExit}, {"env", nEnv},
		{"setenv", nSetenv}, {"unsetenv", nUnSetenv}, {NULL, NULL}};

	 unsigned int i;

	for (i = 0 ; find[i].f != NULL; i++)
	{
		if (strCmpr(vars->av[0], find[i].name) == 0)
			break;
	}

	if (find[i].f != NULL)
	{
		find[i].f(vars);
	}

	return (find[i].f);

}


/**
 * nExit -> new Exit
 * to exit the program
 *
 * @vars: variablesShell
 *
 * Return:void
 */

void nExit(vars_t *vars)
{
	int status;

	if (strCmpr(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
	{
		status = atoiFun(vars->av[1]);
		if (status == -1)
		{
			vars->status = 2;
			print_error(vars, ": Illegal integer: ");
			nPuts2(vars->av[1]);
			nPuts2("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}

		vars->status = status;

	}
	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	free_env(vars->env);
	exit(vars->status);

}

/**
 * nEnv - prints the current environment
 *
 * @vars: variablesShell
 * Return: void.
 */

void nEnv(vars_t *vars)
{
	unsigned int i;

	for (i = 0; vars->env[i]; i++)
	{
		putsF(vars->env[i]);
		putsF("\n");
	}
	vars->status = 0;
}


/**
 * nSetenv - create a new environment variable, or edit an existing variable
 * @vars: pointer to struct of variables
 *
 * Return: void
 */


void nSetenv(vars_t *vars)
{
	char **key;
	char *var;

	if (vars->av[1] == NULL || vars->av[2] == NULL)
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
		add_key(vars);
	else
	{
		var = add_value(vars->av[1], vars->av[2]);
		if (var == NULL)
		{
			print_error(vars, NULL);
			free(vars->buffer);
			free(vars->commands);
			free(vars->av);
			free_env(vars->env);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	vars->status = 0;
}

/**
 * nUnSetenv - remove an environment variable
 * @vars: pointer to a struct of variables
 *
 * Return: void
 */
void nUnSetenv(vars_t *vars)
{
	char **key, **newenv;

	unsigned int i, j;

	if (vars->av[1] == NULL)
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
	{
		print_error(vars, ": No variable to unset");
		return;
	}
	for (i = 0; vars->env[i] != NULL; i++)
		;
	newenv = malloc(sizeof(char *) * i);
	if (newenv == NULL)
	{
		print_error(vars, NULL);
		vars->status = 127;
		nExit(vars);
	}
	for (i = 0; vars->env[i] != *key; i++)
		newenv[i] = vars->env[i];
	for (j = i + 1; vars->env[j] != NULL; j++, i++)
		newenv[i] = vars->env[j];
	newenv[i] = NULL;
	free(*key);
	free(vars->env);
	vars->env = newenv;
	vars->status = 0;
}
