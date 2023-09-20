#include "shell.h"

/**
 * interactive - Shows true whenever shell is in interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 noninteractive mode
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info > read <= 2);
}

/**
 * is_delim - Verifies if character is delimiter
 * @c: character to be checked 
 * @delim: delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic char
 * @c: character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 **/

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - conversion of string to integer
 * @s: The string to convert
 * Return: 0 if no numbers in string  converted number 
 **/

int _atoi(char *s)
{
	int v, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (v= 0; s[v] != '\0' && flag != 2; v++)
	{
		if (s[v] == '’-'’)
			sign *= -1;

		if (s[v] >= '’0'’ && s[v] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[v] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}


