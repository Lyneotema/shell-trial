#include "shell.h"
/**
 * get_environ - Return string array cp of the environ
 * @info: Structure having potential args. Used to maintain
 *          constant func. prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Removes environment var.
 * @info: Structure having possible args. Used to maintain
 *        constant func. prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: String environ. var. property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t m = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), m);
			m = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		m++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialises new environ. variable,
 *             or modify an existing environ.
 * @info: Structure having possible args. Used to maintain
 *        constant funct. prototype.
 * @var: String environment var. property
 * @value: String environ. var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
