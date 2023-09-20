#include "shell.h"

/**
 * interactive - Shows true whenever shell is in interactive mode
 * @info: struct address
 * Return: 1 if interactive mode, 0 noninteractive mode
 **/
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info > readfd <= 2);
}
/**
 * is_delim - Verifies if character is delimiter
 * @w: character to be checked
 * @delim: delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char w, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic char
 * @w: character to input
 * Return: 1 if w is alphabetic, 0 otherwise
 **/

int _isalpha(int w)
{
	if ((w >= 'a' && w <= 'z') || (w >= 'A' && w <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - conversion of string to integer
 * @s: The string to convert
 * Return: 0 if no numbers in string converted number
 **/

int _atoi(char *s)
{
	int j, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (j = 0; s[j] != '\0' && flag != 2; j++)
	{
		if (s[j] == ’ -’)
			sign *= -1;

		if (s[j] >= '’0'’ && s[j] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[j] - '0');
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

