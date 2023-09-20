Built_in0.c

#include "shell.h"

/**
 * _myhistory - Shows list of history each command line by line continue
 * with line numbers begin at  0
 * @info: This is the  structure with arguments and helps maintain
 *function prototype consistently
 *Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Sets alias to a string
 * @info: parameter struct
 * @str: String alias set
 *
 * Return: o for success 1 for  failure
 **/
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sest alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return:  0 on success, 1 on failure
 **/
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Print an alias string
 * @node: alias node
 *
 * Return:  0 on success, 1 on fail
 **/
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Copies alias builtin command man alias
 * @info: Structure with  arguments and it is to maintain
 *     function prototype in code consistently
 *Return: 0 Always
 **/
int _myalias(info_t *info)
{
	int l = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (l = 1; info->argv[l]; l++)
	{
		p = _strchr(info->argv[l], '=');
		if (p)
			set_alias(info, info->argv[l]);
		else
			print_alias(node_starts_with(info->alias, info->argv[l], '='));
	}

	return (0);
}
