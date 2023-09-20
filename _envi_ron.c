#include "shell.h"
/**
 * _myenv -  Current environment is printed
 * @info: Struct with arguments and ensures prototype
 *    function  is maintained consistently
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Fetch value of  environ variable
 * @info: Struct with arguments and ensures prototype
*     function  is maintained consistently
 * @name:  Name of environ variable
 *
 * Return:  value
 **/
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Sets new environment variable
 *         or alters existing variable
 * @info: Includes all arguments in the code and is used to
 *    to maintain consistency of prototypes
 *  Return:  0  Always
 **/
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 *_myunsetenv -environment variable is eradicated
 * @info:The arguments are located here and are used
 *to ensure functionality of prototypes
 * Return: Always 0
 **/
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - addition to environ linked list
 * @info: This has arguments and is used to maintain function
 *prototype and its consistency
 * Return: 0 Always
 **/
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
